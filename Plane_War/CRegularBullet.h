#pragma once
#include "CMyBullet.h"
#include "resource.h"

#define UP	  -1
#define DOWN   1

class CRegularBullet : public CMyBullet
{
protected:
	int direction$;	//-1up, 1down

public:
	CRegularBullet();
	CRegularBullet(long x, long y, int speed, int atk, int direction);
	virtual ~CRegularBullet();

	//绘制 一个游戏对象，param：设备环境，暂停绘制标记纯虚函数
	BOOL drawOb(CDC*, BOOL);

	//获得对象的矩形区域，纯虚函数
	CRect& getObRect();

	//更新矩形
	void   newObRect();

	//加载对象图像
	static BOOL  Load();

	//设置我的常规导弹的宽度和高度
	static const int REGULARBULLET_WIDTH = 10;    
	static const int REGULARBULLET_HEIGHT = 33;
	static CImageList rbImages;
};



