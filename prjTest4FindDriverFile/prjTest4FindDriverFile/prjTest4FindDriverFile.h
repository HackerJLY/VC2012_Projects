
// prjTest4FindDriverFile.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CprjTest4FindDriverFileApp:
// �йش����ʵ�֣������ prjTest4FindDriverFile.cpp
//

class CprjTest4FindDriverFileApp : public CWinApp
{
public:
	CprjTest4FindDriverFileApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CprjTest4FindDriverFileApp theApp;