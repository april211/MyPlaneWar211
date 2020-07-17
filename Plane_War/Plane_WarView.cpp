
// Plane_WarView.cpp: CPlaneWarView 类的实现
//
#include <windows.h>
#include "pch.h"
#include "framework.h"
#include <MMSYSTEM.H>
#include <mmsystem.h>
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Plane_War.h"
#endif

#include <atlimage.h>
#include "Plane_WarDoc.h"
#include "resource.h"
#include "Plane_WarView.h"
#include "CMyPlane.h"
#include "CSDialog.h"
#include "CZDialog.h"
#include <dsound.h>
#pragma comment(lib, "winmm")


#define  UP    -1
#define  DOWN   1

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneWarView


//类的静止成员变量声明与赋值
int			CPlaneWarView::bmovepos = 0;
CBitmap*    CPlaneWarView::pMemBmp$ = new CBitmap;
CDC*		CPlaneWarView::pMemDC$  = new CDC;
CClientDC*  CPlaneWarView::pDC$;
CMyPlane*   CPlaneWarView::pMyPlane$;
CObList     CPlaneWarView::obList$[8];


IMPLEMENT_DYNCREATE(CPlaneWarView, CView)

BEGIN_MESSAGE_MAP(CPlaneWarView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
	//ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_COMMAND(ID_32776, &CPlaneWarView::OnReStart)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_32777, &CPlaneWarView::OnGamePause)
END_MESSAGE_MAP()

// CPlaneWarView 构造/析构

//int myscore$;	    //战机得分
//int curlevel$;		    //当前关卡
//BOOL ispass$;	        //是否通关

CPlaneWarView::CPlaneWarView(int sumlevel) : myscore$(0), issupermode$(FALSE), curlevel$(1), ispass$(FALSE), ispause$(FALSE), lasts$(0), epwait$(0)
									,showboss$(FALSE), bossid$(0), sumlevel$(sumlevel), epcnt$(0), bosscnt$(0), hintflag$(FALSE), deFlag$(FALSE),
									defeatsound$(0), victorysound$(0)
{
	// TODO: 在此处添加构造代码

	//加载各对象的图像
	CMyPlane::Load();			//非静态成员引用必须与特定对象相对
	CEnemyPlane::Load();
	CRegularBullet::Load();
	CEnemyBullet::Load();
	CExplosion::Load();
	CBossPlane::Load();
	CGem::Load();
	CDefence::Load();

}

CPlaneWarView::~CPlaneWarView()
{
}

BOOL CPlaneWarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneWarView 绘图

void CPlaneWarView::OnDraw(CDC* pDC)
{
	CPlaneWarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

}


// CPlaneWarView 打印

BOOL CPlaneWarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneWarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneWarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneWarView 诊断

#ifdef _DEBUG
void CPlaneWarView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneWarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneWarDoc* CPlaneWarView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneWarDoc)));
	return (CPlaneWarDoc*)m_pDocument;
}
#endif //_DEBUG




// CPlaneWarView 消息处理程序

//创建（WM_Create) 消息的处理函数
int CPlaneWarView::OnCreate(LPCREATESTRUCT lpcs)//仅初始化一次
{
	
	if (CView::OnCreate(lpcs) == -1) { return -1;}//创建失败

	AfxMessageBox(_T("欢迎来到飞机大战（PlaneWar）游戏！\n在本游戏中，你需要通过键盘上的方向键和空格键来抵御敌机和BOSS的攻击。\n在获得防护罩后，你会在窗口左中部位得到提示。按G键来释放防护罩技能\n关卡会随着时间而越来越难，你发射的导弹数也会随之增加。\n每架敌机死亡后，有一定几率掉落宝石，捡到宝石有几率会获得防护罩！而且宝石是珍贵的加血资源，Don't miss them！\n每击落50架小敌机，该关的BOSS就会出现。\n当该关卡的BOSS被击败后，才算通过该关卡。\n接下来，按回车键（Enter）配置你的关卡数！（无敌模式默认5关，且无法修改）"), MB_OK);
	
	CSDialog start0;
	int flag = start0.DoModal();//创建模态对话框
	if (flag == IDOK)
	{
		sumlevel$ = start0.summlevel$;
		if (sumlevel$ <= 0) sumlevel$ = 1;
	}
	else if (flag == IDCANCEL)
	{
		issupermode$ = TRUE;//选择进入无敌模式
		sumlevel$ = 5;		//默认5关以供演示
	}
	
	srand((unsigned)time(NULL));   //产生随机数种子

	//众指针在这里初始化（pDC$不能在构造函数里，this不能是野指针）
	pDC$	 = new CClientDC(this);				//建立客户区DC
	pMemDC$  = new CDC;						//建立内存DC
	pMemBmp$ = new CBitmap;					//建立内存位图

	pMemDC$ ->CreateCompatibleDC(pDC$);		//创建兼容内存DC准备双缓冲
	pMemBmp$->CreateCompatibleBitmap(pDC$, AREA_WIDTH, AREA_HEIGHT);	//创建位图兼容
	pMemDC$ ->SelectObject(pMemBmp$);		//将位图选入内存DC

	pMyPlane$ = new CMyPlane;//产生我的战机

	SetTimer(1, 30, NULL);//准备进入主界面，设置定时
	return 1;			  //创建成功
}

//判断按键是否被按下
BOOL CPlaneWarView::isKeyPressed(int vkey)   
{
	//GetKeyState在按键不按的情况下开始为0，当一次‘按下抬起’后变为1，依次循环(按位与&100000000000，低位省略）
	if ((GetKeyState(vkey) & 1000000000000000)) return TRUE;//1000 0000 0000 0000
	else    return FALSE;
}


//双缓存机制绘图：先在内存DC中绘制动态背景，再推送到显示器上
//当启用双缓冲时，所有绘制操作首先呈现到内存缓冲区，而不是屏幕上的绘图图面。
//BitBlt函数不会对原来的位图进行拉伸或压缩，只会根据我们给定的nWidth，nHeight 值来决定该有多少部分进行显示
BOOL CPlaneWarView::drawBack(CDC* pMemDC, UINT bID, int bmovepos)
{
	CBitmap bmp;				//承载临时对象的缓冲位图
	CRect   rc1;				//后面用来获得窗口区域
	CDC     MemDC;				//用于双缓冲操作的内存DC

	GetClientRect(rc1);			//获得用户窗口的矩形区域
	bmp.LoadBitmapW(bID);		//获得目标位图
	MemDC.CreateCompatibleDC(pMemDC);		// 创建兼容DC，准备实行双缓冲
	MemDC.SelectObject(&bmp);			// 将画布和缓冲DC关联（将位图选入内存区域）
	pMemDC->StretchBlt(0, 0, AREA_WIDTH, AREA_HEIGHT, &MemDC, 0, -bmovepos, 512, 768, SRCCOPY);
	pMemDC->StretchBlt(0, 0, AREA_WIDTH, AREA_HEIGHT, &MemDC, 0, 768 - bmovepos, 512, 768, SRCCOPY);
	//两项输出，以实现滚动效果。StretchBlt：从源矩形中复制一个位图到目标矩形，必要时按目标设备设置的模式进行图像的拉伸或压缩。实现双缓冲图像的显示
	//SRCCOPY: 将源矩形区域直接拷贝到目标矩形区域
	return TRUE;
}

BOOL CPlaneWarView::isDead(CGameObject* pt)
{
	if (pt == NULL) return TRUE;
	else			return FALSE;
}

void CPlaneWarView::updateFrm(CDC* pMemDC)
{
	//实现滚动背景：内存DC，目标背景图，步进参数。使用了双缓冲技术
	//按照关卡随机更换背景图
	int n = curlevel$ % 10;
	if (n == 1 || n == 5)
	{
		drawBack(pMemDC, IDB_BACKGROUND1, bmovepos);

	}
	else if (n == 2 || n == 6 || n == 9)
	{
		drawBack(pMemDC, IDB_BACKGROUND2, bmovepos);

	}
	else if (n == 3 || n == 7)
	{
		drawBack(pMemDC, IDB_BACKGROUND3, bmovepos);

	}
	else
	{
		drawBack(pMemDC, IDB_BACKGROUND4, bmovepos);
	}


	//设置我方战机最大发射间隔
	if (pMyPlane$ != NULL)
	{
		if (curlevel$ <= 3)
		{
			pMyPlane$->maxtwait$ = 7;
		}
		else if (curlevel$ > 3 && curlevel$ <= 5)
		{
			pMyPlane$->maxtwait$ = 6;
		}
		else if (curlevel$ > 5 && curlevel$ <= 7)
		{
			pMyPlane$->maxtwait$ = 5;
		}
		else
		{
			pMyPlane$->maxtwait$ = 4;
		}
	}


	//绘制我方战机
	if (!isDead(pMyPlane$))		//如果我方战机没死
	{
		pMyPlane$ -> drawOb(pMemDC$, FALSE);
		//达到胜利条件
		if (sumlevel$ + 1 == curlevel$)
		{
			CFont newfont;					//用来保存新字体
			CFont* oldFont;					//用来保存旧字体
			newfont.CreateFontW(
				50,							//字体的宽度
				33,							//字体的高度
				0,							//字体显示的角度
				0,							//字体的角度
				FW_NORMAL,					//字体的磅数
				FALSE,						//斜体字体
				FALSE,						//带下划线的字体
				0,							//带删除线的字体
				ANSI_CHARSET,				//所需的字符集
				OUT_DEFAULT_PRECIS,			//输出的精度
				CLIP_DEFAULT_PRECIS,		//裁减的精度
				DEFAULT_QUALITY,			//实际字体之间的精度
				DEFAULT_PITCH | FF_SWISS,	//字体间距和字体集
				_T("Arial")					//使用的字体名称
			);//创建新字体

			oldFont = pMemDC->SelectObject(&newfont);//选择新字体
			pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetBkColor(RGB(0, 0, 0));
			pMemDC->SetTextColor(RGB(255, 0, 0));
			pMemDC->TextOut(AREA_WIDTH / 2, AREA_HEIGHT / 2, _T("!!VICTORY!!"));
			pMemDC->SelectObject(&oldFont);
			if (victorysound$ == 0)
			{
				victorysound$++;
			}				
			obList$[enBossPlane].RemoveAll();
			obList$[enEnemyPlane].RemoveAll();
			obList$[enExplosion].RemoveAll();
			obList$[enRegularBullet].RemoveAll();
			obList$[enEnemyBullet].RemoveAll();
		}
	}//if
	else					//我方战机死亡
	{		

		strdead$.Format(_T("关卡:%d"), curlevel$);
		pMemDC$->TextOutW(50, 20, strdead$);
		strdead$.Format(_T("得分:%d"), myscore$);
		pMemDC$->TextOutW(50, 50, strdead$);

		CFont newfont;					//用来保存新字体
		CFont* oldFont;					//用来保存旧字体
		newfont.CreateFontW(50,33,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,	OUT_DEFAULT_PRECIS,	
												CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,_T("Arial"));//创建新字体

		oldFont = pMemDC->SelectObject(&newfont);//选择新字体
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetBkColor(RGB(0, 0, 0));
		pMemDC->SetTextColor(RGB(255, 0, 0));
		pMemDC->TextOutW(AREA_WIDTH / 2, AREA_HEIGHT / 2, _T("!DEFEAT!"));
		pMemDC->SelectObject(&oldFont);
		if (defeatsound$ == 0)
		{
			defeatsound$++;
		}
		obList$[enBossPlane].RemoveAll();
		obList$[enEnemyPlane].RemoveAll();
		obList$[enExplosion].RemoveAll();
		obList$[enRegularBullet].RemoveAll();
		obList$[enEnemyBullet].RemoveAll();
		obList$[enGem].RemoveAll();
		obList$[enDefence].RemoveAll();
	}

	//绘制BOSS血条
	if (obList$[enBossPlane].GetHeadPosition() != NULL)
	{
		CBossPlane* pBossPlane = (CBossPlane*)obList$[enBossPlane].GetHead();
		CPoint  bpPt = pBossPlane->getObPoint();
		int sumhp = ((curlevel$ * 700 > 4900) ? 4900 : (curlevel$ * 700));//当前关卡BOSS总血量（在加入BOSS对象时所用）
		pMemDC->FillSolidRect(bpPt.x, bpPt.y, 100, 10, RGB(0, 0, 0));//总血量黑条
		pMemDC->FillSolidRect(bpPt.x, bpPt.y, (pBossPlane->hp$)* 100 / sumhp , 10, RGB(255, 0, 0));
		//红条覆盖长黑条，形成百分比血量条
	}

	//利用多态，不断刷新我的常规导弹、爆炸、敌机、敌机的子弹、BOSS、Gem、防护罩队列，将该删除的对象删除 %%%%%%%%%%
	for (int i = 0; i < 7; i++)
	{
		POSITION pos1, pos2;    //获取两个用来操作CObList的指针
		for (pos1 = obList$[i].GetHeadPosition(); (pos2 = pos1) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)obList$[i].GetNext(pos1);//返回当前元素的值，pos1指向下一个元素
			BOOL isAlive = (pObj->drawOb(pMemDC, FALSE));
			if (!isAlive)	//如果元素已过期（死亡或飞出边界等）
			{
				obList$[i].RemoveAt(pos2);	//从链表中删除pos2处的元素
				delete pObj;		//释放该元素内存
			}
		}
	}

	//如果关卡没有暂停
	if ((!ispause$))
	{
		CFont newfont;					//用来保存新字体
		CFont* oldFont;					//用来保存旧字体
		newfont.CreateFontW(20,	10,	0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,	OUT_DEFAULT_PRECIS,	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
																		DEFAULT_PITCH | FF_SWISS,_T("Arial"));//创建新字体

		oldFont = pMemDC$->SelectObject(&newfont);//选择新字体
		pMemDC$->SetBkMode(TRANSPARENT);
		pMemDC$->  SetTextColor(RGB(255, 0, 0));
		pMemDC$->SelectObject(&oldFont);

		if (pMyPlane$ != NULL)
		{	
			CString str;
			//格式输出信息
			pMemDC->SetTextAlign(TA_LEFT);//设置文字左对齐，否则结束时会出现文字错误
			str.Format(L"关卡总数:%d", sumlevel$);
			pMemDC$->TextOutW(10, 20, str);
			str.Format(L"所在关卡:%d", curlevel$);
			pMemDC$->TextOutW(10, 40, str);
			str.Format(L"你的得分:%d", myscore$);
			pMemDC$->TextOutW(10, 60, str);
			str.Format(L"剩余生命:%d", pMyPlane$->getHp());
			pMemDC$->TextOutW(10, 80, str);
			if (hintflag$)
			{
				pMemDC$->SetTextColor(RGB(0, 0, 255));
				pMemDC$->TextOutW(10, AREA_HEIGHT / 2, _T("按G键可释放防护罩！"));
			}

		}
		

	}

	//复制内存DC到设备DC
	pDC$ -> BitBlt(0, 0, AREA_WIDTH, AREA_HEIGHT, pMemDC$, 0, 0, SRCCOPY);
	if (victorysound$ == 1)
	{
		PlaySound((LPCTSTR)IDR_VICTORY, AfxGetInstanceHandle(), SND_RESOURCE | SND_SYNC);
		victorysound$ = -1;
	}
	else if(defeatsound$ == 1)
	{
		PlaySound((LPCTSTR)IDR_DEFEAT, AfxGetInstanceHandle(), SND_RESOURCE | SND_SYNC);
		defeatsound$ = -1;
	}
}

void CPlaneWarView::gameLogic()
{
	//随机产生敌机
	epwait$ = rand() % 10 + 12;		

	if (epwait$ == 14)
	{
		obList$[enEnemyPlane].AddTail(new CEnemyPlane);
		if (curlevel$ >= 6)
		{
			obList$[enEnemyPlane].AddTail(new CEnemyPlane);
		}
	}
	
	//每死亡50架敌机，且当前没有BOSS时，释放本关BOSS
	if ((epcnt$ >= 50) && (bosscnt$ == 0))
	{
		ispass$ = FALSE;
		showboss$ = TRUE;
		bosscnt$ = 1;
		epcnt$ = 0;
	}
	else
	{
		ispass$ = FALSE;
		showboss$ = FALSE;
		//NO epcnt$ = 0;
	}

	if (showboss$)
	{
		bossid$ = rand() % 9 + 1;
		//对应4种BOSS，随机出现，血量随着关卡而变化
		if (bossid$ == 1 || bossid$ == 2)
		{
			obList$[enBossPlane].AddTail(new CBossPlane(0, ((curlevel$* 700 > 4900)?4900:(curlevel$ * 700))));
		}
		else if (bossid$ == 3 || bossid$ == 4 || bossid$ == 5)
		{
			obList$[enBossPlane].AddTail(new CBossPlane(1, ((curlevel$ * 700 > 4900) ? 4900 : (curlevel$ * 700))));
		}
		else if (bossid$ == 6 || bossid$ == 7 )
		{
			obList$[enBossPlane].AddTail(new CBossPlane(2, ((curlevel$ * 700 > 4900) ? 4900 : (curlevel$ * 700))));
		}
		else 
		{
			obList$[enBossPlane].AddTail(new CBossPlane(3, ((curlevel$ * 700 > 4900) ? 4900 : (curlevel$ * 700))));
		}
		showboss$ = FALSE;
		ispass$ = FALSE;
		epcnt$ = 0;
	}
	else
	{
		bossid$ = 1;
	}
	
	if (isDead(pMyPlane$)) return;		//我方战死，结束逻辑推演

	//我的战机四个方向的移动

	pMyPlane$->verticalm$ = 0;
	pMyPlane$->horizenm$  = 0;		//初始delta均为0
	BOOL UMotion = FALSE;			//准备记录方向键动作信息
	BOOL DMotion = FALSE;			//实现左下、右上等组合键动作
	BOOL LMotion = FALSE;
	BOOL RMotion = FALSE;
	BOOL GKEY    = FALSE;

	GKEY = (isKeyPressed('G'));		//检测到z键，判断开启防护罩
	if (GKEY && pMyPlane$->isdefence$ && !deFlag$)//当z被按下，且战机要被防护，且当前战机未受到防护时，增加防护罩 
	{
		CPoint tt = pMyPlane$->getObPoint();
		obList$[enDefence].AddTail(new CDefence(tt.x - 5, tt.y - 10));//添加防护罩到队列
		deFlag$ = TRUE;//我的战机已受到实际防护，且在防护罩存续期间，仅仅添加一次对象
		hintflag$ = FALSE;
		//issupermode$ = TRUE;//短暂开启无敌模式
	}
	if (!GKEY && pMyPlane$->isdefence$&& !deFlag$)//当z没被按下，且战机要被防护，且当前战机未受到防护时，显示提示  
	{
		hintflag$ = TRUE;
	}
	else
	{
		hintflag$ = FALSE;
	}


	if (!pMyPlane$->isdefence$ && deFlag$)//当战机不应当被防护，且防护罩仍然存在时
	{
		deFlag$ = FALSE;  //取消实际防护罩
		//issupermode$ = FALSE;
	}

	UMotion = (isKeyPressed(VK_UP) || isKeyPressed('W'));		//检测到上键
	if (UMotion) pMyPlane$->verticalm$ = -1;
			
	DMotion = (isKeyPressed(VK_DOWN) || isKeyPressed('S'));	//检测到下键
	if (DMotion) pMyPlane$->verticalm$ =  1;

	LMotion = (isKeyPressed(VK_LEFT) || isKeyPressed('A'));	//检测到左键
	if (LMotion) pMyPlane$->horizenm$  = -1;

	RMotion = (isKeyPressed(VK_RIGHT) || isKeyPressed('D'));	//检测到右键
	if (RMotion) pMyPlane$->horizenm$  =  1;

	//我的战机发射导弹
	if (isKeyPressed(VK_SPACE))				  //如果客户按下了空格键
	{
		if (!isDead(pMyPlane$) && pMyPlane$->ifFire())//若我的战机未阵亡，并且已装载好弹药（经历延时）
		{
			CPoint tt = pMyPlane$ -> getObPoint();	  //获取当前我的战机的左上角坐标

			//在合适的位置添加（发射）一对子弹，默认速度30，攻击力10，UP
			//两列子弹无条件添加
			obList$[enRegularBullet].AddTail(new CRegularBullet(tt.x + 9 , tt.y,     30, 10, UP));
			obList$[enRegularBullet].AddTail(new CRegularBullet(tt.x + 45, tt.y,     30, 10, UP));

			//当关卡数在
			if (curlevel$ >= 2 && curlevel$ < 5)
			{
				obList$[enRegularBullet].AddTail(new CRegularBullet(tt.x + 27, tt.y - 7, 30, 10, UP));//中间的子弹向前凸出
			}

			if (curlevel$ >= 5)
			{
				//保持对称性
				obList$[enRegularBullet].AddTail(new CRegularBullet(tt.x + 21, tt.y - 7, 30, 10, UP));//中间的子弹向前凸出
				obList$[enRegularBullet].AddTail(new CRegularBullet(tt.x + 33, tt.y - 7, 30, 10, UP));//中间的子弹向前凸出

			}

			//添加常规导弹发射声音
			PlaySound((LPCTSTR)IDR_MYSHOT, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);//%%%
		}

	}

	//防护罩的删除和进一步判断
	POSITION dePos = obList$[enDefence].GetHeadPosition();
	if (!isDead(pMyPlane$)&& deFlag$)//若我的战机未阵亡，并且在接受保护   
	{
		CPoint tt = pMyPlane$->getObPoint();	      //获取当前我的战机的左上角坐标
		if (dePos != NULL)//如果防护罩真的存在
		{
			lasts$++;
			//issupermode$ = TRUE;
			obList$[enDefence].RemoveAt(dePos);
			obList$[enDefence].AddTail(new CDefence(tt.x - 5, tt.y - 10));//添加防护罩到队列
		}
		else
		{
			pMyPlane$->isdefence$ = FALSE;
			deFlag$ = FALSE;
			//issupermode$ = FALSE;
		}

		if (lasts$ > CDefence::LAST)
		{
			obList$[enDefence].RemoveAt(obList$[enDefence].GetHeadPosition());
			lasts$ = 0;
			pMyPlane$->isdefence$ = FALSE;
			deFlag$ = FALSE;
			//issupermode$ = FALSE;
		}
	}


	//敌机发射导弹
	if (!isDead(pMyPlane$))
	{
		CRect myRect0 = pMyPlane$->getObRect();

		for (POSITION enPos = obList$[enEnemyPlane].GetHeadPosition(); enPos != NULL;)
		{
			CEnemyPlane* pEnemy = (CEnemyPlane*)obList$[enEnemyPlane].GetNext(enPos);
			CRect  eRect = pEnemy->getObRect();
			//敌机发射导弹
			if (pEnemy->ifFire() && ((eRect.left >= myRect0.left && eRect.left <= myRect0.right) || (eRect.right >= myRect0.left && eRect.right <= myRect0.right)))
			{
				obList$[enEnemyBullet].AddTail(new CEnemyBullet(eRect.left + 20, eRect.top + 10, 6, 10,  pEnemy->verticalm$));
			}

		}
	
	}

	//BOSS 发射导弹
	for (POSITION bsPos = obList$[enBossPlane].GetHeadPosition(); bsPos != NULL;)
	{
		CBossPlane* pBoss = (CBossPlane*)obList$[enBossPlane].GetNext(bsPos);
		CPoint  bPt = pBoss->getObPoint();

		//BOSS发射导弹
		if (pBoss->ifFire())
		{
			//三列导弹
			obList$[enEnemyBullet].AddTail(new CEnemyBullet(bPt.x + 50, bPt.y + 70, 6, 10, pBoss->verticalm$));
			obList$[enEnemyBullet].AddTail(new CEnemyBullet(bPt.x + 60, bPt.y + 70, 6, 10, pBoss->verticalm$));
			obList$[enEnemyBullet].AddTail(new CEnemyBullet(bPt.x + 70, bPt.y + 70, 6, 10, pBoss->verticalm$));

		}
	}


	//我的战机触碰到BOSS，我方战机急剧减血
	if (pMyPlane$ != NULL)
	{
		POSITION bpPos1 = NULL, bpPos2 = NULL;
		CRect myRect3 = pMyPlane$->getObRect();
		for (bpPos1 = obList$[enBossPlane].GetHeadPosition(); (bpPos2 = bpPos1) != NULL;)
		{
			CRect tt;
			CBossPlane* pBossPlane = (CBossPlane*)obList$[enBossPlane].GetNext(bpPos1);
			CRect bpRect0 = pBossPlane->getObRect();
			int ttatk = 30;		//一次敌机碰撞战机-30点血量

			if (tt.IntersectRect(&bpRect0, &myRect3))//矩形域相切，表示我的战机触碰到BOSS
			{
				//只在我方战机处添加爆炸效果
				obList$[enExplosion].AddTail(new CExplosion(myRect3.left, myRect3.top));

				//添加爆炸声音
				PlaySound((LPCTSTR)IDR_SMALLBANG, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);

				if (!issupermode$ && !(deFlag$))//不是无敌模式，无防护罩
				{
	     			//我方战机血量减少（必须放在删除子弹之前）
					pMyPlane$->hp$ -= ttatk;
				}

				//如果我方战机血量降至0，或者0以下
				if (pMyPlane$->hp$ <= 0)
				{
					//我的战机死亡，删除战机
					delete pMyPlane$;
					pMyPlane$ = NULL;
					break;
				}

				//不会删除该BOSS，我的碰撞本身不会对BOSS产生任何伤害
			}
		}
	}
	

	//敌机子弹炸我的战机（包括了BOSS）
	if (!isDead(pMyPlane$))
	{
		POSITION ebPos1 = NULL, ebPos2 = NULL;
		CRect myRect1 = pMyPlane$->getObRect();
		for (ebPos1 = obList$[enEnemyBullet].GetHeadPosition(); (ebPos2 = ebPos1) != NULL;)
		{
			CRect tt;
			CEnemyBullet* pEnemyBullet = (CEnemyBullet*)obList$[enEnemyBullet].GetNext(ebPos1);
			CRect ebRect = pEnemyBullet->getObRect();
			int ttatk = pEnemyBullet->getAtk();

			if (tt.IntersectRect(&ebRect, &myRect1))//矩形域相切，表示炸弹击中了目标
			{
				//在敌机子弹所在的位置添加爆炸效果
				obList$[enExplosion].AddTail(new CExplosion(ebRect.left, ebRect.top));

				//添加爆炸声音
				PlaySound((LPCTSTR)IDR_SMALLBANG, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);

				if (!issupermode$ && !(deFlag$))//不是无敌模式
				{
					//我方战机血量减少（必须放在删除子弹之前）
					pMyPlane$->hp$ -= ttatk;
				}

				//如果我方战机血量降至0，或者0以下
				if (pMyPlane$->hp$ <= 0)
				{
					//我的战机死亡，删除战机
					delete pMyPlane$;
					pMyPlane$ = NULL;
					break;
				}

				//删除子弹
				obList$[enEnemyBullet].RemoveAt(ebPos2);
				delete pEnemyBullet;

			}
		}
	}
	

	//敌机自杀式碰撞来炸我的战机

	if (pMyPlane$ != NULL)//如果我方战机已死，就不能获取矩形域
	{	
		POSITION enPos1 = NULL, enPos2 = NULL;
		CRect myRect2 = pMyPlane$->getObRect();
		for (enPos1 = obList$[enEnemyPlane].GetHeadPosition(); (enPos2 = enPos1) != NULL;)
		{
			CRect tt;
			CEnemyPlane* pEnemyPlane = (CEnemyPlane*)obList$[enEnemyPlane].GetNext(enPos1);
			CRect epRect0 = pEnemyPlane->getObRect();
			int ttatk = 20;		//一次敌机碰撞战机-20点血量

			if (tt.IntersectRect(&epRect0, &myRect2))//矩形域相切，表示敌机自杀式碰撞击中了目标
			{
				epcnt$++;
				//只在原敌机处添加爆炸效果
				obList$[enExplosion].AddTail(new CExplosion(epRect0.left, epRect0.top));

				//添加爆炸声音
				PlaySound((LPCTSTR)IDR_SMALLBANG, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);

				if (!issupermode$ && !(deFlag$))//不是无敌模式
				{
					//我方战机血量减少（必须放在删除子弹之前）
					pMyPlane$->hp$ -= ttatk;
				}

				//如果我方战机血量降至0，或者0以下
				if (pMyPlane$->hp$ <= 0)
				{
					//我的战机死亡，删除战机
					delete pMyPlane$;
					pMyPlane$ = NULL;
					break;
				}

				//删除该敌机
				obList$[enEnemyPlane].RemoveAt(enPos2);
				delete pEnemyPlane;

			}
		}
	}

	//宝石与我的战机碰撞检测

	if (pMyPlane$ != NULL)//如果我方战机已死，就不能获取矩形域
	{
		POSITION gmPos1 = NULL, gmPos2 = NULL;
		CRect myRect2 = pMyPlane$->getObRect();
		for (gmPos1 = obList$[enGem].GetHeadPosition(); (gmPos2 = gmPos1) != NULL;)
		{
			CRect tt;
			CGem* pGem = (CGem*)obList$[enGem].GetNext(gmPos1);
			CRect gmRect0 = pGem->getObRect();
			int ttplus = pGem->plushp$;		

			if (tt.IntersectRect(&gmRect0, &myRect2))//矩形域相切
			{
				//我方战机血量增加
				pMyPlane$->hp$ += ttplus;

				//随机获得防护罩
				int n = (rand() % 9 + 2); 
				if (n >= 4 && n <= 5 && !(pMyPlane$->isdefence$))// && deFlag$
				{
					pMyPlane$->isdefence$ = TRUE;
				}

				//删除该GEM
				obList$[enGem].RemoveAt(gmPos2);
				delete pGem;

			}
		}
	}
	


	//战机导弹炸掉敌机
	POSITION mbPos1 = NULL, mbPos2 = NULL;

	//我方战机发射的每一颗导弹与每一个敌机的相切检测
	for (mbPos1 = obList$[enRegularBullet].GetHeadPosition(); (mbPos2 = mbPos1) != NULL;)
	{
		CRegularBullet* pRegularBullet = (CRegularBullet*)obList$[enRegularBullet].GetNext(mbPos1);
		CRect rbRect  =  pRegularBullet -> getObRect();
		int   ttatk = pRegularBullet->getAtk();

		POSITION epPos1 = NULL, epPos2 = NULL;
		for (epPos1 = obList$[enEnemyPlane].GetHeadPosition(); (epPos2 = epPos1) != NULL;)
		{
			CRect tt;
			CEnemyPlane* pEnemy = (CEnemyPlane*)obList$[enEnemyPlane].GetNext(epPos1);
			CRect epRect1 = pEnemy->getObRect();
			if (tt.IntersectRect(&rbRect, &epRect1))//矩形域相切，表示炸弹击中了目标
			{
				//添加爆炸效果
				obList$[enExplosion].AddTail(new CExplosion(epRect1.left, epRect1.top));

				//添加爆炸声音
				PlaySound((LPCTSTR)IDR_SMALLBANG, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);

				//敌机减少血量（小敌机直接炸死）
				pEnemy->hp$ -= ttatk;

				//如果敌方战机血量降至0，或者0以下
				if (pEnemy->hp$ <= 0)
				{
					//打掉一个敌机，加200分值
					myscore$ += 200;
					if (bosscnt$ == 0)
					{
						epcnt$++;
					}
					

					//删除敌机
					obList$[enEnemyPlane].RemoveAt(epPos2);
					delete pEnemy;

					//随机掉落宝石
					int n = (rand() % 9 + 1);
					if (n == 4)
					{
						obList$[enGem].AddTail(new CGem(epRect1.left, epRect1.top, 1));
					}

				}

				//删除导弹
				obList$[enRegularBullet].RemoveAt(mbPos2);
				delete pRegularBullet;
				break;
			}
		}
	}

	//战机导弹炸BOSS
	POSITION mbPos11 = NULL, mbPos22 = NULL;

	//我方战机发射的每一颗导弹与BOSS的相切检测
	for (mbPos11 = obList$[enRegularBullet].GetHeadPosition(); (mbPos22 = mbPos11) != NULL;)
	{
		CRegularBullet* pRegularBullet = (CRegularBullet*)obList$[enRegularBullet].GetNext(mbPos11);
		CRect rbRect = pRegularBullet->getObRect();
		int ttatk = pRegularBullet->getAtk();

		POSITION bpPos1 = NULL, bpPos2 = NULL;
		for (bpPos1 = obList$[enBossPlane].GetHeadPosition(); (bpPos2 = bpPos1) != NULL;)
		{
			CBossPlane* pBoss = (CBossPlane*)obList$[enBossPlane].GetNext(bpPos1);//++++++++
			CRect bpRect1 = pBoss->getObRect();
			CRect tt;
			if (tt.IntersectRect(&rbRect, &bpRect1))//矩形域相切，表示炸弹击中了目标
			{
				//添加爆炸效果
				obList$[enExplosion].AddTail(new CExplosion(rbRect.left, rbRect.top));

				//添加爆炸声音
				PlaySound((LPCTSTR)IDR_SMALLBANG, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);

				//BOSS减少血量
				pBoss->hp$ -= ttatk;

				//如果BOSS血量降至0，或者0以下
				if (pBoss->hp$ <= 0)
				{
					//打掉一个BOSS，加1000分值
					myscore$ += 1000;
					//添加大爆炸音效
					PlaySound((LPCTSTR)IDR_BIGBANG, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					//添加大爆炸
					obList$[enExplosion].AddTail(new CExplosion(bpRect1.left, bpRect1.top));
					obList$[enExplosion].AddTail(new CExplosion(bpRect1.left + bpRect1.Width(), bpRect1.top));
					obList$[enExplosion].AddTail(new CExplosion((bpRect1.right + bpRect1.left)/2, (bpRect1.bottom + bpRect1.top)/2));
					obList$[enExplosion].AddTail(new CExplosion(bpRect1.right + bpRect1.Width(), bpRect1.bottom));
					obList$[enExplosion].AddTail(new CExplosion(bpRect1.right, bpRect1.bottom));
					//删除BOSS，本关完成。将自动进入下一关
					epcnt$ = 0;//这里要归零。。。。这个BUG耗了太长时间啊。。。。。
					bosscnt$ = 0;
					curlevel$++;
					ispass$ = TRUE;
					obList$[enBossPlane].RemoveAt(bpPos2);
					delete pBoss;
				}

				//删除导弹
				obList$[enRegularBullet].RemoveAt(mbPos22);
				delete pRegularBullet;
				break;
			}
		}
	}


}



void CPlaneWarView::stopGame()
{
	delete pMyPlane$;
	delete pMemDC$;
	delete pDC$;
	delete pMemBmp$;
}

//程序开始后不断被执行，刷新画面。nIDEvent来自于SetTimer函数
void CPlaneWarView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//刷新游戏帧画面: 在内存DC上绘图

	updateFrm(pMemDC$);
	gameLogic();
	if (++bmovepos > 700) bmovepos = 0; //添加步进以刷新视图
	 
	CView::OnTimer(nIDEvent);
}


//BOOL CPlaneWarView::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	return TRUE;
//}


void CPlaneWarView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
	CView::OnPaint();	// 不为绘图消息调用 CView::OnPaint()
}






void CPlaneWarView::OnReStart()
{
	// TODO: 在此添加命令处理程序代码
	//重绘
	KillTimer(1);
	obList$[enBossPlane].RemoveAll();
	obList$[enEnemyPlane].RemoveAll();
	obList$[enExplosion].RemoveAll();
	obList$[enRegularBullet].RemoveAll();
	obList$[enEnemyBullet].RemoveAll();
	obList$[enGem].RemoveAll();
	obList$[enDefence].RemoveAll();

	CSDialog start0;
	int flag = start0.DoModal();//创建模板对话框
	if (flag == IDOK)
	{
		sumlevel$ = start0.summlevel$;
		if (sumlevel$ <= 0) sumlevel$ = 1;
	}
	else if (flag == IDCANCEL)
	{
		issupermode$ = TRUE;//选择进入无敌模式
		sumlevel$ = 5;		//默认5关以供演示
	}

	srand((unsigned)time(NULL));   //产生随机数种子

	defeatsound$ = 0;
	victorysound$ = 0;
	ispass$ = FALSE;
	ispause$ = FALSE;
	lasts$ = 0;
	epwait$ = 0;
	showboss$ = FALSE;
	bossid$ = 0;
	epcnt$ = 0;
	bosscnt$ = 0;
	hintflag$ = FALSE;
	deFlag$ = FALSE;

	myscore$ = 0;
	curlevel$ = 1;
	delete pMyPlane$;
	pMyPlane$ = new CMyPlane;//产生我的战机

	SetTimer(1, 30, NULL);//准备进入主界面，设置定时
}


void CPlaneWarView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPlaneWarView::stopGame();
	CView::OnClose();
}


void CPlaneWarView::OnDestroy()
{
	CView::OnDestroy();
	this->stopGame();
	// TODO: 在此处添加消息处理程序代码
}


void CPlaneWarView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	// TODO: 在此添加专用代码和/或调用基类
}


void CPlaneWarView::OnGamePause()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(1);
	CZDialog start0;
	int flag = start0.DoModal();//创建模板对话框
	if (flag == IDCANCEL)
	{
		SetTimer(1, 30, NULL);//准备进入主界面，设置定时
	}
	else
	{
		SetTimer(1, 30, NULL);//准备进入主界面，设置定时
	}

}
