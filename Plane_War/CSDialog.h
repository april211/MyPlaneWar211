#pragma once


// CSDialog 对话框

class CSDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSDialog)

public:
	CSDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSDialog();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int summlevel$;
};
