
// prjTest4ZLibWrapperMultiByteDlg.h : 头文件
//

#pragma once


// CprjTest4ZLibWrapperMultiByteDlg 对话框
class CprjTest4ZLibWrapperMultiByteDlg : public CDialogEx
{
// 构造
public:
	CprjTest4ZLibWrapperMultiByteDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PRJTEST4ZLIBWRAPPERMULTIBYTE_DIALOG };

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
