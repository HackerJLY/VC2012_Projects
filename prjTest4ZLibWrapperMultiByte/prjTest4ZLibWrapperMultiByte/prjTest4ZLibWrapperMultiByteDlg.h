
// prjTest4ZLibWrapperMultiByteDlg.h : ͷ�ļ�
//

#pragma once


// CprjTest4ZLibWrapperMultiByteDlg �Ի���
class CprjTest4ZLibWrapperMultiByteDlg : public CDialogEx
{
// ����
public:
	CprjTest4ZLibWrapperMultiByteDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PRJTEST4ZLIBWRAPPERMULTIBYTE_DIALOG };

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
