#pragma once
#include <algorithm>
#include "BoundingVolume.h"

//using namespace std;


bool IntersectRayAABB2D( const Vector2& aStart, const Vector2& aEnd, const AABB2D* aAABB, Vector2& aCollisionPoint, int64& aCollisionPos )
{
    Vector2 startToEnd( aEnd.x - aStart.x, aEnd.z - aStart.z);
    int64 len = startToEnd.Magnitude();
    int64 tNear = INT64_MIN;
    int64 tFar = INT64_MAX;
    
    for(int i = 0; i < 2; i++)
    {
        //平行与当前轴的垂直面(x-slab)
        if ( startToEnd[i] == 0 )
        {
            if( aStart[i] < aAABB->min[i] || aStart[i] > aAABB->max[i] )
            {
                return false;
            }
        }
        else
        {
            
            //本来应该是( aAABB->min[i] - aStart[i] )/startToEnd[i]; 考虑精度问题，我们使用长度，不使用比例
            int64 t1 = ( aAABB->min[i] - aStart[i] ) * len / startToEnd[i];
            int64 t2 = ( aAABB->max[i] - aStart[i] ) * len / startToEnd[i];

            if( t1 > t2)
            {
                std::swap(t1, t2);
            }
            tNear = std::max(tNear, t1);
            tFar = std::min(tFar, t2);
            if( tNear > tFar)
            {
                return false;
            }
            
        }
    }
    aCollisionPos = tNear;
    aCollisionPoint = aStart;
    startToEnd.ScaleToLen(tNear);
    aCollisionPoint += startToEnd;
    
    return true;
}

bool ContainPointAABB2D(const Vector2& aPoint, const AABB2D* aAABB)
{
    int64 minX = aAABB->min.x;
    int64 maxX = aAABB->max.x;
    if (maxX < minX) 
	{
         std::swap(maxX, minX);
    }
    int64 minZ = aAABB->min.z;
    int64 maxZ = aAABB->max.z;
    if (maxZ < minZ) 
	{
         std::swap(maxZ, minZ);
    }
    if (aPoint.x < minX || 
        aPoint.x > maxX || 
        aPoint.z < minZ || 
        aPoint.z > maxZ)
    {
        return false;
    }
    return true;
}

bool IntersectSegmentAABB2D( const Vector2& aStart, const Vector2& aEnd, const AABB2D* aAABB, Vector2& aCollisionPoint, int64& aCollisionPos )
{
    bool containStart = ContainPointAABB2D(aStart, aAABB); //首先判断首尾点的情况，是否在AABB内
    bool containEnd   = ContainPointAABB2D(aEnd, aAABB);
    if (containStart && containEnd)  //两者都在AABB内，属于特殊情况，直接返回
    {
        aCollisionPos = 0;
        aCollisionPoint = aStart;
        return true;
    }

    Vector2 startToEnd( aEnd.x - aStart.x, aEnd.z - aStart.z);
    int64 len = startToEnd.Magnitude();
    int64 tNear = INT64_MIN;
    int64 tFar = INT64_MAX;
    int Count = 0;  //在线段的范围内，与slab边界线及其衍生线相交的次数
    
    for(int i = 0; i < 2; i++)
    {
        //平行与当前轴
        if ( startToEnd[i] == 0 )
        {
            if( aStart[i] < aAABB->min[i] || aStart[i] > aAABB->max[i] )
            {
                return false;
            }
        }
        else
        {
            int64 t1 = ( aAABB->min[i] - aStart[i] ) * len / startToEnd[i];
            int64 t2 = ( aAABB->max[i] - aStart[i] ) * len / startToEnd[i];
            if (t1 >=0 && t1 <= len) 
			{
                Count++;
            }
            if (t2 >=0 && t2 <= len) 
			{
                Count++;
            }
            if( t1 > t2)
            {
                std::swap(t1, t2);
            }
            tNear = std::max(tNear, t1);
            tFar = std::min(tFar, t2);
            if( tNear > tFar)
            {
                return false;
            }
        }
    }
    if (Count == 0) 
	{ //没有焦点在线段范围内，不相交
        return false;
    }
    if (Count == 1) 
	{  //只有一个焦点在线段范围内
        if (containStart) 
		{
            //aCollisionPos = tFar;  //start点在AABB内，但是end在外的情况，焦点其实是由tFar表示的
            aCollisionPos = 0;  //希望让startPoint来表示碰撞点
        }
		else if (containEnd) 
		{
            aCollisionPos = tNear;
        } 
		else 
		{
            return false; //首尾两点都不在AABB内，且只有1个焦点在线段范围内，这种情况不可能相交
        }
    } else 
	{  //拥有2个或2个以上的焦点处在线段自身范围内，且“射线”与AABB相交，则“线段”必定与之相交
        if (containStart) 
		{
            aCollisionPos = tFar;
        } 
		else 
		{
            aCollisionPos = tNear;
        }
    }
    
    aCollisionPoint = aStart;
    startToEnd.ScaleToLen(aCollisionPos);
    aCollisionPoint += startToEnd;
    
    return true;
}

bool IntersectSegmentSphere2D( const Vector2& aStart, const Vector2& aEnd,  Vector2 aCenter, int64 aRadius, Vector2& aCollisionPoint, int64& aCollisionPos )
{

    Vector2 startToCenter( aCenter.x - aStart.x, aCenter.z - aStart.z);
    Vector2 centerToStart( aStart.x - aCenter.x, aStart.z - aCenter.z);  //f
    //起点在圆内或圆上
    int64 c =  centerToStart.Magnitude2() - aRadius*aRadius; //c
    if ( c <= 0)
    {
        aCollisionPos = 0;
        aCollisionPoint = aStart;
        return true;
    }
    if (aStart == aEnd)  //如果线段只是一个点，不在园内就不可能相交了
    {
        return false;
    }

    Vector2 startToEnd( aEnd.x - aStart.x, aEnd.z - aStart.z);  //d
    int64 lineMag2 = startToEnd.Magnitude2(); //a

    int64 product = Vector2::Dot(startToEnd, centerToStart); //b/2

    //https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
    //https://stackoverflow.com/questions/1073336/circle-line-segment-collision-detection-algorithm
    int64 discriminant = product * product - lineMag2 * c;  // b^2/4 - ac
    if ( discriminant < 0 )
    {
        return false; //两点都在园外，且公式无解，不相交
    }

    int64 numerator1  = -product - Sqrt(discriminant);

    aCollisionPos = Sqrt(lineMag2) * numerator1 / lineMag2;

    if(aCollisionPos < 0)
    {
        aCollisionPos = 0;
		return false;
    }
	if(startToEnd.Magnitude() < aCollisionPos)
    {
        return false;
    }

    aCollisionPoint = aStart;
    startToEnd.ScaleToLen(aCollisionPos);
    aCollisionPoint += startToEnd;
    return true;
}

float Dot(float x1, float y1, float x2, float y2)
{
    return x1 * x2 + y1 * y2;
}

bool testSegmentSphere2D( float start_x, float start_z, float end_x, float end_z, float center_x, float center_z,
 float aRadius )
{
    float d_x = end_x - start_x;
    float d_z = end_z - start_z;
    float f_x = start_x - center_x;
    float f_z = start_z - center_z;

    float a = Dot(d_x, d_z, d_x, d_z);
    float b = 2 * Dot(f_x, f_z, d_x, d_z);
    float c = Dot(f_x, f_z, f_x, f_z) - aRadius * aRadius;

    float discriminant = b*b - 4*a*c;
    //cout << "float discriminant = " << discriminant << endl;
    if (discriminant < 0)
    {
        //cout<< "no intersection at all" << endl;
        return false;
    }

    discriminant = sqrt( discriminant );

    float t1 = (-b - discriminant)/(2*a);
    float t2 = (-b + discriminant)/(2*a);

    if (t1 >=0 && t1 <= 1)
    {
        //cout << "Impale or Poke, t1 = " << t1 << endl;
        //cout << "collision point is: <" << d_x * t1 + start_x << ", " << d_z * t1 + start_z << ">" << endl;
        return true;
    }

    if (t2 >=0 && t2 <= 1)
    {
        //cout<< "ExitWound, t2 = " << t2 << endl;
        //cout << "collision point is: <" << d_x * t2 + start_x << ", " << d_z * t2 + start_z << ">" << endl;
        return true;
    }


    return false;
}


bool IntersectMovingSphereAABB2D( const Vector2& aStart, const Vector2& aEnd, int64 aRadius, const AABB2D* aAABB, Vector2& aCollisionPoint, int64& aCollisionPos)
{
    //首先判断起点是否已经在目标AABB内
    if (ContainPointAABB2D(aStart, aAABB))
    {
        aCollisionPoint = aStart;
        aCollisionPos = 0;
        return true;
    }

    AABB2D e = *aAABB;
    e.min.x -= aRadius;
    e.max.x += aRadius;
    e.min.z -= aRadius;
    e.max.z += aRadius;

    Vector2 point;
    //判断是否和外包的矩形相交，不相交则Sphere和AABB没有相交的可能
    if( !IntersectSegmentAABB2D(aStart, aEnd, &e, point, aCollisionPos) )
    {
        return false;
    }

    Vector2 sideCenter;
    int mark = 0;

    //判断交点的落点，决定是否要对矩形的某个角作二次检查
    if( point.x < aAABB->min.x) 
    {
        sideCenter.x = aAABB->min.x;
        if (point.z > aAABB->max.z)
        {
            sideCenter.z = aAABB->max.z;

        } 
		else if (point.z < aAABB->min.z)
        {
            sideCenter.z = aAABB->min.z;
        } 
		else
        {
            mark = 1; //left
        }
    }
    else if( point.x > aAABB->max.x) 
    {
        sideCenter.x = aAABB->max.x;
        if (point.z > aAABB->max.z)
        {
            sideCenter.z = aAABB->max.z;

        } 
		else if (point.z < aAABB->min.z)
        {
            sideCenter.z = aAABB->min.z;
        } 
		else
        {
            mark = 2; //right
        }
    }

    if( point.z < aAABB->min.z) 
    {
        sideCenter.z = aAABB->min.z;
        if (point.x > aAABB->max.x)
        {
            sideCenter.x = aAABB->max.x;

        }
		else if (point.x < aAABB->min.x)
        {
            sideCenter.x = aAABB->min.x;
        }
		else
        {
            mark = 3; //down
        }
    }
    else if( point.z > aAABB->max.z) 
    {
        sideCenter.z = aAABB->max.z;
        if (point.x > aAABB->max.x)
        {
            sideCenter.x = aAABB->max.x;

        } 
		else if (point.x < aAABB->min.x)
        {
            sideCenter.x = aAABB->min.x;
        } 
		else
        {
            mark = 4; //up
        }
    }
    
    if ( mark == 0 ) //与四个角之一相交，需要二次检测
    {
        if (!IntersectSegmentSphere2D(aStart, aEnd, sideCenter, aRadius, point, aCollisionPos))
        {
            return false;
        }
        aCollisionPoint = sideCenter;  //这种情况交点就是4个角中的一个
    } 
	else 
    {
        aCollisionPos += aRadius;  //修正pos，之前的pos只是圆心的位置，所以要补上半径部分
        aCollisionPoint = point;
        switch (mark)  //真正的交点需要视情况作上下左右修正，交点必然在外立面上
        {
            case 1:
                aCollisionPoint.x = aAABB->min.x;
                break;
            case 2:
                aCollisionPoint.x = aAABB->max.x;
                break;
            case 3:
                aCollisionPoint.z = aAABB->min.z;
                break;
            case 4:
                aCollisionPoint.z = aAABB->max.z;
                break;
            default:
                break;
        }
    }

    return true;
}

bool ImplementIntersectMovingSphereSphere2D(const Vector2& aStart, const Vector2& aEnd, int64 aRadius1, const Vector2& aCenter, int64 aRadius2, Vector2& aCollisionPoint, int64& aCollisionPos)
{
    return IntersectSegmentSphere2D(aStart, aEnd, aCenter, aRadius1 + aRadius2, aCollisionPoint, aCollisionPos);
}

bool IntersectMovingSphereSphere2D( const Vector3& aStart, const Vector3& aEnd, int64 aRadius, const Cylinder* aCylinder, Vector2& aCollisionPoint, int64& aCollisionPos)
{
    Vector2 start(aStart.x, aStart.z);
    Vector2 end(aEnd.x, aEnd.z);
    Vector2 center(aCylinder->center.x, aCylinder->center.z);
    return ImplementIntersectMovingSphereSphere2D(start, end, aRadius, center, aCylinder->radius, aCollisionPoint, aCollisionPos );
}

bool IntersectMovingSphereOBB2D( const Vector2& aStart, const Vector2& aEnd, int64 aRadius, OBB* aOBB, Vector2& aCollisionPoint, int64& aCollisionPos)
{
    //先变换成AABB
    Vector2 center(aOBB->center.x, aOBB->center.z);
    Vector2 start(aStart.x - center.x, aStart.z - center.z);
    Vector2 end(aEnd.x - center.x, aEnd.z - center.z);
    int64 len = aOBB->right.Magnitude();

    int64 tmpX = Vector2::Dot(start, aOBB->right)/len;
    int64 tmpZ = Vector2::Dot(start, aOBB->front)/len;
    start.x = tmpX;
    start.z = tmpZ;

    tmpX = Vector2::Dot(end, aOBB->right)/len;
    tmpZ = Vector2::Dot(end, aOBB->front)/len;
    end.x = tmpX;
    end.z = tmpZ;

    AABB2D aabb;
    aabb.min = Vector2(-aOBB->halfSize.x,-aOBB->halfSize.z);
    aabb.max = Vector2( aOBB->halfSize.x, aOBB->halfSize.z);

    bool res = IntersectMovingSphereAABB2D( start, end, aRadius, &aabb, aCollisionPoint, aCollisionPos);

    Vector2 startToEnd( aEnd.x - aStart.x, aEnd.z - aStart.z);
    aCollisionPoint.x = aStart.x;
    aCollisionPoint.z = aStart.z;
    startToEnd.ScaleToLen(aCollisionPos);
    aCollisionPoint += startToEnd;

    return res;
}

int64 DetectSideLinePoint(const Vector2& aStart, const Vector2& aEnd, const Vector2& aPoint)
{
    //正数左，负数右边
    return (aStart.x - aPoint.x) * (aEnd.z - aPoint.z) - (aStart.z - aPoint.z) * (aEnd.x - aPoint.x);
}

bool IntersectSectorSphere2D(const Vector2& aSCenter, const Vector2& aDir, const int64 aHalfTheta, int64 aThetaBase,
 const int64 aSRadius, const Vector2& aCenter, int64 aRadius, Vector2& aCollisionPoint, int64& aCollisionPos)
{
    Vector2 right(aDir.x, aDir.z);
    Vector2 front(-aDir.z, aDir.x);
    Vector2 origFront(0, 100);
    Vector2 origRight(100, 0);
    int64 len = right.Magnitude();
    int64 origLen = 100;

    Vector2 center(aCenter.x - aSCenter.x, aCenter.z - aSCenter.z);  //转换圆心的坐标系

    int64 tmpX = Vector2::Dot(center, right)/len;
    int64 tmpZ = Vector2::Dot(center, front)/len;
    center.x = tmpX;
    center.z = tmpZ;
    bool flipped = false;
    if (center.z < 0)
    {
        center.z = -center.z;  //因为对称，可以只计算一半
        flipped = true;
    }

    tmpX = Vector2::Dot(origFront, right)/len;
    tmpZ = Vector2::Dot(origFront, front)/len;
    origFront.x = tmpX;
    origFront.z = tmpZ;
    tmpX = Vector2::Dot(origRight, right)/len;
    tmpZ = Vector2::Dot(origRight, front)/len;
    origRight.x = tmpX;
    origRight.z = tmpZ;

    //计算扇形右上角的顶点坐标，注意转换后的扇形圆心位于零点，正对x轴右侧方向
    //假设顶点坐标为<x, 100>,通过已知的cos(theta)和法向量right求解x的值
    int64 cosbase = 1000000;
    int64 cosval = CosineInt(aHalfTheta, aThetaBase, cosbase);
    tmpX = 0;
    tmpZ = 100;
    if (cosval * 100 / cosbase != 0) //认为小于0.01就等于0了
    {
        int64 cvp = cosval * cosval;
        tmpX = Sqrt( 10000 * cvp / (cosbase * cosbase - cvp) );
		if (cosval < 0)
		{
			tmpX = -tmpX;
		}
    }
    Vector2 upCorner(tmpX, tmpZ);
    upCorner.ScaleToLen(aSRadius);  //这是转换坐标后的一个扇形非圆心端点
    Vector2 downCorner(upCorner.x, -upCorner.z);  //和另一个端点沿x轴镜像对称
    Vector2 start(0, 0);

    int64 side = DetectSideLinePoint(start, upCorner, center);
    //cout << "side = " << side << endl;
    if (side <= 0)  //先考虑在右侧的情况
    {   //弧面相对，可以计算扇心与圆心连线同圆是否有交点
        if (center.Magnitude() <= aRadius + aSRadius)
        {
            if (!IntersectSegmentSphere2D(start, center, center, aRadius, aCollisionPoint, aCollisionPos))
            {
                return false;
            }
            Vector2 startToEnd(aCenter.x - aSCenter.x, aCenter.z - aSCenter.z);
            aCollisionPoint = aSCenter;
            startToEnd.ScaleToLen(aCollisionPos);
            aCollisionPoint += startToEnd;
        }
        else
        {
            return false;
        }
    }
    else  //否则计算扇形的斜边与园是否有交点
    {
        if (IntersectSegmentSphere2D(start, upCorner, center, aRadius, aCollisionPoint, aCollisionPos))
        {
            Vector2 startToEnd; //原坐标系中，扇形扇心到一端点的向量
            if (flipped)  //如果是反转过的，这里要用另一侧的腰线（x轴下方）
            {
                //先计算出原始坐标系下扇形的两个非圆心端点的坐标（圆心还是在0点）
                tmpX = Vector2::Dot(downCorner, origRight)/origLen;  //将碰撞点反转回去
                tmpZ = Vector2::Dot(downCorner, origFront)/origLen;
                startToEnd.x = tmpX;
                startToEnd.z = tmpZ;
            }
            else
            {
                tmpX = Vector2::Dot(upCorner, origRight)/origLen;
                tmpZ = Vector2::Dot(upCorner, origFront)/origLen;
                startToEnd.x = tmpX;
                startToEnd.z = tmpZ;
            }
            aCollisionPoint = aSCenter;
            startToEnd.ScaleToLen(aCollisionPos);
            aCollisionPoint += startToEnd;
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool IntersectSectorSphere(const Vector2& aSCenter, const Vector2& aRight, const Vector2& aFront, const Vector2& aLeftCorner, const Vector2& aRightCorner, const Vector2& aCenter, int64 aRadius, Vector2& aCollisionPoint, int64& aCollisionPos)
{
    Vector2 center(aCenter.x - aSCenter.x, aCenter.z - aSCenter.z);  //转换圆心的坐标系
    Vector2 right(aRight.x, aRight.z);
    int64 len = right.Magnitude();

    int64 tmpX = Vector2::Dot(center, aRight)/len;
    int64 tmpZ = Vector2::Dot(center, aFront)/len;
    center.x = tmpX;
    center.z = tmpZ;
    bool flipped = false;
    if (center.z < 0)
    {
        center.z = -center.z;  //因为对称，可以只计算一半
        flipped = true;
    }

    Vector2 end(aLeftCorner.x - aSCenter.x, aLeftCorner.z - aSCenter.z);  //转换扇形一角的坐标系
    tmpX = Vector2::Dot(end, aRight)/len;
    tmpZ = Vector2::Dot(end, aFront)/len;
    end.x = tmpX;
    end.z = tmpZ;

    Vector2 start(0, 0);
    int64 sectorRadius = end.Magnitude(); //扇形半径

    int64 side = DetectSideLinePoint(start, end, center);

    if (side <= 0)  //先考虑在右侧的情况
    {   //弧面相对，可以计算扇心与圆心连线同圆是否有交点
        if (center.Magnitude() <= aRadius + sectorRadius)
        {
            if (!IntersectSegmentSphere2D(start, center, center, aRadius, aCollisionPoint, aCollisionPos))
            {
                //cout <<"should not happen, need warning"<<endl;
                return false;
            }
            Vector2 startToEnd(aCenter.x - aSCenter.x, aCenter.z - aSCenter.z);
            aCollisionPoint = aSCenter;
            startToEnd.ScaleToLen(aCollisionPos);
            aCollisionPoint += startToEnd;
        }
        else
        {
            return false;
        }
    }
    else  //否则计算扇形的斜边与园是否有交点
    {
        if (IntersectSegmentSphere2D(start, end, center, aRadius, aCollisionPoint, aCollisionPos))
        {
            Vector2 startToEnd;
            if (flipped)  //如果是反转过的，这里要用右侧的腰线
            {
                startToEnd.x = aRightCorner.x - aSCenter.x;
                startToEnd.z = aRightCorner.z - aSCenter.z;
            }
            else
            {
                startToEnd.x = aLeftCorner.x - aSCenter.x;
                startToEnd.z = aLeftCorner.z - aSCenter.z;
            }
            aCollisionPoint = aSCenter;
            startToEnd.ScaleToLen(aCollisionPos);
            aCollisionPoint += startToEnd;
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool IntersectOBBSphere2D( const Vector2& aCenter, int64 aRadius, OBB* aOBB, Vector2& aCollisionPoint, int64& aCollisionPos)
{
    //先变换成AABB
    Vector2 centerOBB(aOBB->center.x, aOBB->center.z);
    Vector2 centerSphere(aCenter.x - centerOBB.x, aCenter.z - centerOBB.z);
    int64 len = aOBB->right.Magnitude();

    int64 tmpX = Vector2::Dot(centerSphere, aOBB->right)/len;
    int64 tmpZ = Vector2::Dot(centerSphere, aOBB->front)/len;
    centerSphere.x = tmpX;
    centerSphere.z = tmpZ;

    Vector2 origFront(0, 100);
    Vector2 origRight(100, 0);
    int64 origLen = 100;
    tmpX = Vector2::Dot(origFront, aOBB->right)/len;
    tmpZ = Vector2::Dot(origFront, aOBB->front)/len;
    origFront.x = tmpX;
    origFront.z = tmpZ;
    tmpX = Vector2::Dot(origRight, aOBB->right)/len;
    tmpZ = Vector2::Dot(origRight, aOBB->front)/len;
    origRight.x = tmpX;
    origRight.z = tmpZ;

    AABB2D aabb;
    aabb.min = Vector2(-aOBB->halfSize.x,-aOBB->halfSize.z);
    aabb.max = Vector2( aOBB->halfSize.x, aOBB->halfSize.z);

    bool res = IntersectMovingSphereAABB2D( centerSphere, centerSphere, aRadius, &aabb, aCollisionPoint, aCollisionPos);
    if (res == false)
    {
        return false;
    }

    tmpX = Vector2::Dot(aCollisionPoint, origRight)/origLen;  //将碰撞点反转回去
    tmpZ = Vector2::Dot(aCollisionPoint, origFront)/origLen;
    aCollisionPoint.x = tmpX + centerOBB.x;
    aCollisionPoint.z = tmpZ + centerOBB.z;

    return true;
}