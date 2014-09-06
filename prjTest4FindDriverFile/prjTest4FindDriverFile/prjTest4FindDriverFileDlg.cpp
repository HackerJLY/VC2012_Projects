
// prjTest4FindDriverFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "prjTest4FindDriverFile.h"
#include "prjTest4FindDriverFileDlg.h"
#include "afxdialogex.h"

#include "afxwin.h"

//#include "EnumSys.cpp"

//bool copyfile(char* inifile);




// CprjTest4FindDriverFileDlg �Ի���

// EnumSys.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>
#include <strstream>
#include <fstream>
#include <sstream>
#include <io.h>
#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi")

typedef int (__stdcall * Wow64DisableWow64FsRedirectionA)(PVOID *); 
typedef int (__stdcall * Wow64RevertWow64FsRedirectionA)(LPVOID);

//#define _CRT_NON_CONFORMING_SWPRINTFS

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void enable_file_redirection(PVOID OldValue)
{
	Wow64RevertWow64FsRedirectionA f_Wow64RevertWow64FsRedirection = (Wow64RevertWow64FsRedirectionA)
		GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "Wow64RevertWow64FsRedirection"); 
	if(f_Wow64RevertWow64FsRedirection != NULL) 
	{
		f_Wow64RevertWow64FsRedirection(OldValue);
	}
}

 
void disibale_file_redirection(PVOID* OldValue)
{
	Wow64DisableWow64FsRedirectionA f_Wow64DisableWow64FsRedirection = (Wow64DisableWow64FsRedirectionA)
		GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "Wow64DisableWow64FsRedirection");
	if (f_Wow64DisableWow64FsRedirection != NULL)
	{
		f_Wow64DisableWow64FsRedirection(OldValue);
	}
}

bool enumfile(std::string &path, std::string &filename)
{
	struct _finddata_t fda = {0};
	std::string enupath = path + "\\*.*";
	long handle = _findfirst(enupath.c_str(), &fda);
	if (handle != -1)
	{
		while(!_findnext(handle, &fda))
		{
			if (strcmp(fda.name, ".") == 0 ||
				strcmp(fda.name, "..") == 0)
			{
				continue;
			}
			if (fda.attrib&_A_SUBDIR)
			{
				std::string newpath = path+"\\"+fda.name;
				if( enumfile(newpath, filename) )
				{
					path = newpath;
					return true;
				}
			}
			else if (_stricmp(filename.c_str(), fda.name) == 0)
			{
				return true;
			}
		}
		_findclose(handle);
	}
	return false;
}

bool findfile(std::string &file)
{
	char* path = new char[MAX_PATH];
	GetSystemDirectoryA(path, MAX_PATH);

	std::string tmpname = path;
	tmpname += "\\" + file;

	if ( !_access(tmpname.c_str(), 0) )
	{
		file = tmpname;
		delete []path;
		return true;
	}

	tmpname = path ;
	tmpname += "\\drivers\\"+file;
	if ( !_access(tmpname.c_str(), 0) )
	{
		file = tmpname;
		delete []path;
		return true;
	}

	// �����ļ�
	// C:\Windows\System32\DriverStore\FileRepository\xxxx 
	tmpname = path ; // C:\windows\sytem32 
//	tmpname += "\\DriverStore\\FileRepository";
	delete []path;
	if (enumfile(tmpname, file))
	{
		tmpname += "\\"+file;
		file = tmpname;
		return true;
	}
	

	return false;
}


bool EnumNeedFileName(const char* filename, std::vector<std::string> &fina)
{
	/*
	std::ifstream infile(filename);
	if(!infile)
	{
		return false;
	}
	std::string fileline;
	while(std::getline(infile, fileline))
	{
		if (fileline[0] == '[' && fileline.find("SourceDisksFiles") != std::string::npos)
		{
			while(std::getline(infile, fileline))
			{
				if (fileline[0] == '[')
				{
					break;
				}
				std::istringstream str(fileline);
				std::string tmpname;
				if (str>>tmpname)
				{
					size_t len = tmpname.find('=');
					if (len != std::string::npos)
					{
						tmpname.erase(len);
					}

					PVOID OldValue = NULL;
					disibale_file_redirection(&OldValue);
					findfile(tmpname);
					enable_file_redirection(OldValue);
					fina.push_back(tmpname);
				}
			}
			break;
		}
	}
	infile.close();
	*/

	char* pbuf = new char[1024];
	GetPrivateProfileSectionNamesA(pbuf, 1024, filename);
	const char* pstr = pbuf;
	std::string fileline;

	// cat�ļ�
	GetPrivateProfileSectionA("Version", pbuf, 1024, filename);
	pstr = pbuf;
	while(*pstr != NULL)
	{
		fileline = pstr;
		size_t len = fileline.find("CatalogFile");
		if (len == std::string::npos)
		{
			pstr += strlen(pstr) + 1;
			continue;
		}
		len = fileline.find('=');
		if (len != std::string::npos)
		{
			PVOID OldValue = NULL;
			disibale_file_redirection(&OldValue);
			std::string findttt = &fileline.at(len+1);
			findfile(findttt);
			enable_file_redirection(OldValue);
			fina.push_back(findttt);
		}
		pstr += strlen(pstr) + 1;
	}


	// dll��sys�ļ�
	GetPrivateProfileSectionNamesA(pbuf, 1024, filename);
	pstr = pbuf;
	while(*pstr != NULL)
	{
		if ( StrStrIA(pstr, "SourceDisksFiles") != NULL)
		{
			fileline = pstr;
			break;
		}		
		pstr += strlen(pstr) + 1;
	}

	if (fileline == "")
	{
		return false;
	}
	GetPrivateProfileSectionA(fileline.c_str(), pbuf, 1024, filename);
	pstr = pbuf;
	while(*pstr != NULL)
	{
		fileline = pstr;
		size_t len = fileline.find('=');
		if (len != std::string::npos)
		{
			fileline.erase(len);
		}
		PVOID OldValue = NULL;
		disibale_file_redirection(&OldValue);
		findfile(fileline);
		enable_file_redirection(OldValue);
		fina.push_back(fileline);

		pstr += strlen(pstr) + 1;
	}

	delete []pbuf;
	return true;
}

// �����ַ����и����ַ������ֵ�λ��
LPCSTR FindLasteSymbolA(LPCSTR CommandLine, CHAR FindWchar)
{
	int Len;
	for ( Len = strlen(CommandLine) ; Len>0; Len-- )
	{
		if (CommandLine[Len] == FindWchar)
		{
			Len++;
			break;
		}
	}
	return &CommandLine[Len];
}

bool copyfile(char* inifile)
{
	WCHAR szwcharMsg[MAX_PATH * 2];
	CHAR szcharMsg[MAX_PATH * 2];

	std::vector<std::string> alldriver;
	const char* inifilename = FindLasteSymbolA(inifile, '\\');
	CreateDirectoryA( inifilename, NULL);

	std::string inipath;
	if (inifilename != inifile)
	{
		inipath = inifile;
	}
	else
	{
		char* path = new char[MAX_PATH];
		GetWindowsDirectoryA(path, MAX_PATH);
		inipath = path;
		inipath += "\\inf\\" ;
		inipath	+= inifile;
		delete []path;
	}
	std::string newpath = inifilename;
	newpath += "\\" ;
	newpath += inifilename;
	CopyFileA(inipath.c_str(), newpath.c_str(), FALSE);

	// �õ������ļ�
	EnumNeedFileName(inipath.c_str(), alldriver);

	// ����
	
	for(std::vector<std::string>::iterator i = alldriver.begin(); 
	i != alldriver.end(); 
	i++)
	{
		newpath = inifilename;
		newpath += "\\" ;
		newpath += FindLasteSymbolA(i->c_str(), '\\');
		PVOID OldValue = NULL;
		disibale_file_redirection(&OldValue);

		//TRACE(L"----------------------------------------------------------------------\r\n");
		OutputDebugStringA("----------------------------------------------------------------------\r\n");
		sprintf(szcharMsg, "File : %s\r\n", i->c_str());
		OutputDebugStringA(szcharMsg);
		//OutputDebugStringA(i->c_str());
		sprintf(szcharMsg, "New File : %s\r\n", newpath.c_str());
		OutputDebugStringA(szcharMsg);
		//OutputDebugStringA(newpath.c_str());

		CopyFileA(i->c_str(), newpath.c_str(), FALSE);

		enable_file_redirection(OldValue);
		std::cout<<*i<<" ---> "<<newpath<<std::endl;
	}
	return true;
}

#if 0

int main(int argc, char* argv[])
{
	char ffnam[MAX_PATH];
	printf("ini�ļ���:");
	scanf("%s", ffnam);
	copyfile(ffnam);
	return 0;
}

#endif




CprjTest4FindDriverFileDlg::CprjTest4FindDriverFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CprjTest4FindDriverFileDlg::IDD, pParent)
	, m_strInfFilePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CprjTest4FindDriverFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_editInfFilePath, m_strInfFilePath);
	DDX_Control(pDX, IDC_editInfFilePath, m_editInfFilePath);
}

BEGIN_MESSAGE_MAP(CprjTest4FindDriverFileDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_btnTest, &CprjTest4FindDriverFileDlg::OnBnClickedbtntest)
END_MESSAGE_MAP()


// CprjTest4FindDriverFileDlg ��Ϣ�������

BOOL CprjTest4FindDriverFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CprjTest4FindDriverFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CprjTest4FindDriverFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CprjTest4FindDriverFileDlg::OnBnClickedbtntest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	//========================================================================
	UpdateData();

	//m_strInfFilePath
	//------------------------------------------------------------------------

	char ffnam[MAX_PATH];
	//strcpy_s(ffnam, "C:\\Windows\\inf\\oem11.inf");
	//strcpy_s(ffnam, "C:\\Windows\\inf\\oem83.inf");
	strcpy_s(ffnam, "C:\\WINDOWS\\inf\\usbstor.inf");
	copyfile(ffnam);

	AfxMessageBox(L"Complete !");

	return;
}
