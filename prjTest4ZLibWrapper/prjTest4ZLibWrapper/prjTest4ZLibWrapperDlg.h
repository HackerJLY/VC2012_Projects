
// prjTest4ZLibWrapperDlg.h : 头文件
//

#pragma once


// CprjTest4ZLibWrapperDlg 对话框
class CprjTest4ZLibWrapperDlg : public CDialogEx
{
// 构造
public:
	CprjTest4ZLibWrapperDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PRJTEST4ZLIBWRAPPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
