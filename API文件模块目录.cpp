
#include "stdafx.h"
#include <iostream>
using namespace std;




int main(int argc, LPTSTR argv[])
{
	//CreateDirectory创建文件夹
	//GetCurrentDirctory获取当前文件夹
	//GetModuleFilename得到模块文件名

	//绝对路径
	/*if (!CreateDirectory(TEXT("f:\\dog"), NULL))
	{
		printf("创建失败\n");
		return 1;
	}
	printf("创建成功\n");*/
	//当前路径
	TCHAR sz[MAX_PATH];
	DWORD len;
	len = GetCurrentDirectory(MAX_PATH, sz);
	if (len == 0)
	{
		printf("获取当前目录失败\n");
		return 2;
	}
	wprintf(L"%s\n", sz);

    /*
	if (!CreateDirectory(TEXT("cat"), NULL))
	{
		printf("创建失败\n");
		return 1;
	}
	printf("创建成功\n");*/


	//主模块
	TCHAR szModPath[MAX_PATH];

	if (!GetModuleFileName(NULL, szModPath, MAX_PATH))
	{
		printf("获取主模块路径失败\n");
		return 3;
	}
	wprintf(L"%s\n", szModPath);
	//模块2
	HMODULE hKernel32;//模块句柄
	TCHAR szModPath2[MAX_PATH];

	hKernel32 = LoadLibrary(TEXT("kernel32.dll"));//加载库DLL

	if (!GetModuleFileName(hKernel32, szModPath2, MAX_PATH))
	{
		printf("获取主模块路径失败\n");
		return 4;
	}
	wprintf(L"%s\n", szModPath2);

	system("pause");
	return 0;
}

