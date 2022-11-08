#pragma once
/*

������ͼ�����Ȩƥ�䡣

����ô�������С��ʱ����С��ѡ��Ŀ��λ�á����Է�ʽ�����ҵ�һ��·�����ཻ�Ķ�Ӧ����

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
