
// prjTest4VS2012Dlg.h : ͷ�ļ�
//

#pragma once


// CprjTest4VS2012Dlg �Ի���
class CprjTest4VS2012Dlg : public CDialogEx
{
// ����
public:
	CprjTest4VS2012Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PRJTEST4VS2012_DIALOG };

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
