
#include "KuhnMunkres.h"
#include "IntMath.h"



KuhnMunkres::KuhnMunkres(int aMaxX, int aMaxY)
{
    mMaxX = aMaxX;
    mMaxY = aMaxY;
    mArrVisitX = new bool[mMaxX];
    mArrVisitY = new bool[mMaxY];
    mArrLabelX = new int[mMaxX];
    mArrLabelY = new int[mMaxY];
    mArrSlack = new int[mMaxY];
    mArrWeight = new int[mMaxX * mMaxY];
    mArrMatch = new int[mMaxY];

    mNumX = mMaxX;
    mNumY = mMaxY;
}

KuhnMunkres::~KuhnMunkres()
{
    delete[]mArrVisitX;
    delete[]mArrVisitY;
    delete[]mArrLabelX;
    delete[]mArrLabelY;

    delete[]mArrSlack;
    delete[]mArrWeight;
    delete[]mArrMatch;
}


int KuhnMunkres::Init(int aNumX, int aNumY)
{
    if (aNumX > mMaxX || aNumY > mMaxY)
    {
        return -1;
    }
    mNumX = aNumX;
    mNumY = aNumY;
    return 0;
}



int KuhnMunkres::DoBestMatch()
{
    if (mNumX <= 0 || mNumY <= 0)
    {
        return -1;
    }

    //初始化 
    for (int y = 0; y < mNumY; y++)
    {
        mArrMatch[y] = -1;
        mArrLabelY[y] = 0;
    }

    int tmpLabelX = 0;
    int offset = 0;
    for (int x = 0; x < mNumX; x++)
    {
        tmpLabelX = INT32_MIN_VALUE;
        offset = x * mNumY;
        for (int y = 0; y < mNumY; y++)
        {
            if (tmpLabelX < mArrWeight[offset + y])
            {
                tmpLabelX = mArrWeight[offset + y];
            }
        }
        mArrLabelX[x] = tmpLabelX;
    }

    //求解过程  
    for (int x = 0; x < mNumX; x++)
    {
        for (int y = 0; y < mNumY; y++)
        {
            mArrSlack[y] = INT32_MAX_VALUE;
        }
        while (true)
        {
            for (int i = 0; i < mNumX; i++)
            {
                mArrVisitX[i] = false;
            }
            for (int i = 0; i < mNumY; i++)
            {
                mArrVisitY[i] = false;
            }
            if (findPath(x))
            {
                break;
            }
            else
            {
                int delt = INT32_MAX_VALUE;
                for (int y = 0; y < mNumY; y++)
                {
                    if (!mArrVisitY[y] && delt > mArrSlack[y])
                    {
                        delt = mArrSlack[y];
                    }
                }
                for (int i = 0; i < mNumX; i++)
                {
                    if (mArrVisitX[i])
                    {
                        mArrLabelX[i] -= delt;
                    }
                }
                for (int i = 0; i < mNumY; i++)
                {
                    if (mArrVisitY[i])
                    {
                        mArrLabelY[i] += delt;
                    }
                }
            }
        }
    }

    return true;
}


bool KuhnMunkres::findPath(int aX)
{
    int tmpDelt;
    mArrVisitX[aX] = true;
    for (int y = 0; y < mNumY; y++)
    {
        if (mArrVisitY[y])
        {
            continue;
        }
        tmpDelt = mArrLabelX[aX] + mArrLabelY[y] - mArrWeight[aX * mNumY + y];
        if (tmpDelt == 0)//aX->y 是相等字图中的一条边   
        {
            mArrVisitY[y] = true;
            if (mArrMatch[y] == -1 || findPath(mArrMatch[y]))
            {
                mArrMatch[y] = aX;
                return true;
            }
        }
        else if (mArrSlack[y] > tmpDelt)
        {
            mArrSlack[y] = tmpDelt;
        }
    }
    return false;
}
