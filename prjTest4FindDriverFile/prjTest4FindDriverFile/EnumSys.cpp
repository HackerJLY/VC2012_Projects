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

	// 查找文件
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

	// cat文件
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


	// dll，sys文件
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

// 查找字符串中给定字符最后出现的位置
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

	// 得到所有文件
	EnumNeedFileName(inipath.c_str(), alldriver);

	// 复制
	
	for(std::vector<std::string>::iterator i = alldriver.begin(); 
	i != alldriver.end(); 
	i++)
	{
		newpath = inifilename;
		newpath += "\\" ;
		newpath += FindLasteSymbolA(i->c_str(), '\\');
		PVOID OldValue = NULL;
		disibale_file_redirection(&OldValue);
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
	printf("ini文件名:");
	scanf("%s", ffnam);
	copyfile(ffnam);
	return 0;
}

#endif
