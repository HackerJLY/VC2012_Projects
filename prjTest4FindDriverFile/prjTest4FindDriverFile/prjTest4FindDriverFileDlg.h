
// prjTest4FindDriverFileDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CprjTest4FindDriverFileDlg �Ի���
class CprjTest4FindDriverFileDlg : public CDialogEx
{
// ����
public:
	CprjTest4FindDriverFileDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PRJTEST4FINDDRIVERFILE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedbtntest();
	CString m_strInfFilePath;
	CEdit m_editInfFilePath;
};
