
// Plane_WarView.h: CPlaneWarView 类的接口
//

#pragma once
#include "CMyPlane.h"
#include "CMyPlane.h"
#include "CEnemyPlane.h"
#include "CMyBullet.h"
#include "CBossPlane.h"
#include "CRegularBullet.h"
#include "CEnemyBullet.h"
#include "CExplosion.h"
#include "CGem.h"
#include "CDefence.h"

class CPlaneWarView : public CView
{
protected: // 仅从序列化创建
	CPlaneWarView(int sumlevel = 10);
	DECLARE_DYNCREATE(CPlaneWarView)

// 特性
public:
	CPlaneWarDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPlaneWarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:

//位图内存指针
	static CBitmap* pMemBmp$; 

//内存DC指针
	static CDC* pMemDC$;

//设备DC指针        
	static CClientDC* pDC$;

//创建游戏对象指针     
	static CMyPlane*		pMyPlane$;
	static CEnemyPlane*		pEnemyPlane$;
	static CMyBullet*		pMyBullet$;
	static CRegularBullet*  pRegularBullet$;
	static CEnemyBullet*	pEnemyBullet$;
	static CBossPlane*      pBossPlane$;
	static CExplosion*		pExplosion$;
	static CGem*			pGem$;
	static CDefence*        pDefence$;



//创建游戏对象链表	
	static CObList obList$[8];

//CObList元素下标枚举，易于表示
	enum ObjType 
		{ enEnemyPlane = 0, enRegularBullet, enEnemyBullet, enExplosion, enBossPlane, enGem , enDefence};

//游戏信息
	int myscore$;			//战机得分
	int curlevel$;		    //当前关卡
	int sumlevel$;			//设置的总关卡数
	int bossid$;			//出现的BOSS编号
	int epcnt$;				//击败敌机数目
	int bosscnt$;			//当前屏幕上的BOSS数目（不能超过1）
	CString strdead$;       //战机死亡后的信息
	BOOL showboss$;			//是否应当出现BOSS
	BOOL ispass$;	        //是否通关
	BOOL ispause$;			//是否暂停
	BOOL issupermode$;		//是否选择了无敌模式
	BOOL hintflag$;			//是否显示防护罩提示
	BOOL deFlag$;			//战机是否真的收到了防护罩的保护
	BOOL lasts$;			//防护罩已经存在的时长
	int  epwait$;			//控制单位时间的敌机数量
	int defeatsound$;		//是否播放战败音效
	int victorysound$;		//是否播放胜利音效

//背景步进参数
	static int bmovepos;	

//绘制滚动背景，并利用双缓冲机制解决屏闪等问题
	BOOL drawBack(CDC* pDC, UINT bmpID, int pos);	

//初始化游戏
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);

//判断按键是否被按下
	BOOL isKeyPressed(int vkey);  

//终止游戏
	void stopGame();	

//不断刷新游戏界面
	void updateFrm(CDC* pMemDC);

//游戏逻辑过程
	void gameLogic();	

//判断战机等物体是否“死亡”
	BOOL isDead(CGameObject * pt);


// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnReStart();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
	afx_msg void OnGamePause();
};

#ifndef _DEBUG  // Plane_WarView.cpp 中的调试版本
inline CPlaneWarDoc* CPlaneWarView::GetDocument() const
   { return reinterpret_cast<CPlaneWarDoc*>(m_pDocument); }
#endif

