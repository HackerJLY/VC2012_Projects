
// prjTest4VS2012.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CprjTest4VS2012App:
// �йش����ʵ�֣������ prjTest4VS2012.cpp
//

class CprjTest4VS2012App : public CWinApp
{
public:
	CprjTest4VS2012App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CprjTest4VS2012App theApp;