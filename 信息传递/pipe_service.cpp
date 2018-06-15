#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define BUFFER_SIZE 4096

DWORD WINAPI StartAddress(LPVOID lpParameter);

int _tmain(void)
{
	LPTSTR szPipename = _T("\\\\.\\pipe\\basicMPI");

	while (TRUE)
	{
		_tprintf(_T("basicMPI: waiting click connection\n"));
		//instance 实例 type 类型 duplex 双工 创建管道对象
		HANDLE hPipe = CreateNamedPipe(szPipename, PIPE_ACCESS_DUPLEX, PIPE_WAIT | PIPE_READMODE_MESSAGE | PIPE_TYPE_MESSAGE, PIPE_UNLIMITED_INSTANCES, BUFFER_SIZE, BUFFER_SIZE, 0, NULL);

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			_tprintf(_T("CreateNamePipe failed! Error code: [%u]\n"), GetLastError());
			return 2;
		}
		//如果在CreateNamedPipe没有指定FILE_FLAG_OVERLAPPED就获得管道对象,该函数在未连接客户端之前不会返回 
		if (ConnectNamedPipe(hPipe, NULL))//CreatNamedPipe 用来无线循环
		{
			_tprintf("Connection succeeded.\n");
			//创建一个线程 处理客户端请求 此时主线程同时准备下一个请求
			HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartAddress, hPipe, 0, NULL);
			CloseHandle(hThread);
		}
	}
	
	return 0;
}
DWORD WINAPI StartAddress(LPVOID lpParameter)
{
	HANDLE hPipe = (HANDLE)lpParameter;

	PTCHAR szRequest = (PTCHAR)HeapAlloc(GetProcessHeap(), 0, BUFFER_SIZE * sizeof(TCHAR));
	PTCHAR szReply = (PTCHAR)HeapAlloc(GetProcessHeap(), 0, BUFFER_SIZE * sizeof(TCHAR));

	DWORD dwBytesRead = 0;
	DWORD dwReplyBytes = 0;
	DWORD dwBytesWritten = 0;
	//接收
	_tprintf(_T("Waiting messages.\n"));
	if (!ReadFile(hPipe, szRequest, BUFFER_SIZE * sizeof(TCHAR), &dwBytesRead, NULL))
	{
		_tprintf(_T("ReadFile failed! error code : [%u]\n"), GetLastError());
		return 2;
	}
	_tprintf(_T("Click request:\"%s\"\n"), szRequest);


	_tcscpy_s(szReply, BUFFER_SIZE, _T("default anwser from server"));
	dwReplyBytes = (_tcslen(szReply) + 1) * sizeof(TCHAR);
	//返回给client
	if (!WriteFile(hPipe, szReply, dwReplyBytes, &dwBytesRead, NULL))
	{
		_tprintf(_T("WriteFile failed! error code : [%u]\n"), GetLastError());
		return 2;
	}
	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	HeapFree(GetProcessHeap(), 0, szRequest);
	HeapFree(GetProcessHeap(), 0, szReply);
	_tprintf("success\n");
	return 0L;
}