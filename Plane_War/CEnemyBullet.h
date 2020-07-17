#pragma once
#include "CBullet.h"
#include "resource.h"
#define DOWN   1

class CEnemyBullet : public CBullet
{
protected:
	int direction$;	//敌机子弹飞行方向。一般为1，down
public:
	CEnemyBullet();
	CEnemyBullet(long x, long y, int speed, int atk, int direction);
	virtual ~CEnemyBullet();

	//绘制 一个游戏对象，param：设备环境，暂停绘制标记
	BOOL drawOb(CDC*, BOOL);

	//获得对象的矩形区域，纯虚函数
	CRect& getObRect();

	//更新矩形
	void   newObRect();

	//加载对象图像
	static BOOL Load();

	//设置我的常规导弹的宽度和高度
	static const int ENEMYBULLET_WIDTH = 8;
	static const int ENEMYBULLET_HEIGHT = 8;
	static CImageList ebImages;
};

