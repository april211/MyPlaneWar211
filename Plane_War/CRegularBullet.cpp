#include "pch.h"
#include "CRegularBullet.h"
#include "resource.h"

CImageList CRegularBullet::rbImages;

CRegularBullet::CRegularBullet() :CMyBullet(0, 0, 30, 10), direction$(UP) { newObRect(); }
CRegularBullet::CRegularBullet(long x, long y, int speed, int atk, int direction):CMyBullet(x, y, speed, atk),
																				direction$(direction)
{
	newObRect();
}

CRegularBullet::~CRegularBullet() {}


//方法实现
void CRegularBullet::newObRect()
{
	obrect$ =  CRect(obposition$, CPoint(obposition$.x + REGULARBULLET_WIDTH, 
														 obposition$.y + REGULARBULLET_HEIGHT));
}

BOOL CRegularBullet::Load()
{
	return CGameObject::LoadPhoto(rbImages, IDB_REGULARBULLET, RGB(255, 0, 0), REGULARBULLET_WIDTH, 
																			REGULARBULLET_HEIGHT, 1);
}

//租父类虚函数重写
CRect& CRegularBullet::getObRect()
{
	newObRect();
	return obrect$;
}

BOOL CRegularBullet::drawOb(CDC* pDC, BOOL Pause)//param：设备环境，暂停绘制标记
{
	if (!Pause)
	{
		obposition$.y += speed$ * direction$;//一般是UP
		newObRect();
	}

	if (obposition$.y < -REGULARBULLET_HEIGHT)	//如果子弹飞出边界
		return FALSE;

	return rbImages.Draw(pDC, 0, obposition$, ILD_TRANSPARENT);


}