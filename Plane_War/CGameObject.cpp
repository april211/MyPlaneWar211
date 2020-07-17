#include "pch.h"
#include "resource.h"
#include "CGameObject.h"

//这里放置类GameObject的实现代码

CGameObject::CGameObject(long x, long y): obposition$(x, y) {}

CGameObject::~CGameObject() {}

CPoint CGameObject::getObPoint() { return obposition$; }

void CGameObject::setObPoint(long x, long y)
{
	obposition$.x = x;
	obposition$.y = y;
}

//params: CImageList&, 位图ID，掩码，图像的像素宽，图像的像素高，初始化的位图数
BOOL CGameObject::LoadPhoto(CImageList& imgList, UINT bmpID, COLORREF crMask, int bmpw, int bmph, int nInitial)
{
	//建立一个位图对象
	CBitmap ttbmp;	
	ttbmp.LoadBitmap(bmpID);
	imgList.Create(bmpw, bmph, ILC_COLOR24 | ILC_MASK, nInitial, 0);
	
	//实现透明贴图, 最后一个参数就是指透明的颜色，表示显示时需要将图片的所有crMask色透明掉,否则会有色底
	imgList.Add(&ttbmp, crMask);

	//加载图像成功
	return TRUE;
}