
// prjTest4ZLibWrapper.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CprjTest4ZLibWrapperApp:
// �йش����ʵ�֣������ prjTest4ZLibWrapper.cpp
//

class CprjTest4ZLibWrapperApp : public CWinApp
{
public:
	CprjTest4ZLibWrapperApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CprjTest4ZLibWrapperApp theApp;