#pragma once
#include "CGameObject.h"
#include "resource.h"
class CExplosion : public CGameObject
{

protected:

	//爆炸图片的图像列表
	static CImageList exImages;

	//图像索引的步进参数，用以实现爆炸的动画效果
	int    proc$;

public:
	CExplosion(int x, int y);
	~CExplosion();

	BOOL drawOb(CDC* pDC, BOOL bPause);
	static BOOL Load();
	CRect& getObRect();
	void newObRect();

	//单个爆炸图像的宽度
	static const int  EXPLOSION_WIDTH  = 66;	

	//单个爆炸图像的高度
	static const int  EXPLOSION_HEIGHT = 66;
};

