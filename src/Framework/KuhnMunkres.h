#pragma once
/*

求解二分图的最大权匹配。

最初用处：控制小兵时，给小兵选择目标位置。可以方式可以找到一个路径不相交的对应方案

*/

class KuhnMunkres
{


public:
    KuhnMunkres(int aMaxX, int aMaxY);
    ~KuhnMunkres();

    int Init(int aNumX, int aNumY);

    inline void SetWeight(int aX, int aY, int aWeight)
    {
        mArrWeight[aX * mNumY + aY] = aWeight;
    }

    inline int GetMatchOfY(int aY)
    {
        return mArrMatch[aY];
    }

    int DoBestMatch();
private:
    bool findPath(int aX);


private:
    int mMaxX, mMaxY;
    int mNumX, mNumY;
    bool* mArrVisitX;
    bool* mArrVisitY;
    int* mArrLabelX;
    int* mArrLabelY;
    int* mArrSlack;
    int* mArrWeight;
    int* mArrMatch;


};
