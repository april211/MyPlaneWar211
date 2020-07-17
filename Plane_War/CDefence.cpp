#include "pch.h"
#include "CDefence.h"
#include "resource.h"

CImageList CDefence::dcImages;


//构造
CDefence::CDefence() :CGameObject(0, 0)

{
	setObPoint(0, 0);		//设置我的战机的初始位置
	newObRect();
}

CDefence::CDefence(int x, int y) :CGameObject(x, y)

{
	setObPoint(x, y);		//设置我的战机的初始位置
	newObRect();
}

CDefence::~CDefence() {}

//方法

BOOL CDefence::Load()
{
	return CGameObject::LoadPhoto(dcImages, IDB_DEFENCE, RGB(0, 0, 0), DEFENCE_WIDTH, DEFENCE_HEIGHT, 1);
}

void CDefence::newObRect()		//更新战机的矩形域
{
	obrect$ = CRect(obposition$, CPoint(obposition$.x + DEFENCE_WIDTH, obposition$.y + DEFENCE_HEIGHT));
}

//重写祖父类虚函数

CRect& CDefence::getObRect()	//获得战机的矩形域
{
	newObRect();
	return obrect$;
}

BOOL CDefence::drawOb(CDC* pDC, BOOL Pause)//param：设备环境，暂停绘制标记
{
	if (!Pause)		//如果不暂停绘制的话
	{
		obposition$.x += 0;
		obposition$.y += 0;
		newObRect();
	}


	if (dcImages.Draw(pDC, 0, obposition$, ILD_TRANSPARENT))
		return TRUE;
	else
		return FALSE;

	

}