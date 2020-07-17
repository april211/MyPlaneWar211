#pragma once
#include "CGameObject.h"
#include "pch.h"

class CGem :
    public CGameObject
{
protected:
	int plushp$;
	int speed$;
	int direction$;	//敌机子弹飞行方向。一般为1，down
public:
	CGem();
	CGem(long x, long y, int direction);
	virtual ~CGem();

	//绘制 一个游戏对象，param：设备环境，暂停绘制标记
	BOOL drawOb(CDC*, BOOL);

	//获得对象的矩形区域，纯虚函数
	CRect& getObRect();

	//更新矩形
	void   newObRect();

	//加载对象图像
	static BOOL Load();

	//设置我的常规导弹的宽度和高度
	static const int GEM_WIDTH = 22;
	static const int GEM_HEIGHT = 27;
	static CImageList gmImages;

	friend class CPlaneWarView;
};

