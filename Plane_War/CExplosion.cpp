#include "pch.h"
#include "CExplosion.h"
#include "resource.h"

//CExplosion.cpp
CImageList CExplosion::exImages;

//构造
CExplosion::CExplosion(int x, int y) :CGameObject(x, y), proc$(0) { newObRect(); }

CExplosion::~CExplosion() {}

//方法
void CExplosion::newObRect()
{
	obrect$ = CRect(obposition$, CPoint(obposition$.x + EXPLOSION_WIDTH, obposition$.y + EXPLOSION_HEIGHT));
}


CRect& CExplosion::getObRect()
{
	newObRect();
	return obrect$;
}

BOOL CExplosion::drawOb(CDC* pDC, BOOL bPause)
{
	if (proc$ == 8)//8张图片,连体
	{
		proc$ = 0;
		return FALSE;
	}

	exImages.Draw(pDC, proc$, obposition$, ILD_TRANSPARENT);//用新位置绘制图像，实现动画效果
	proc$++;
	return TRUE;
}

BOOL CExplosion::Load()
{
	return CGameObject::LoadPhoto(exImages, IDB_EXPLOSION, RGB(255, 0, 0), 66, 66, 8);
}