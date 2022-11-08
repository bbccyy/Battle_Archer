
#include "CollisionDetection.h"
#include "Framework/Util.h"

bool IntersectRayAABB2D(const Vector2& aStart, const Vector2& aEnd, const AABB2D* aAABB, CollisionResults &aCollision)
{
    Vector2 startToEnd(aEnd.x - aStart.x, aEnd.z - aStart.z);
    int64 len = startToEnd.Magnitude();
    int64 tNear = INT64_MIN_VALUE;
    int64 tFar = INT64_MAX_VALUE;

    for (int i = 0; i < 2; i++)
    {
        //平行与当前轴的垂直面(x-slab) 
        if (startToEnd[i] == 0)
        {
            if (aStart[i] < aAABB->min[i] || aStart[i] > aAABB->max[i])
            {
                return false;
            }
        }
        else
        {

            //本来应该是( aAABB->min[i] - aStart[i] )/startToEnd[i]; 考虑精度问题，我们使用长度，不使用比例 
            int64 t1 = (aAABB->min[i] - aStart[i]) * len / startToEnd[i];
            int64 t2 = (aAABB->max[i] - aStart[i]) * len / startToEnd[i];

            if (t1 > t2)
            {
                std::swap(t1, t2);
            }
            tNear = std::max(tNear, t1);
            tFar = std::min(tFar, t2);
            if (tNear > tFar)
            {
                return false;
            }

        }
    }
    aCollision.CollisionPos = tNear;
    aCollision.CollisionPoint = aStart;
    startToEnd.ScaleToLen(tNear);
    aCollision.CollisionPoint += startToEnd;

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

bool IntersectSegmentSegment2D(const Vector2& aPoint11, const Vector2& aPoint12, const Vector2& aPoint21, const Vector2& aPoint22, CollisionResults &aCollision)
{
    //p,p+r; q,q+s 分别是线段A,B的两个端点 
    //https://stackoverflow.com/questions/563198
    Vector2 p(aPoint11.x, aPoint11.z);
    Vector2 r(aPoint12.x - aPoint11.x, aPoint12.z - aPoint11.z);
    Vector2 q(aPoint21.x, aPoint21.z);
    Vector2 s(aPoint22.x - aPoint21.x, aPoint22.z - aPoint21.z);

    Vector2 p2q(q.x - p.x, q.z - p.z);
    int64 rs = Vector2::Cross(r, s);
    int64 rr = Vector2::Dot(r, r);
    int64 p2qCr = Vector2::Cross(p2q, r);

    if (rs == 0 && p2qCr == 0)  //case 1: colinear 共线 
    {
        int64 t0 = Vector2::Dot(p2q, r);  //降到1维去比较 
        int64 t1 = Vector2::Dot(s, r) + t0;
        if (Vector2::Dot(s, r) >= 0)  //s 和 r 同向, 考察[t0, t1] 与 [0, Dot(r,r)]是否有重叠, p点是0点 
        {
            if (t1 <0 || t0 > rr)
            {
				RestoreObjToPool(p);
				RestoreObjToPool(r);
				RestoreObjToPool(q);
				RestoreObjToPool(s);
				RestoreObjToPool(p2q);
                return false;
            }
            else
            {
                //将重合部分的中心点作为交点返回 
                if (t0 < 0)
                {
                    if (t1 <= rr)  //t0 -> p -> t1 -> p+r
                    {
                        //重合部分的中点 
                        aCollision.CollisionPoint.x = (aPoint11.x + aPoint22.x) / 2;
                        aCollision.CollisionPoint.z = (aPoint11.z + aPoint22.z) / 2;
                    }
                    else   //t0 -> p -> p+r -> t1
                    {
                        aCollision.CollisionPoint.x = (aPoint11.x + aPoint12.x) / 2;
                        aCollision.CollisionPoint.z = (aPoint11.z + aPoint12.z) / 2;
                    }
                }
                else //t0 <= rr
                {
                    if (t1 <= rr)  //p -> t0 -> t1 -> p+r
                    {
                        aCollision.CollisionPoint.x = (aPoint21.x + aPoint22.x) / 2;
                        aCollision.CollisionPoint.z = (aPoint21.z + aPoint22.z) / 2;
                    }
                    else   //p -> t0 -> p+r -> t1
                    {
                        aCollision.CollisionPoint.x = (aPoint21.x + aPoint12.x) / 2;
                        aCollision.CollisionPoint.z = (aPoint21.z + aPoint12.z) / 2;
                    }
                }
				RestoreObjToPool(p);
				RestoreObjToPool(r);
				RestoreObjToPool(q);
				RestoreObjToPool(s);
				RestoreObjToPool(p2q);
                return true;  //overlap
            }
        }
        else  //s 和 r 反向, 考察[t1, t0] 与 [0, Dot(r,r)]是否有重叠 
        {
            if (t0 <0 || t1 > rr)
            {
				RestoreObjToPool(p);
				RestoreObjToPool(r);
				RestoreObjToPool(q);
				RestoreObjToPool(s);
				RestoreObjToPool(p2q);
                return false;
            }
            else
            {
                if (t1 < 0)
                {
                    if (t0 <= rr)  //t1 -> p -> t0 -> p+r
                    {
                        aCollision.CollisionPoint.x = (aPoint11.x + aPoint21.x) / 2;
                        aCollision.CollisionPoint.z = (aPoint11.z + aPoint21.z) / 2;
                    }
                    else   //t1 -> p -> p+r -> t0
                    {
                        aCollision.CollisionPoint.x = (aPoint11.x + aPoint12.x) / 2;
                        aCollision.CollisionPoint.z = (aPoint11.z + aPoint12.z) / 2;
                    }
                }
                else    // t1 <= rr
                {
                    if (t0 <= rr)  //p -> t1 -> t0 -> p+r
                    {
                        aCollision.CollisionPoint.x = (aPoint22.x + aPoint21.x) / 2;
                        aCollision.CollisionPoint.z = (aPoint22.z + aPoint21.z) / 2;
                    }
                    else   //p -> t1 -> p+r -> t0
                    {
                        aCollision.CollisionPoint.x = (aPoint22.x + aPoint12.x) / 2;
                        aCollision.CollisionPoint.z = (aPoint22.z + aPoint12.z) / 2;
                    }
                }
				RestoreObjToPool(p);
				RestoreObjToPool(r);
				RestoreObjToPool(q);
				RestoreObjToPool(s);
				RestoreObjToPool(p2q);
                return true;  //overlap
            }
        }
    }
    else if (rs == 0 && p2qCr != 0)  //case 2: parallel 平行 
    {
		RestoreObjToPool(p);
		RestoreObjToPool(r);
		RestoreObjToPool(q);
		RestoreObjToPool(s);
		RestoreObjToPool(p2q);
        return false;
    }

    //t = p2q x s / (r x s),  u = p2q x r / (r x s)
    int64 t = Vector2::Cross(p2q, s);  //这里的t只是分子 
    int64 u = Vector2::Cross(p2q, r);
    int64 rCs = Vector2::Cross(r, s);  //这是公共分母 

    if (rCs != 0)
    {
        if ( (t<0) != (rCs<0) || (u<0) != (rCs<0))  //分子分母异号的话，结果肯定<0 
        {
			RestoreObjToPool(p);
			RestoreObjToPool(r);
			RestoreObjToPool(q);
			RestoreObjToPool(s);
			RestoreObjToPool(p2q);
            return false;
        }

        if ((t == rCs || t / rCs == 0) && (u == rCs || u / rCs == 0))  //表示t和u的绝对值不能大于|r x c|的绝对值 
        {
            aCollision.CollisionPoint.x = p.x;
            aCollision.CollisionPoint.z = p.z;

			if ((t > DENOM_SQR || t < -DENOM_SQR) && (rCs > DENOM_SQR || rCs < -DENOM_SQR))
			{
				t = t / DENOM;
				rCs = rCs / DENOM;
			}

            Vector2 dir(r.x, r.z);
			int64 len = dir.Magnitude() * t;
			len = len / rCs;
            dir.ScaleToLen(len);

            aCollision.CollisionPoint += dir;

			RestoreObjToPool(p);
			RestoreObjToPool(r);
			RestoreObjToPool(q);
			RestoreObjToPool(s);
			RestoreObjToPool(p2q);
			RestoreObjToPool(dir);
            return true;
        }
    }

	RestoreObjToPool(p);
	RestoreObjToPool(r);
	RestoreObjToPool(q);
	RestoreObjToPool(s);
	RestoreObjToPool(p2q);
    return false;
}

bool IntersectSegmentAABB2D(const Vector2& aStart, const Vector2& aEnd, const AABB2D* aAABB, CollisionResults &aCollision)
{
    bool containStart = ContainPointAABB2D(aStart, aAABB); //首先判断首尾点的情况，是否在AABB内 
    bool containEnd = ContainPointAABB2D(aEnd, aAABB);
    if (containStart && containEnd)  //两者都在AABB内，属于特殊情况，直接返回 
    {
        aCollision.CollisionPos = 0;
        aCollision.CollisionPoint.Set(aStart);
        return true;
    }

    Vector2 startToEnd(aEnd.x - aStart.x, aEnd.z - aStart.z);
    int64 len = startToEnd.Magnitude();
    int64 tNear = INT64_MIN_VALUE;
    int64 tFar = INT64_MAX_VALUE;
    int Count = 0;  //在线段的范围内，与slab边界线及其衍生线相交的次数 

    for (int i = 0; i < 2; i++)
    {
        //平行与当前轴 
        if (startToEnd[i] == 0)
        {
            if (aStart[i] < aAABB->min[i] || aStart[i] > aAABB->max[i])
            {
				RestoreObjToPool(startToEnd);
                return false;
            }
        }
        else
        {
            int64 t1 = (aAABB->min[i] - aStart[i]) * len / startToEnd[i];
            int64 t2 = (aAABB->max[i] - aStart[i]) * len / startToEnd[i];
            if (t1 >= 0 && t1 <= len)
            {
                Count++;
            }
            if (t2 >= 0 && t2 <= len)
            {
                Count++;
            }
            if (t1 > t2)
            {
                std::swap(t1, t2);
            }
            tNear = std::max(tNear, t1);
            tFar = std::min(tFar, t2);
            if (tNear > tFar)
            {
				RestoreObjToPool(startToEnd);
                return false;
            }
        }
    }
    if (Count == 0)
    { //没有焦点在线段范围内，不相交 
		RestoreObjToPool(startToEnd);
        return false;
    }
    if (Count == 1)
    {  //只有一个焦点在线段范围内 
        if (containStart)
        {
            //aCollisionPos = tFar;  //start点在AABB内，但是end在外的情况，焦点其实是由tFar表示的 
            aCollision.CollisionPos = 0;  //希望让startPoint来表示碰撞点 
        }
        else if (containEnd)
        {
            aCollision.CollisionPos = tNear;
        }
        else
        {
			RestoreObjToPool(startToEnd);
            return false; //首尾两点都不在AABB内，且只有1个焦点在线段范围内，这种情况不可能相交 
        }
    }
    else
    {  //拥有2个或2个以上的焦点处在线段自身范围内，且“射线”与AABB相交，则“线段”必定与之相交 
        if (containStart)
        {
            aCollision.CollisionPos = tFar;
        }
        else
        {
            aCollision.CollisionPos = tNear;
        }
    }

    aCollision.CollisionPoint.Set(aStart);
    startToEnd.ScaleToLen(aCollision.CollisionPos);
    aCollision.CollisionPoint += startToEnd;
	RestoreObjToPool(startToEnd);
    return true;
}


bool IntersectSegmentSphere2D(const Vector2& aStart, const Vector2& aEnd, Vector2 aCenter, int64 aRadius, CollisionResults &aCollision)
{
    int64 r2 = aRadius * aRadius;    
    Vector2 centerToStart(aStart.x - aCenter.x, aStart.z - aCenter.z);  //f
                                                                        //起点在圆内或圆上 
    int64 c = centerToStart.Magnitude2() - r2; //c
    if (c <= 0)
    {
        aCollision.CollisionPos = 0;
        aCollision.CollisionPoint = aStart;
        RestoreObjToPool(centerToStart);
        return true;
    }
    if (aStart == aEnd)  //如果线段只是一个点，不在园内就不可能相交了 
    {
        RestoreObjToPool(centerToStart);
        return false;
    }
    Vector2 centerToEnd(aEnd.x - aCenter.x, aEnd.z - aCenter.z);
    int64 centerToEndLen = centerToEnd.Magnitude2();
    RestoreObjToPool(centerToEnd);
    if ( centerToEndLen <= r2)
    {
        aCollision.CollisionPos = 1;
        aCollision.CollisionPoint = aEnd;
        RestoreObjToPool(centerToStart);
        return true;
    }

    Vector2 startToEnd(aEnd.x - aStart.x, aEnd.z - aStart.z);  //d
    int64 lineMag2 = startToEnd.Magnitude2(); //a

    int64 product = Vector2::Dot(startToEnd, centerToStart); //b/2
    bool scaleDown = lineMag2 > DENOM_SQR || product > DENOM_SQR || product < -DENOM_SQR || c > DENOM_SQR;
                                                             //https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
                                                             //https://stackoverflow.com/questions/1073336/circle-line-segment-collision-detection-algorithm
    RestoreObjToPool(centerToStart);
    int64 discriminant;
    if (scaleDown)
    {
        if (lineMag2 > DENOM_SQR)
        {
            discriminant = product * (product / DENOM_SQR) - (lineMag2 / DENOM_SQR) * c;  // b^2/4 - ac
        }
        else
        {
            discriminant = product * (product / DENOM_SQR) - (c / DENOM_SQR) * lineMag2;  // b^2/4 - ac
        }
    }
    else
    {
        discriminant = product * product - lineMag2 * c;  // b^2/4 - ac
    }
    if (discriminant < 0)
    {
        RestoreObjToPool(startToEnd);
        return false; //两点都在园外，且公式无解，不相交 
    }

    int64 numerator1;
    if (scaleDown)
    {
        numerator1 = -product - Sqrt(discriminant) * DENOM;
    }
    else
    {
        numerator1 = -product - Sqrt(discriminant);
    }

    if (numerator1 < 0)
    {
        aCollision.CollisionPos = 0;
        RestoreObjToPool(startToEnd);
        return false;
    }
    if (numerator1 > DENOM_SQR &&  lineMag2 > DENOM_SQR)
    {
        aCollision.CollisionPos = Sqrt(lineMag2) * (numerator1 / DENOM_SQR) / (lineMag2 / DENOM_SQR);
    }
    else
    {
        aCollision.CollisionPos = Sqrt(lineMag2) * numerator1 / lineMag2;
    }

    if (startToEnd.Magnitude() < aCollision.CollisionPos)
    {
        RestoreObjToPool(startToEnd);
        return false;
    }

    aCollision.CollisionPoint.Set(aStart);
    startToEnd.ScaleToLen(aCollision.CollisionPos);
    aCollision.CollisionPoint += startToEnd;
    RestoreObjToPool(startToEnd);
    return true;
}

bool IntersectMovingSphereAABB2D(const Vector2& aStart, const Vector2& aEnd, int64 aRadius, const AABB2D* aAABB, CollisionResults &aCollision)
{
    //首先判断起点是否已经在目标AABB内 
    if (ContainPointAABB2D(aStart, aAABB))
    {
        aCollision.CollisionPoint.Set(aStart);
        aCollision.CollisionPos = 0;
        return true;
    }

    AABB2D e = *aAABB;
    e.min.x -= aRadius;
    e.max.x += aRadius;
    e.min.z -= aRadius;
    e.max.z += aRadius;

    //判断是否和外包的矩形相交，不相交则Sphere和AABB没有相交的可能 
    if (!IntersectSegmentAABB2D(aStart, aEnd, &e, aCollision))
    {
		RestoreObjToPool(e);
        return false;
    }

    Vector2 point = aCollision.CollisionPoint;
    Vector2 sideCenter;
    int mark = 0;

    //判断交点的落点，决定是否要对矩形的某个角作二次检查 
    if (point.x < aAABB->min.x)
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
    else if (point.x > aAABB->max.x)
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

    if (point.z < aAABB->min.z)
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
    else if (point.z > aAABB->max.z)
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

    if (mark == 0) //与四个角之一相交，需要二次检测 
    {
        if (!IntersectSegmentSphere2D(aStart, aEnd, sideCenter, aRadius, aCollision))
        {
			RestoreObjToPool(point);
			RestoreObjToPool(sideCenter);
			RestoreObjToPool(e);
            return false;
        }
        aCollision.CollisionPoint.Set(sideCenter);  //这种情况交点就是4个角中的一个 
    }
    else
    {
        aCollision.CollisionPos += aRadius;  //修正pos，之前的pos只是圆心的位置，所以要补上半径部分 
        aCollision.CollisionPoint.Set(point);
        switch (mark)  //真正的交点需要视情况作上下左右修正，交点必然在外立面上 
        {
        case 1:
            aCollision.CollisionPoint.x = aAABB->min.x;
            break;
        case 2:
            aCollision.CollisionPoint.x = aAABB->max.x;
            break;
        case 3:
            aCollision.CollisionPoint.z = aAABB->min.z;
            break;
        case 4:
            aCollision.CollisionPoint.z = aAABB->max.z;
            break;
        default:
            break;
        }
    }

	RestoreObjToPool(point);
	RestoreObjToPool(sideCenter);
	RestoreObjToPool(e);
    return true;
}

bool IntersectMovingSphereSphere2D(const Vector2& aStart, const Vector2& aEnd, int64 aRadius, const Cylinder* aCylinder, CollisionResults &aCollision)
{
    Vector2 start(aStart.x, aStart.z);
    Vector2 end(aEnd.x, aEnd.z);
    Vector2 center(aCylinder->center.x, aCylinder->center.z);
    bool ret = IntersectSegmentSphere2D(start, end, center, aCylinder->radius + aRadius, aCollision);
    RestoreObjToPool(start);
    RestoreObjToPool(end);
    RestoreObjToPool(center);
    return ret;
}

bool IntersectMovingSphereOBB2D(const Vector2& aStart, const Vector2& aEnd, int64 aRadius, OBB* aOBB, CollisionResults &aCollision)
{
    //先变换成AABB 
    Vector2 center(aOBB->center.x, aOBB->center.z);
    Vector2 start(aStart.x - center.x, aStart.z - center.z);
    Vector2 end(aEnd.x - center.x, aEnd.z - center.z);
    int64 len = aOBB->right.Magnitude();
	LOG_ASSERT(len > 0);

    int64 tmpX = Vector2::Dot(start, aOBB->right) / len;
    int64 tmpZ = Vector2::Dot(start, aOBB->front) / len;
    start.x = tmpX;
    start.z = tmpZ;

    tmpX = Vector2::Dot(end, aOBB->right) / len;
    tmpZ = Vector2::Dot(end, aOBB->front) / len;
    end.x = tmpX;
    end.z = tmpZ;

    AABB2D aabb;
    aabb.min.Set(-aOBB->halfSize.x, -aOBB->halfSize.z);
    aabb.max.Set(aOBB->halfSize.x, aOBB->halfSize.z);

    bool res = IntersectMovingSphereAABB2D(start, end, aRadius, &aabb, aCollision);

    Vector2 startToEnd(aEnd.x - aStart.x, aEnd.z - aStart.z);
    aCollision.CollisionPoint.x = aStart.x;
    aCollision.CollisionPoint.z = aStart.z;
    startToEnd.ScaleToLen(aCollision.CollisionPos);
    aCollision.CollisionPoint += startToEnd;
	RestoreObjToPool(aabb);
	RestoreObjToPool(startToEnd);
	RestoreObjToPool(start);
	RestoreObjToPool(center);
	RestoreObjToPool(end);
    return res;
}

int64 DetectSideLinePoint(const Vector2& aStart, const Vector2& aEnd, const Vector2& aPoint)
{
    //正数左，负数右边 
    return (aStart.x - aPoint.x) * (aEnd.z - aPoint.z) - (aStart.z - aPoint.z) * (aEnd.x - aPoint.x);
}

bool IntersectSectorSphere2D(const Vector2& aSCenter, const Vector2& aDir, const int64 aHalfTheta, int64 aThetaBase,
    const int64 aSRadius, const Vector2& aCenter, int64 aRadius, CollisionResults &aCollision)
{
    Vector2 right(aDir.x, aDir.z);
    Vector2 front(-aDir.z, aDir.x);
    Vector2 origFront(0, 100);
    Vector2 origRight(100, 0);
    int64 len = right.Magnitude();
    int64 origLen = 100;

	if(len == 0) return false;

    Vector2 center(aCenter.x - aSCenter.x, aCenter.z - aSCenter.z);  //转换圆心的坐标系 

    int64 tmpX = Vector2::Dot(center, right) / len;
    int64 tmpZ = Vector2::Dot(center, front) / len;
    center.x = tmpX;
    center.z = tmpZ;
    bool flipped = false;
    if (center.z < 0)
    {
        center.z = -center.z;  //因为对称，可以只计算一半 
        flipped = true;
    }

    tmpX = Vector2::Dot(origFront, right) / len;
    tmpZ = Vector2::Dot(origFront, front) / len;
    origFront.x = tmpX;
    origFront.z = tmpZ;
    tmpX = Vector2::Dot(origRight, right) / len;
    tmpZ = Vector2::Dot(origRight, front) / len;
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
        tmpX = Sqrt(10000 * cvp / (cosbase * cosbase - cvp));
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
            if (!IntersectSegmentSphere2D(start, center, center, aRadius, aCollision))
            {
                return false;
            }
            Vector2 startToEnd(aCenter.x - aSCenter.x, aCenter.z - aSCenter.z);
            aCollision.CollisionPoint.Set(aSCenter);
            startToEnd.ScaleToLen(aCollision.CollisionPos);
            aCollision.CollisionPoint += startToEnd;
        }
        else
        {
            return false;
        }
    }
    else  //否则计算扇形的斜边与园是否有交点 
    {
        if (IntersectSegmentSphere2D(start, upCorner, center, aRadius, aCollision))
        {
            Vector2 startToEnd; //原坐标系中，扇形扇心到一端点的向量 
            if (flipped)  //如果是反转过的，这里要用另一侧的腰线（x轴下方） 
            {
                //先计算出原始坐标系下扇形的两个非圆心端点的坐标（圆心还是在0点） 
                tmpX = Vector2::Dot(downCorner, origRight) / origLen;  //将碰撞点反转回去 
                tmpZ = Vector2::Dot(downCorner, origFront) / origLen;
                startToEnd.x = tmpX;
                startToEnd.z = tmpZ;
            }
            else
            {
                tmpX = Vector2::Dot(upCorner, origRight) / origLen;
                tmpZ = Vector2::Dot(upCorner, origFront) / origLen;
                startToEnd.x = tmpX;
                startToEnd.z = tmpZ;
            }
            aCollision.CollisionPoint.Set(aSCenter);
            startToEnd.ScaleToLen(aCollision.CollisionPos);
            aCollision.CollisionPoint += startToEnd;
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool IntersectOBBSphere2D(const Vector2& aCenter, int64 aRadius, OBB* aOBB, CollisionResults &aCollision)
{
    //先变换成AABB 
    Vector2 centerOBB(aOBB->center.x, aOBB->center.z);
    Vector2 centerSphere(aCenter.x - centerOBB.x, aCenter.z - centerOBB.z);
    int64 len = aOBB->right.Magnitude();
	if (len == 0) return false;

    int64 tmpX = Vector2::Dot(centerSphere, aOBB->right) / len;
    int64 tmpZ = Vector2::Dot(centerSphere, aOBB->front) / len;
    centerSphere.x = tmpX;
    centerSphere.z = tmpZ;

    Vector2 origFront(0, 100);
    Vector2 origRight(100, 0);
    int64 origLen = 100;
    tmpX = Vector2::Dot(origFront, aOBB->right) / len;
    tmpZ = Vector2::Dot(origFront, aOBB->front) / len;
    origFront.x = tmpX;
    origFront.z = tmpZ;
    tmpX = Vector2::Dot(origRight, aOBB->right) / len;
    tmpZ = Vector2::Dot(origRight, aOBB->front) / len;
    origRight.x = tmpX;
    origRight.z = tmpZ;

    AABB2D aabb; 
    aabb.min.Set(-aOBB->halfSize.x, -aOBB->halfSize.z); 
    aabb.max.Set(aOBB->halfSize.x, aOBB->halfSize.z); 

    bool res = IntersectMovingSphereAABB2D(centerSphere, centerSphere, aRadius, &aabb, aCollision);
    if (res == false)
    {
		RestoreObjToPool(centerOBB);
		RestoreObjToPool(centerSphere);
		RestoreObjToPool(origFront);
		RestoreObjToPool(origRight);
		RestoreObjToPool(aabb);
        return false;
    }

    tmpX = Vector2::Dot(aCollision.CollisionPoint, origRight) / origLen;  //将碰撞点反转回去 
    tmpZ = Vector2::Dot(aCollision.CollisionPoint, origFront) / origLen;
    aCollision.CollisionPoint.x = tmpX + centerOBB.x;
    aCollision.CollisionPoint.z = tmpZ + centerOBB.z;

	RestoreObjToPool(centerOBB);
	RestoreObjToPool(centerSphere);
	RestoreObjToPool(origFront);
	RestoreObjToPool(origRight);
	RestoreObjToPool(aabb);
    return true;
}

bool IntersectOBBOBBoneside(OBB* aOBB1, OBB* aOBB2)
{
    Vector2 center2(aOBB2->center.x - aOBB1->center.x, aOBB2->center.z - aOBB1->center.z);
    int64 len1 = aOBB1->right.Magnitude();
    Vector2 right2(Vector2::Dot(aOBB2->right, aOBB1->right) / len1, Vector2::Dot(aOBB2->right, aOBB1->front) / len1); //转换到OBB1坐标系后，OBB2的正方向 
    Vector2 front2(Vector2::Dot(aOBB2->front, aOBB1->right) / len1, Vector2::Dot(aOBB2->front, aOBB1->front) / len1);
    Vector2 center21(Vector2::Dot(center2, aOBB1->right) / len1, Vector2::Dot(center2, aOBB1->front) / len1);  //同上，转换之后的OBB2的中心点 
    right2.ScaleToLen(aOBB2->halfSize.x);
    front2.ScaleToLen(aOBB2->halfSize.z);

    Vector2 minP(INT64_MAX_VALUE, INT64_MAX_VALUE);
    Vector2 maxP(INT64_MIN_VALUE, INT64_MIN_VALUE);
    for (int i = 0; i<4; i++)  //计算OBB2的4个顶点投影在x和z轴上的最小值与最大值 
    {
        int64 x = 0, z = 0;
        if ((i & 1) > 0)
        {
            x += right2.x;
            z += right2.z;
        }
        else
        {
            x -= right2.x;
            z -= right2.z;
        }

        if ((i & 2) > 0)
        {
            x += front2.x;
            z += front2.z;
        }
        else
        {
            x -= front2.x;
            z -= front2.z;
        }

        minP.x = std::min(minP.x, x);
        minP.z = std::min(minP.z, z);

        maxP.x = std::max(maxP.x, x);
        maxP.z = std::max(maxP.z, z);
    }

    minP += center21;  //修正位置 
    maxP += center21;

    if (aOBB1->halfSize.x < minP.x || -aOBB1->halfSize.x > maxP.x)
    {
        return false;
    }

    if (aOBB1->halfSize.z < minP.z || -aOBB1->halfSize.z > maxP.z)
    {
        return false;
    }

    return true;
}

bool IntersectOBBOBB2D(OBB* aOBB1, OBB* aOBB2)
{
    if (IntersectOBBOBBoneside(aOBB1, aOBB2) == false)
    {
        return false;
    }
    else if (IntersectOBBOBBoneside(aOBB2, aOBB1) == false)
    {
        return false;
    }
    return true;
}

bool IntersectOBBOBBwithCollisionPointOneside(OBB* aOBB1, OBB* aOBB2, CollisionResults &aCollision, bool isSecond)
{
    //只以aOBB1为基准，计算aOBB2对aOBB1的碰撞点 
    int64 len1 = aOBB1->right.Magnitude();
    Vector2 right2(Vector2::Dot(aOBB2->right, aOBB1->right) / len1, Vector2::Dot(aOBB2->right, aOBB1->front) / len1); //转换到OBB1坐标系后，OBB2的正方向 
    Vector2 front2(Vector2::Dot(aOBB2->front, aOBB1->right) / len1, Vector2::Dot(aOBB2->front, aOBB1->front) / len1);

    Vector2 center2(aOBB2->center.x - aOBB1->center.x, aOBB2->center.z - aOBB1->center.z);
    Vector2 center21(Vector2::Dot(center2, aOBB1->right) / len1, Vector2::Dot(center2, aOBB1->front) / len1);  //同上，转换之后的OBB2的中心点 

    Vector2 origFront(0, 100);
    Vector2 origRight(100, 0);
    int64 origLen = 100;
    int64 tmpX = Vector2::Dot(origFront, aOBB1->right) / len1;
    int64 tmpZ = Vector2::Dot(origFront, aOBB1->front) / len1;
    origFront.x = tmpX;
    origFront.z = tmpZ;
    tmpX = Vector2::Dot(origRight, aOBB1->right) / len1;
    tmpZ = Vector2::Dot(origRight, aOBB1->front) / len1;
    origRight.x = tmpX;
    origRight.z = tmpZ;

    right2.ScaleToLen(aOBB2->halfSize.x);
    front2.ScaleToLen(aOBB2->halfSize.z);

    AABB2D aabb;
    aabb.min.Set(-aOBB1->halfSize.x, -aOBB1->halfSize.z);
    aabb.max.Set(aOBB1->halfSize.x, aOBB1->halfSize.z);

    Vector2 corners[5];
    corners[0] = Vector2(-right2.x - front2.x + center21.x, -right2.z - front2.z + center21.z);
    corners[1] = Vector2(right2.x - front2.x + center21.x, right2.z - front2.z + center21.z);
    corners[2] = Vector2(right2.x + front2.x + center21.x, right2.z + front2.z + center21.z);
    corners[3] = Vector2(-right2.x + front2.x + center21.x, -right2.z + front2.z + center21.z);
    corners[4] = Vector2(-right2.x - front2.x + center21.x, -right2.z - front2.z + center21.z);

    bool find = false;

    int indoor[5] = { 0,0,0,0,0 };
    for (int i = 1; i<5; i++)
    {
        if (ContainPointAABB2D(corners[i], &aabb))
        {
            indoor[i] = 1;
        }
    }

    int ct = 0;
    for (int i = 1; i<5; i++)
    {
        ct += indoor[i];
    }

    if (ct == 1)  //只有1个点在AABB中，取与这点相邻2边与AABB的交点的连线的中点 
    {
        int idx1 = 1;
        for (int i = 1; i<5; i++)
        {
            if (indoor[i] > 0)
            {
                idx1 = i;
                break;
            }
        }
        Vector2 AO = corners[idx1];
        Vector2 AL = corners[idx1 - 1];
        Vector2 AR = corners[(idx1 + 1) % 4];

        CollisionResults extra1, extra2;

        IntersectSegmentAABB2D(AO, AL, &aabb, extra1);
        IntersectSegmentAABB2D(AO, AR, &aabb, extra2);
        aCollision.CollisionPoint.x = (extra1.CollisionPoint.x + extra2.CollisionPoint.x) / 2;
        aCollision.CollisionPoint.z = (extra1.CollisionPoint.z + extra2.CollisionPoint.z) / 2;
        find = true;
		RestoreObjToPool(AO);
		RestoreObjToPool(AL);
		RestoreObjToPool(AR);
    }
    else if (ct == 2)  //有2个点在AABB中，取内部2点连线的中点 
    {
        int idx1 = 0, idx2 = 0;
        for (int i = 1; i<5; i++)
        {
            if (indoor[i] > 0)
            {
                if (idx1 == 0)
                {
                    idx1 = i;
                }
                else
                {
                    idx2 = i;
                    break;
                }
            }
        }
        Vector2 A = corners[idx1];
        Vector2 B = corners[idx2];

        aCollision.CollisionPoint.x = (A.x + B.x) / 2;
        aCollision.CollisionPoint.z = (A.z + B.z) / 2;
        find = true;
		RestoreObjToPool(A);
		RestoreObjToPool(B);
    }
    else if (ct == 3)  //有3个点在AABB中，取不在AABB中那点的2条临边与AABB的交点的连线中点 
    {
        int idx1 = 1;
        for (int i = 1; i<5; i++)
        {
            if (indoor[i] == 0)
            {
                idx1 = i;
                break;
            }
        }
        Vector2 AO = corners[idx1];
        Vector2 AL = corners[idx1 - 1];
        Vector2 AR = corners[(idx1 + 1) % 4];

        CollisionResults extra1, extra2;

        IntersectSegmentAABB2D(AO, AL, &aabb, extra1);
        IntersectSegmentAABB2D(AO, AR, &aabb, extra2);
        aCollision.CollisionPoint.x = (extra1.CollisionPoint.x + extra2.CollisionPoint.x) / 2;
        aCollision.CollisionPoint.z = (extra1.CollisionPoint.z + extra2.CollisionPoint.z) / 2;
        find = true;
		RestoreObjToPool(AO);
		RestoreObjToPool(AL);
		RestoreObjToPool(AR);
    }
    else if (ct == 4)  //4个点全部在AABB中, 取任意对角线中点 
    {
        Vector2 A = corners[1];
        Vector2 B = corners[3];

        aCollision.CollisionPoint.x = (A.x + B.x) / 2;
        aCollision.CollisionPoint.z = (A.z + B.z) / 2;
        find = true;
		RestoreObjToPool(A);
		RestoreObjToPool(B);
    }
    else  //没有点在AABB中 
    {
        if (isSecond) //两个OBB互相没有点在彼此内部 
        {
            Vector2 point1, point2;
            CollisionResults extra;
            int ctr = 0;
            for (int i = 1; i<5; i++)
            {
                if (IntersectSegmentAABB2D(corners[i], corners[(i + 1) % 4], &aabb, extra))
                {
                    if (ctr == 0)
                    {
                        point1.x = extra.CollisionPoint.x;
                        point1.z = extra.CollisionPoint.z;
                        ctr++;
                    }
                    else
                    {
                        point2.x = extra.CollisionPoint.x;
                        point2.z = extra.CollisionPoint.z;
                        ctr++;
                        break;
                    }
                }
            }
            if (ctr == 2)
            {
                aCollision.CollisionPoint.x = (point1.x + point2.x) / 2;
                aCollision.CollisionPoint.z = (point1.z + point2.z) / 2;
                find = true;
            }
			RestoreObjToPool(point1);
			RestoreObjToPool(point2);
        }
        else
        {
			RestoreObjToPool(aabb);
            return false; //obb2对于obb1来说，没有任何点在内部，需要对调下2个obb再算一次 
        }
    }

    if (!find)
    {
		RestoreObjToPool(aabb);
        return false;
    }

    tmpX = Vector2::Dot(aCollision.CollisionPoint, origRight) / origLen;  //将碰撞点反转回去 
    tmpZ = Vector2::Dot(aCollision.CollisionPoint, origFront) / origLen;
    aCollision.CollisionPoint.x = tmpX + aOBB1->center.x;
    aCollision.CollisionPoint.z = tmpZ + aOBB1->center.z;
	RestoreObjToPool(aabb);
    return true;

}

bool IntersectOBBOBB2D(OBB* aOBB1, OBB* aOBB2, CollisionResults &aCollision)
{
    if (IntersectOBBOBBwithCollisionPointOneside(aOBB1, aOBB2, aCollision, false))
    {
        return true;
    }
    else if (IntersectOBBOBBwithCollisionPointOneside(aOBB2, aOBB1, aCollision, true))
    {
        return true;
    }
    return false;
}

bool IntersectRingSphere2D(const Vector2& aCenter, int64 aRadius, const Vector2& aRingCenter, int64 aRadiusMin, int64 aRadiusMax)
{
    Vector2 RingToCenter(aCenter.x - aRingCenter.x, aCenter.z - aRingCenter.z);
    int64 len = RingToCenter.Magnitude();
    if (len < aRadiusMin - aRadius)
    {
        return false;
    }

    if (len > aRadiusMax + aRadius)
    {
        return false;
    }

    return true;
}

bool IntersectRingSphere2D(const Vector2& aCenter, int64 aRadius, const Vector2& aRingCenter, int64 aRadiusMin, int64 aRadiusMax, CollisionResults &aCollision)
{
    Vector2 RingToCenter(aCenter.x - aRingCenter.x, aCenter.z - aRingCenter.z);
    int64 len = RingToCenter.Magnitude();
    if (len < aRadiusMin - aRadius)
    {
        return false;
    }

    if (len > aRadiusMax + aRadius)
    {
        return false;
    }

    if (len <= aRadiusMax && len >= aRadiusMin)
    {
        aCollision.CollisionPoint.x = aCenter.x;
        aCollision.CollisionPoint.z = aCenter.z;
        return true;
    }

    if (len < aRadiusMin)
    {
        if (len == 0)
        {
            RingToCenter.x = 100;
        }
        RingToCenter.ScaleToLen(aRadiusMin);
        RingToCenter += aRingCenter;
        aCollision.CollisionPoint.x = RingToCenter.x;
        aCollision.CollisionPoint.z = RingToCenter.z;
        return true;
    }

    if (len > aRadiusMax)
    {
        RingToCenter.ScaleToLen(aRadiusMax);
        RingToCenter += aRingCenter;
        aCollision.CollisionPoint.x = RingToCenter.x;
        aCollision.CollisionPoint.z = RingToCenter.z;
        return true;
    }

    return false;
}

bool IntersectPointSphere2D(const Vector2& aCenter, int64 aRadius, const Vector2& aPoint)
{
    Vector2 PointToCenter(aCenter.x - aPoint.x, aCenter.z - aPoint.z);
    int64 len = PointToCenter.Magnitude2();
    RestoreObjToPool(PointToCenter);
    if (len <= aRadius*aRadius)
    {
        return true;
    }

    return false;
}

//--implement GJK here

size_t indexOfFurthestPoint(const Vector2 aVertices[], size_t aCount, Vector2 aDir)
{
	// Get furthest vertex along a certain direction
	int64 maxProduct = Vector2::Dot(aDir, aVertices[0]);
	size_t index = 0;
	for (size_t i = 1; i < aCount; i++)
	{
		int64 curPorduct = Vector2::Dot(aDir, aVertices[i]);
		if (curPorduct > maxProduct)
		{
			maxProduct = curPorduct;
			index = i;
		}
	}
	return index;
}

Vector2 support(const Vector2 aVertices1[], size_t aCount1,
	const Vector2 aVertices2[], size_t aCount2, Vector2 aDir)
{
	// Minkowski sum support function for GJK
	// get furthest point of first body along an arbitrary direction
	size_t i = indexOfFurthestPoint(aVertices1, aCount1, aDir);
	// get furthest point of second body along the opposite direction
	size_t j = indexOfFurthestPoint(aVertices2, aCount2, aDir.Negate());
	// subtract (Minkowski sum) the two points to see if bodies 'overlap'
	return Vector2::MinkowskiSub(aVertices1[i], aVertices2[j]);
}

bool gjk(const Vector2 aVertices1[], size_t aCount1,
	const Vector2 aVertices2[], size_t aCount2)
{
	size_t index = 0; // index of current vertex of simplex
	Vector2 a, b, c, d, ao, ab, ac, abperp, acperp, simplex[3];

	Vector2 position1 = Vector2::AveragePoint(aVertices1, aCount1);
	Vector2 position2 = Vector2::AveragePoint(aVertices2, aCount2);

	d = Vector2::MinkowskiSub(position1, position2);

	if (d.x == 0 && d.z == 0)
	{
		//don't like zero as initial direction
		d.x = 1;
	}
	// set the first support as initial point of the new simplex
	simplex[0] = support(aVertices1, aCount1, aVertices2, aCount2, d);
    a = simplex[0];

	if (Vector2::Dot(a, d) <= 0)
	{
		return false;  //no collision
	}

	d.Negate();

	int coins = GJK_MAX_TRY;
	while (coins > 0)
	{
		--coins;

		simplex[++index] = support(aVertices1, aCount1, aVertices2, aCount2, d);
        a = simplex[index];
		if (Vector2::Dot(a, d) <= 0)
		{
			return false;
		}

		ao = a.Negate(); // from point A to Origin is just negative A
		
		// simplex has 2 points, a line segment, not a triangle yet
		if (index < 2)
		{
			b = simplex[0];
			ab = Vector2::MinkowskiSub(b, a); // from point A to B
			d = Vector2::TripleProduct(ab, ao, ab); // ***it's  normal to AB towards Origin: (AB x AO) x AB***
			if (d.Magnitude2() == 0)
			{
				d = Vector2::Perpendicular(ab);
			}
			continue;  // skip to next iteration
		}

		b = simplex[1];
		c = simplex[0];
		ab = Vector2::MinkowskiSub(b, a);
		ac = Vector2::MinkowskiSub(c, a);

		acperp = Vector2::TripleProduct(ab, ac, ac);

		if (Vector2::Dot(acperp, ao) >= 0)
		{
			d = acperp; // new direction is normal to AC towards Origin
		}
		else
		{
			abperp = Vector2::TripleProduct(ac, ab, ab);
			if (Vector2::Dot(abperp, ao) < 0)
			{
				return true; // collision
			}

			simplex[0] = simplex[1];  // swap first elem, which is point C

			d = abperp;  // new direction is normal to AB towards Origin
		}

		simplex[1] = simplex[2];  //swap elem in middle, which is point B
		--index;
	}

	return false;
}