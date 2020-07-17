#include "pch.h"
#include "CMyPlane.h"
#include "resource.h"
//CMyPlane.cpp

CImageList CMyPlane::mpImages;	//静态成员需要类外定义

//构造
CMyPlane::CMyPlane() : CPlane(6, 0, 500), verticalm$(0), horizenm$(0), isdefence$(FALSE), maxtwait$(7)
{
	setObPoint(270, 500);		//设置我的战机的初始位置
	newObRect();
}
CMyPlane::CMyPlane(const CMyPlane& tt):CPlane(tt)
				, verticalm$(0), horizenm$(0), isdefence$(tt.isdefence$), maxtwait$(tt.maxtwait$)
{
	newObRect();
}

CMyPlane::~CMyPlane() {}

//方法
void CMyPlane::setDefence(bool isd)
{
	isdefence$ = isd;
}
bool CMyPlane::getDefence()
{
	return isdefence$;
}

BOOL CMyPlane::Load()
{
	return CGameObject::LoadPhoto(mpImages, IDB_MYPLANE, RGB(255, 0, 0), MYPLANE_WIDTH, MYPLANE_HEIGHT, 1);
}

void CMyPlane::newObRect()		//更新战机的矩形域
{
	obrect$ = CRect(obposition$, CPoint(obposition$.x + MYPLANE_WIDTH, obposition$.y + MYPLANE_HEIGHT));
}

//重写祖父类虚函数

CRect& CMyPlane::getObRect()	//获得战机的矩形域
{
	newObRect();
	return obrect$;
}

BOOL CMyPlane::drawOb(CDC* pDC, BOOL Pause)//param：设备环境，暂停绘制标记
{
	if (twait$ > maxtwait$) { twait$ = 0;}
	else { twait$++; }	//设置战机装弹间隔

	if (!Pause)		//如果不暂停绘制的话
	{
		obposition$.x += horizenm$* speed$;
		obposition$.y += verticalm$* speed$;
		newObRect();
	}
	//还没有显示在屏幕上
	//如果战机飞出右边缘
	if (obposition$.x >= AREA_WIDTH - MYPLANE_WIDTH)
	{
		obposition$.x = AREA_WIDTH - MYPLANE_WIDTH;
		newObRect();
	}
	//如果战机飞出下边缘
	if (obposition$.y >= AREA_HEIGHT - MYPLANE_HEIGHT)
	{
		obposition$.y = AREA_HEIGHT - MYPLANE_HEIGHT;
		newObRect();
	}
	//如果战机飞出左边缘
	if (obposition$.x <= 0)
	{
		obposition$.x = 0;
		newObRect();
	}
	//如果战机飞出上边缘
	if (obposition$.y <= 0)
	{
		obposition$.y = 0;
		newObRect();
	}

	if (mpImages.Draw(pDC, 0, obposition$, ILD_TRANSPARENT))
		return TRUE;
	else
		return FALSE;
}