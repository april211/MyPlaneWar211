#include "pch.h"
#include "CEnemyBullet.h"
#include "resource.h"


CImageList CEnemyBullet::ebImages;

CEnemyBullet::CEnemyBullet() :CBullet(0, 0, 55, 10), direction$(DOWN) { newObRect(); }
CEnemyBullet::CEnemyBullet(long x, long y, int speed, int atk, int direction) : CBullet(x, y, speed, atk),
direction$(direction) 
{
	newObRect();
}

CEnemyBullet::~CEnemyBullet() {}


//方法实现
void CEnemyBullet::newObRect()
{
	obrect$ = CRect(obposition$, CPoint(obposition$.x + ENEMYBULLET_WIDTH,
														obposition$.y + ENEMYBULLET_HEIGHT));
}

BOOL CEnemyBullet::Load()
{
	return CGameObject::LoadPhoto(ebImages, IDB_ENEMYBULLET, RGB(0, 0, 0), ENEMYBULLET_WIDTH,
																		   ENEMYBULLET_HEIGHT, 1);
}

//租父类虚函数重写
CRect& CEnemyBullet::getObRect()
{
	newObRect();
	return obrect$;
}

BOOL CEnemyBullet::drawOb(CDC* pDC, BOOL Pause)//param：设备环境，暂停绘制标记
{
	if (!Pause)
	{
		obposition$.y += speed$ * direction$;//一般是DOWN
		newObRect();
	}

	if (obposition$.y > AREA_HEIGHT + ENEMYBULLET_HEIGHT)	//如果敌机子弹飞出下边界
		return FALSE;

	return ebImages.Draw(pDC, 0, obposition$, ILD_TRANSPARENT);


}