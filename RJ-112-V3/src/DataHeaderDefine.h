#ifndef DATAHEADERDEFINE_H
#define DATAHEADERDEFINE_H
#include "qglobal.h"
#define TRANSLATOR //Qt 国际化
#define setbit(x,y) x|=(1<<y) //将X的第Y位置1
#define clrbit(x,y) x&=~(1<<y) //将X的第Y位清0
//#define MAXRESOLUTION  //大分辨率
//#define ARMCOMPILE  //arm编译
extern quint8 m_CardWidthstandard;//自定义宽度标准
#endif // DATAHEADERDEFINE_H
