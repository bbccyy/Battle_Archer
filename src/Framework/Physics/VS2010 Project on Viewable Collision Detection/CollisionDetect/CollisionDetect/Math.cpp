#include "StdAfx.h"
#include "Math.h"

int64 Sqrt(int64 x)  //不要丢负数进去
{
    x *= 10000;
    int64 val = x;
    int64 last = 0;
    int64 val_last = val-last;

    while(val_last>100)
    {
        last = val;
        val = (last + x / last ) / 2;
        val_last = val - last;

        if (val_last < 0)
        {
            val_last = -val_last;
        }
    }

    return val / 100;
}

int64 CosineInt(int64 aAngle, int64 aBase, int64 aCosBase) 
{
  int64 realAngle = aAngle % (aBase * 360);
  if( realAngle < 0)
  {
    realAngle = - realAngle;
  }
  if (realAngle > 180 * aBase) 
  {
    realAngle = 360 * aBase - realAngle;
  }

  if (realAngle > 90 * aBase) 
  {
    return -CosineInt90( 180 * aBase - realAngle, aBase, aCosBase);
  }
  return CosineInt90(realAngle, aBase, aCosBase);
}

//计算cosine值，并以int64(cosVal*aCosBase)的形式返回
//aAngle=角度实际值*aBase， aBase=放大因子，用来告诉函数角度放大了多少倍
//aCosBase=与返回值相关的放大因子，告诉使用者要将返回值除以多少倍以得到最终值
int64 CosineInt90(int64 aAngle, int64 aBase, int64 aCosBase)  //real = angle_para / aBase
{
    int64 comBase = aCosBase;
    const static int tangent[] ={1, 2, 4, 8, 16, 32, 64, 128, 512};  //real = (comBase / tangent[i]) /comBase
    const static int  angleBase = 10;
    const static int  angle[] = { 450, 266, 140, 71, 36, 18, 9, 4, 2, 1 };  //real = angle[i] / angleBase

    int i, signal;

    int64 x_cos, y_sin, x_temp, y_temp, z, z_next;
    x_cos = 0; y_sin = 0; z = aAngle*comBase/aBase; z_next = 0;
    x_temp = 607300;  //0.6073 * comBase
    y_temp = 0;
    signal = 1;

    for (i=0; i<9; i++) 

    {
        x_cos=x_temp - signal * y_temp / tangent[i];
        y_sin=y_temp + signal * x_temp / tangent[i];
        z_next = z - signal * angle[i] * comBase / angleBase;
        x_temp = x_cos;
        y_temp = y_sin;
        z = z_next;

        if(z_next>0)
        {
            signal = +1;
        }
        else
        {
            signal = -1; 
        }
    }

    return x_cos;
}

/*
int64 cosineInt180(int64 aAngle_para, int64 aBase, int64& aCosBase) {
  int64 realAngle = aAngle_para / aBase;
  if( aAngle_para < 0 ||  realAngle > 180){
    return 0;
  }

  if (realAngle > 90) {
    return -cosineInt(180*aBase - aAngle_para, aBase, aCosBase);
  }
  return cosineInt(aAngle_para, aBase, aCosBase);
}

int64 cosineInt(int64 aAngle_para, int64 aBase, int64& aCosBase) {
  int64 realAngle = aAngle_para % (aBase * 360);
  if( realAngle < 0){
    realAngle = - realAngle;
  }
  if (realAngle > 180 * aBase) {
    realAngle = 360 * aBase - realAngle;
  }

  if (realAngle > 90 * aBase) {
    return -cosineInt90( 180 * aBase - realAngle, aBase, aCosBase);
  }
  return cosineInt90(realAngle, aBase, aCosBase);
}

//计算cosine值，并以int64(cosVal*aCosBase)的形式返回
//入参：aAngle_para=角度实际值*aBase， aBase=放大因子，用来告诉函数角度放大了多少倍
//aCosBase=与返回值相关的放大因子，告诉使用者要将返回值除以多少倍以得到最终值
int64 cosineInt90(int64 aAngle_para, int64 aBase, int64& aCosBase)  //real = angle_para / aBase
{
    const static int64 comBase = 1000000;
    aCosBase = comBase;
    const static int tangent[] ={1, 2, 4, 8, 16, 32, 64, 128, 512};  //real = (comBase / tangent[i]) /comBase
    const static int  angleBase = 10;
    const static int  angle[] = { 450, 266, 140, 71, 36, 18, 9, 4, 2, 1 };  //real = angle[i] / angleBase

    int i, signal;

    int64 x_cos, y_sin, x_temp, y_temp, z, z_next;

    x_cos =0; y_sin=0; z=aAngle_para*comBase/aBase; z_next=0;

    x_temp =607300;  //0.6073 * comBase

    y_temp=0;

    signal = 1;

    for (i=0; i<9; i++) 

    {

        x_cos=x_temp - signal * y_temp / tangent[i];

        y_sin=y_temp + signal * x_temp / tangent[i];

        z_next = z - signal * angle[i] * comBase / angleBase;

        x_temp = x_cos;

        y_temp = y_sin;

        z = z_next;

        if(z_next>0)
        {
            signal = +1;
        }
        else
        {
            signal = -1; 
        }

    }

    return x_cos;
}
*/