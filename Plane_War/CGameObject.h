#pragma once
#include <afx.h>

//Designed by Wuguangkai211, Frank, 2020/06 - 2020/07

//这是所有游戏对象的父类的声明，public继承自CObject，其实现放在相应的xxx.cpp文件中

class CGameObject : public CObject
{
protected:
	//描述对象位置的二维坐标（左上角）
	CPoint obposition$;

	//对象所在的矩形区域
	CRect  obrect$;

public:
	//带有默认参数的构造函数
	CGameObject(long x = 0, long y = 0);	

	//设置虚析构，保证所有对象完全析构
	virtual ~CGameObject();			

    //获得对象坐标
	CPoint getObPoint();

	//设置游戏对象坐标
	void   setObPoint(long, long);

	//绘制 一个游戏对象，param：设备环境，暂停绘制标记纯虚函数
	virtual BOOL drawOb(CDC*, BOOL) = 0;

	//获得对象的矩形区域，纯虚函数
	virtual CRect& getObRect() = 0;

	//加载 对象的图像
	//params: CImageList&, 位图ID，掩码，图像的像素宽，图像的像素高，初始化的位图数
	static BOOL LoadPhoto(CImageList&, UINT, COLORREF, int, int, int);
};
