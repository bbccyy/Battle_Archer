

#include "MoveCurve.h"



void MoveCurve::Init(CurveParam& aParam)
{
	InitBase(aParam.mSelf->GetView(), aParam.mSelf, aParam.mTarPos);

	mSpeed0 = aParam.mSpeed;
	mSpeed = mSpeed0;
	mAngle = aParam.mAngle;
	mOffset1 = aParam.mOffset1;
	mOffset2 = aParam.mOffset2;
	for (int i = 0; i < SEG_NUM; i++)
	{
		mAccInSec0[i] = aParam.mAccInSec0[i];
		mAccDInSec[i] = aParam.mAccDInSec[i];
	}

	RefreshStatus();
}


void MoveCurve::Reset()
{
	MoveExecutor::Reset();
	mCurPos.Set(0,0,0);
	mCurRot.Set(0,0,0);
}


void MoveCurve::Enable()
{
	Vector3 curPos;
	GetPosition(curPos);
	if (mView && mSelf && mSelf->GetEntityId() > 0)
	{
		mView->Execute(ViewCommand::Maneuver,
			mSelf->GetEntityId(),
			static_cast<int>(EMoveType::EMoveCurve),
			curPos.x, curPos.y, curPos.z,
			mTargetPos.x, mTargetPos.y, mTargetPos.z,
			mSpeed, mAngle, mOffset1, mOffset2,
			mAccInSec0[0], mAccInSec0[1], mAccInSec0[2],
			mAccDInSec[0], mAccDInSec[1], mAccDInSec[2]);
	}
	mEnabled = true;
	mStatus = EMoveStatus::EMoveStart;
}

void MoveCurve::Disable()
{
	mView->Execute(ViewCommand::Maneuver,
		mSelf->GetEntityId(),
		static_cast<int>(EMoveType::EMoveNone),
		static_cast<int>(EMoveType::EMoveCurve));
}

void MoveCurve::RefreshStatus()
{
	mTime = 0;
	mPosOnLine = 0;
	mSegIndex = 0;

	GetPosition(mStartPos);
	mForward.x = mTargetPos.x - mStartPos.x;
	mForward.z = mTargetPos.z - mStartPos.z;
	mForward.y = 0;
	mRight.x = mForward.z;
	mRight.z = -mForward.x;

	mLineLen = mForward.Magnitude();  // Line distance from startPos to Target in 2D plane
	mForward.y = mTargetPos.y - mStartPos.y;
	mCurTargetLen = mLineLen / SEG_NUM;  // distance for every Seg

	mSinDeflection = CosineInt(90 - mAngle, 1, DENOM);
	mCosDeflection = CosineInt(mAngle, 1, DENOM);

	if(mLineLen > 0 )
	{
		mOffset1 = mOffset1 * mLineLen / DENOM;
		mOffset2 = mOffset2 * mLineLen / DENOM;
		mControlPoint1 = mOffset1 * BEZIER_DENOM / mLineLen;
		mControlPoint2 = mOffset2 * BEZIER_DENOM / mLineLen;
	}
	else
	{
		mControlPoint1 = 0;
		mControlPoint2 = 0;
	}	

	mBezierCoef3 = mControlPoint1 - mControlPoint2;
	mBezierCoef2 = mControlPoint2 - 2 * mControlPoint1;
	mBezierCoef1 = mControlPoint1;

	mStatus = EMoveStatus::EMoveInit;
	mEnabled = false;
	Enable();
}

void MoveCurve::SetTargetPos(Vector3 aPos)
{
	mTargetPos = aPos;
}

void MoveCurve::SetSpeedParams(int64 aSpeed, const int64 aAccInSec0[SEG_NUM], const int64 aAccDInSec[SEG_NUM])
{
	mSpeed0 = aSpeed;
	mSpeed = mSpeed0;
	for (int i = 0; i < SEG_NUM; i++)
	{
		mAccInSec0[i] = aAccInSec0[i];
		mAccDInSec[i] = aAccDInSec[i];
	}
}

EMoveStatus MoveCurve::OnTick(int aDeltaTime)
{
	if (!mEnabled)
	{
		Enable();
	}
	if (mStatus == EMoveStatus::EMoveDone)
	{
		return mStatus;
	}
	if( mLineLen == 0)
	{
		mStatus = EMoveStatus::EMoveDone;
		return mStatus;
	}
	mTime += aDeltaTime;

	bool touchEnd = false;
	GetPosition(mCurPos);
	Vector3 prePos = mCurPos;

	// distance that one should run during delta time
	int64 deltLen = mSpeed * aDeltaTime + mAccInSec0[mSegIndex] * aDeltaTime * aDeltaTime / (MS_OF_SEC2 * 2)
		+ mAccDInSec[mSegIndex] * aDeltaTime*aDeltaTime*aDeltaTime / (MS_OF_SEC3 * 6);
	mSpeed = mSpeed0 + mAccInSec0[mSegIndex] * mTime / MS_OF_SEC2 + mAccDInSec[mSegIndex] * mTime*mTime / MS_OF_SEC3;

	// distance to the next Checkpoint of Segment
	int64 dist = mCurTargetLen - mPosOnLine;
	if (abs(dist) <= abs(deltLen))
	{	//too prevent tiny mCurTargetLen with Hudge deltLen case
		//(which will lead some fancy bug here which stops program from entering this code block)

		//if (mSegIndex >= SEG_NUM)  
		{
			deltLen = dist;
		}
		touchEnd = true;
	}
	mPosOnLine += deltLen;

	//映射到曲线上 
	//三次贝赛尔曲线公式p0*(1-t).^3 + 3*p1*t.*(1-t).^2 + 3*p2*t.^2.*(1-t) + p3*t.^3; 
	//p0 = 0; p3 = 0;    3*p1*t.*(1-t).^2 + 3*p2*t.^2.*(1-t). 
	// 3* [ (p1 - p2)*t.^3 + ( p2 - 2*p1)*t.^2 + p1*t ]
	// 3 * [ (p1 - p2)*t.^2 + ( p2 - 2*p1)*t + p1 ] * t 
	int64 t = mPosOnLine * BEZIER_DENOM / mLineLen;
	int64 lineCurveDist = 3 * (mBezierCoef3*t*t / BEZIER_DENOM_2 + mBezierCoef2 * t / BEZIER_DENOM + mBezierCoef1) * t / BEZIER_DENOM;
	Vector3 forward = mForward;
	forward.ScaleToLen(mPosOnLine);
	Vector2 right = mRight;
	lineCurveDist = lineCurveDist * mLineLen / BEZIER_DENOM;
	right.ScaleToLen(mSinDeflection * lineCurveDist / DENOM);

	mCurPos.x = mStartPos.x + forward.x + right.x;
	mCurPos.z = mStartPos.z + forward.z + right.z;
	mCurPos.y = mStartPos.y + mCosDeflection * lineCurveDist / DENOM + forward.y;
	mCurRot = mCurPos;
	mCurRot -= prePos;

	//if (mView)  //INFO: this part is only for testing, will remove later on
	//{
	//	mView->Execute(ViewCommand::Move
	//		, mSelf->GetEntityId()
	//		, mCurPos.x, mCurPos.y, mCurPos.z
	//		, mCurRot.x, mCurRot.y, mCurRot.z
	//		, mSpeed, 0, 0);
	//}

	SetPosAndRot(mCurPos, mCurRot); //fresh self entity

	if (touchEnd)
	{
		mSegIndex++;
		mCurTargetLen = (mSegIndex + 1) * mLineLen / SEG_NUM;
		if (mSegIndex == SEG_NUM)
		{
			mStatus = EMoveStatus::EMoveDone;
		}
	}

	return mStatus;
}


EMoveType MoveCurve::Type()
{
	return EMoveType::EMoveCurve;
}