#include "pch.h"
#include "CBossPlane.h"
#include "resource.h"

//CBossPlane.cpp

CImageList CBossPlane::bp1Images;	//静态成员需要类外定义
CImageList CBossPlane::bp2Images;	//静态成员需要类外定义
CImageList CBossPlane::bp3Images;	//静态成员需要类外定义
CImageList CBossPlane::bp4Images;	//静态成员需要类外定义

//构造
CBossPlane::CBossPlane(int id, int hp) : CPlane(2, 0, hp), id$(id), verticalm$(1)
{
	if (id$ == 0)
	{
		//BOSS速度随机在4到8之间取值，使得画面更加丰富
		setObPoint(BOSSPLANE1_WIDTH, -BOSSPLANE1_HEIGHT);//设置BOSS的初始位置
		//x: 随机产生；y: 敌机一出现，再移动就会出现在屏幕里了
		newObRect();
	}
	else if (id$ == 1)
	{
		//BOSS速度随机在4到8之间取值，使得画面更加丰富
		setObPoint(BOSSPLANE2_WIDTH, -BOSSPLANE2_HEIGHT);//设置BOSS的初始位置
		//x: 随机产生；y: 敌机一出现，再移动就会出现在屏幕里了
		newObRect();
	}
	else if (id$ == 2)
	{
		//BOSS速度随机在4到8之间取值，使得画面更加丰富
		setObPoint(BOSSPLANE3_WIDTH, -BOSSPLANE3_HEIGHT);//设置BOSS的初始位置
		//x: 随机产生；y: 敌机一出现，再移动就会出现在屏幕里了
		newObRect();
	}
	else
	{
		//BOSS速度随机在4到8之间取值，使得画面更加丰富
		setObPoint(BOSSPLANE4_WIDTH, -BOSSPLANE4_HEIGHT);//设置BOSS的初始位置
		//x: 随机产生；y: 敌机一出现，再移动就会出现在屏幕里了
		newObRect();
	}

}

CBossPlane::CBossPlane(const CBossPlane& tt) :CPlane(tt), id$(tt.id$), verticalm$(tt.verticalm$)
{
	newObRect();
}

CBossPlane::~CBossPlane() {}


BOOL CBossPlane::Load()
{
	if ((CGameObject::LoadPhoto(bp1Images, IDB_BOSS1, RGB(0, 0, 0), BOSSPLANE1_WIDTH, BOSSPLANE1_HEIGHT, 1))
		&& (CGameObject::LoadPhoto(bp2Images, IDB_BOSS2, RGB(0, 0, 0), BOSSPLANE2_WIDTH, BOSSPLANE2_HEIGHT, 1))
		&& (CGameObject::LoadPhoto(bp3Images, IDB_BOSS3, RGB(0, 0, 0), BOSSPLANE3_WIDTH, BOSSPLANE3_HEIGHT, 1))
		&& (CGameObject::LoadPhoto(bp4Images, IDB_BOSS4, RGB(0, 0, 0), BOSSPLANE4_WIDTH, BOSSPLANE4_HEIGHT, 1))
		)
		return TRUE;
	else return FALSE;
}



void CBossPlane::newObRect()		//更新战机的矩形域
{
	if (id$ == enfirst)
	{
		obrect$ = CRect(obposition$, CPoint(obposition$.x + BOSSPLANE1_WIDTH, obposition$.y + BOSSPLANE1_HEIGHT));

	}
	else if (id$ == ensecond)
	{
		obrect$ = CRect(obposition$, CPoint(obposition$.x + BOSSPLANE2_WIDTH, obposition$.y + BOSSPLANE2_HEIGHT));

	}
	else if (id$ == enthird)
	{
		obrect$ = CRect(obposition$, CPoint(obposition$.x + BOSSPLANE3_WIDTH, obposition$.y + BOSSPLANE3_HEIGHT));
	}
	else
	{
		obrect$ = CRect(obposition$, CPoint(obposition$.x + BOSSPLANE4_WIDTH, obposition$.y + BOSSPLANE4_HEIGHT));
	}
}

//重写祖父类虚函数

CRect& CBossPlane::getObRect()	//获得战机的矩形域
{
	newObRect();
	return obrect$;
}

BOOL CBossPlane::drawOb(CDC* pDC, BOOL Pause)//param：设备环境，暂停绘制标记
{
	if (twait$ > 30) { twait$ = 0; }
	else { twait$++; }	//设置BOSS装弹间隔

	if (!Pause)		//如果不暂停绘制的话
	{
		obposition$.y += verticalm$ * speed$;
		newObRect();
	}
	//还没有显示在屏幕上

	if (id$ == enfirst)
	{
		if (obposition$.y > BOSSPLANE1_HEIGHT)
		{
			//让BOSS静止在一个地方
			obposition$.y = BOSSPLANE1_HEIGHT;
			newObRect();
		}

		if (bp1Images.Draw(pDC, 0, obposition$, ILD_TRANSPARENT))
			return TRUE;
		else
			return FALSE;
	}

	else if (id$ == ensecond)
	{
		//让BOSS静止在一个地方
		if (obposition$.y > BOSSPLANE2_HEIGHT)
		{
			obposition$.y = BOSSPLANE2_HEIGHT;
			newObRect();
		}

		if (bp2Images.Draw(pDC, 0, obposition$, ILD_TRANSPARENT))
			return TRUE;
		else
			return FALSE;
	}

	else if (id$ == enthird)
	{
		//让BOSS静止在一个地方
		if (obposition$.y > BOSSPLANE3_HEIGHT)
		{
			obposition$.y = BOSSPLANE3_HEIGHT;
			newObRect();
		}

		if (bp3Images.Draw(pDC, 0, obposition$, ILD_TRANSPARENT))
			return TRUE;
		else
			return FALSE;
	}

	else
	{
		//让BOSS静止在一个地方
		if (obposition$.y > BOSSPLANE4_HEIGHT)
		{
			obposition$.y = BOSSPLANE4_HEIGHT;
			newObRect();
		}

		if (bp4Images.Draw(pDC, 0, obposition$, ILD_TRANSPARENT))
			return TRUE;
		else
			return FALSE;
	}



}