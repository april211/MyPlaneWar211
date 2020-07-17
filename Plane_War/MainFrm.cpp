
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Plane_War.h"
#include "mmsystem.h"
#include "MainFrm.h"
#pragma comment(lib,"WINMM.LIB")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("未能创建工具栏\n");
	//	return -1;      // 未能创建
	//}														---删除掉工具栏第一步，共两步

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("未能创建状态栏\n");							---删除掉状态栏
	//	return -1;      // 未能创建
	//}
	//m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//// TODO: 如果不需要可停靠工具栏，则删除这三行				---删除掉工具栏第二步，共两步
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	//最后一个参数显示设置好的ICON图标
	cs.lpszClass = AfxRegisterWndClass(0, 0, 0, AfxGetApp() -> LoadIcon(IDR_MAINICON) );

	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	//设置初始主窗口的位置
	cs.x = (::GetSystemMetrics(SM_CXSCREEN)) / 9 ;
	cs.y = (::GetSystemMetrics(SM_CYSCREEN)) / 24 ;

	//新窗口的宽度
	cs.cx = AREA_WIDTH + 24;		

	//新窗口的高度 == 游戏区域高度 + 菜单栏高度 + 标题栏高度
	cs.cy = AREA_HEIGHT + ::GetSystemMetrics(SM_CYMENU) + ::GetSystemMetrics(SM_CYCAPTION) + 24;

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序


//锁定主窗口大小
void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	lpMMI->ptMinTrackSize.x = AREA_WIDTH + 24;
	lpMMI->ptMinTrackSize.y = AREA_HEIGHT + ::GetSystemMetrics(SM_CYMENU) + ::GetSystemMetrics(SM_CYCAPTION) + 24;
	lpMMI->ptMaxTrackSize.x = AREA_WIDTH + 24;
	lpMMI->ptMaxTrackSize.y = AREA_HEIGHT + ::GetSystemMetrics(SM_CYMENU) + ::GetSystemMetrics(SM_CYCAPTION) + 24;
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}



