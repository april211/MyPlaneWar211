#include "pch.h"
#include "CGem.h"
#include "resource.h"


CImageList CGem::gmImages;

CGem::CGem() :CGameObject(0, 0), speed$(1), direction$(1), plushp$(50){ newObRect(); }
CGem::CGem(long x, long y, int direction):CGameObject(x, y), speed$(1), direction$(1), plushp$(50)
{
	newObRect();
}

CGem::~CGem() {}


//方法实现
void CGem::newObRect()
{
	obrect$ = CRect(obposition$, CPoint(obposition$.x + GEM_WIDTH, obposition$.y + GEM_HEIGHT));
}

BOOL CGem::Load()
{
	return CGameObject::LoadPhoto(gmImages, IDB_GEM, RGB(0, 0, 255), GEM_WIDTH, GEM_HEIGHT, 1);
}

//租父类虚函数重写
CRect& CGem::getObRect()
{
	newObRect();
	return obrect$;
}

BOOL CGem::drawOb(CDC* pDC, BOOL Pause)//param：设备环境，暂停绘制标记
{
	if (!Pause)
	{
		obposition$.y += speed$ * direction$;//一般是DOWN
		newObRect();
	}

	if (obposition$.y > AREA_HEIGHT + GEM_HEIGHT)	//如果敌机子弹飞出下边界
		return FALSE;

	return gmImages.Draw(pDC, 0, obposition$, ILD_TRANSPARENT);


}