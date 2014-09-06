
// prjTest4VS2012Dlg.h : 头文件
//

#pragma once


// CprjTest4VS2012Dlg 对话框
class CprjTest4VS2012Dlg : public CDialogEx
{
// 构造
public:
	CprjTest4VS2012Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PRJTEST4VS2012_DIALOG };

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
