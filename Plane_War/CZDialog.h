#pragma once


// CZDialog 对话框

class CZDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CZDialog)

public:
	CZDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CZDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
