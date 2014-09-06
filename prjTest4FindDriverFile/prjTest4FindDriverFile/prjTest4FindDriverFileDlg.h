
// prjTest4FindDriverFileDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CprjTest4FindDriverFileDlg 对话框
class CprjTest4FindDriverFileDlg : public CDialogEx
{
// 构造
public:
	CprjTest4FindDriverFileDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PRJTEST4FINDDRIVERFILE_DIALOG };

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
public:
	afx_msg void OnBnClickedbtntest();
	CString m_strInfFilePath;
	CEdit m_editInfFilePath;
};
