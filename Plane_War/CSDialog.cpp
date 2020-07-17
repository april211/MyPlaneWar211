// CSDialog.cpp: 实现文件
//

#include "pch.h"
#include "Plane_War.h"
#include "CSDialog.h"
#include "afxdialogex.h"


// CSDialog 对话框

IMPLEMENT_DYNAMIC(CSDialog, CDialogEx)

CSDialog::CSDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, summlevel$(0)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CSDialog::~CSDialog()
{
}

void CSDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, summlevel$);
}


BEGIN_MESSAGE_MAP(CSDialog, CDialogEx)
END_MESSAGE_MAP()


// CSDialog 消息处理程序
