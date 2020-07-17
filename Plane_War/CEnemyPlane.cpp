#include "pch.h"
#include "CEnemyPlane.h"
#include "resource.h"

//CEnemyPlane.cpp

CImageList CEnemyPlane::epImages;	//静态成员需要类外定义

//构造
CEnemyPlane::CEnemyPlane() : CPlane((rand() % 4 + 6), 0, 10), verticalm$(1)
{
	//战机速度随机在4到8之间取值，使得画面更加丰富
	setObPoint((rand() % (AREA_WIDTH - ENEMYPLANE_HEIGHT) + 1), -ENEMYPLANE_HEIGHT);//设置敌方战机的初始位置
	//x: 随机产生；y: 敌机一出现，再移动就会出现在屏幕里了
	newObRect();
}

CEnemyPlane::CEnemyPlane(int hp): CPlane((rand() % 4 + 6), 0, hp), verticalm$(1)
{
	//战机速度随机在4到8之间取值，使得画面更加丰富
	setObPoint((rand() % (AREA_WIDTH - ENEMYPLANE_HEIGHT) + 1), -ENEMYPLANE_HEIGHT);//设置敌方战机的初始位置
	//x: 随机产生；y: 敌机一出现，再移动就会出现在屏幕里了
	newObRect();
}

CEnemyPlane::CEnemyPlane(const CEnemyPlane& tt) :CPlane(tt), verticalm$(1)
{
	newObRect();
}

CEnemyPlane::~CEnemyPlane() {}


BOOL CEnemyPlane::Load()
{
	return CGameObject::LoadPhoto(epImages, IDB_ENEMYPLANE, RGB(255, 0, 0), ENEMYPLANE_WIDTH, ENEMYPLANE_HEIGHT, 1);
}

void CEnemyPlane::newObRect()		//更新战机的矩形域
{
	obrect$ = CRect(obposition$, CPoint(obposition$.x + ENEMYPLANE_WIDTH, obposition$.y + ENEMYPLANE_HEIGHT));
}

//重写祖父类虚函数

CRect& CEnemyPlane::getObRect()	//获得战机的矩形域
{
	newObRect();
	return obrect$;
}

BOOL CEnemyPlane::drawOb(CDC* pDC, BOOL Pause)//param：设备环境，暂停绘制标记
{
	if (twait$ > 12) { twait$ = 0; }
	else { twait$++; }	//设置战机装弹间隔

	if (!Pause)		//如果不暂停绘制的话
	{
		obposition$.y += verticalm$ * speed$;
		newObRect();
	}
	//还没有显示在屏幕上

	//如果战机飞出下边缘
	if (obposition$.y > AREA_HEIGHT - ENEMYPLANE_HEIGHT)
	{
		newObRect();
		return FALSE;
	}

	if (epImages.Draw(pDC, 0, obposition$, ILD_TRANSPARENT))
		return TRUE;
	else
		return FALSE;
}