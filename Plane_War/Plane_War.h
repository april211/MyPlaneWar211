#include "pch.h"
#include "resource.h"       // 主符号
// Plane_War.h: Plane_War 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif


// CPlaneWarApp:
// 有关此类的实现，请参阅 Plane_War.cpp
//

class CPlaneWarApp : public CWinApp
{
public:
	CPlaneWarApp() noexcept;//noexcept关键字告诉编译器，函数中不会发生异常，与程序优化有关

// 这两个函数必须重写
public:
	virtual BOOL InitInstance();	
	virtual int  ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	
	//声明本类将处理消息
	DECLARE_MESSAGE_MAP()
};

extern CPlaneWarApp theApp;		//声明该应用程序唯一的对象，可全局使用
