
// prjTest4ZLibWrapperDlg.h : ͷ�ļ�
//

#pragma once


// CprjTest4ZLibWrapperDlg �Ի���
class CprjTest4ZLibWrapperDlg : public CDialogEx
{
// ����
public:
	CprjTest4ZLibWrapperDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PRJTEST4ZLIBWRAPPER_DIALOG };

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
};
