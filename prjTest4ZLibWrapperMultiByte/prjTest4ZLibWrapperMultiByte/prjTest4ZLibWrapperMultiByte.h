
// prjTest4ZLibWrapperMultiByte.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CprjTest4ZLibWrapperMultiByteApp:
// �йش����ʵ�֣������ prjTest4ZLibWrapperMultiByte.cpp
//

class CprjTest4ZLibWrapperMultiByteApp : public CWinApp
{
public:
	CprjTest4ZLibWrapperMultiByteApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CprjTest4ZLibWrapperMultiByteApp theApp;