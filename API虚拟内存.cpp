#include <windows.h>
#include <strsafe.h>
#include "resource.h"
#include <Psapi.h>
#pragma comment (lib,"psapi.lib")
#define T_DATA 1

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = TRUE;
	MEMORYSTATUSEX ms = { sizeof(ms) };
	TCHAR szData[512] = { 0 };
	PROCESS_MEMORY_COUNTERS_EX pmc = { sizeof(pmc) };
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SetTimer(hDlg, T_DATA, 1000, NULL);
		SendMessage(hDlg,WM_TIMER,T_DATA,0);//发送消息给定时器马上执行一次
		break;
	}
	case WM_TIMER:
	{
		
		GlobalMemoryStatusEx(&ms);
		StringCchPrintf(szData, _countof(szData), TEXT(" %d\n %I64d\n %I64d\n %I64d\n %I64d\n %I64d\n %I64d\n"), 
			ms.dwMemoryLoad, 
			(__int64)ms.ullTotalPhys, 
			(__int64)ms.ullAvailPhys,
			(__int64)ms.ullTotalPageFile,
			(__int64)ms.ullAvailPageFile,
			(__int64)ms.ullTotalVirtual,
			(__int64)ms.ullAvailVirtual
		);
		SetDlgItemText(hDlg, IDC_DATA, szData);

		GetProcessMemoryInfo(GetCurrentProcess(), (PPROCESS_MEMORY_COUNTERS)&pmc, sizeof(pmc));
		StringCchPrintf(szData, _countof(szData), TEXT(" %I64d\n %I64d\n"),
			(__int64)pmc.WorkingSetSize / 1024,
			(__int64)pmc.PrivateUsage/1024
		);
		SetDlgItemText(hDlg, IDC_PRIVATE, szData);
		//workset 指目前程序所消耗的物理内存
		//privatebytes 指commit的内存
		//一个进程使用内存时 内存分两部分 一部分working set 一部分private bytes减去working set
		//其中working set 储存在物理内存中 paging file 在磁盘上
		break;
	}
	case WM_CLOSE:
	{
		EndDialog(hDlg, 0);
		break;
	}
	default:
		bRet = FALSE;
		break;
	}
	return bRet;
}

int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int nCmdShow)
{

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
	return 0;
}
