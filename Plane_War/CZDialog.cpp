// CZDialog.cpp: 实现文件
//

#include "pch.h"
#include "Plane_War.h"
#include "CZDialog.h"
#include "afxdialogex.h"


// CZDialog 对话框

IMPLEMENT_DYNAMIC(CZDialog, CDialogEx)

CZDialog::CZDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CZDialog::~CZDialog()
{
}

void CZDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CZDialog, CDialogEx)
END_MESSAGE_MAP()


// CZDialog 消息处理程序
