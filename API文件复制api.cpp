
#include "stdafx.h"
#include <iostream>
using namespace std;


//缓冲区
#define BUF_SIZE 256

int main(int argc, LPTSTR argv[])
{
	HANDLE hIn, hOut;
	DWORD nIn, nOut;//读写字节数
	CHAR buffer[BUF_SIZE];

	if (argc != 3)
	{
		printf("no file file1 file2\n");
		return 1;
	}
	//打开文件
	hIn = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hIn == INVALID_HANDLE_VALUE)
	{
		printf("cannot open file error\n");
		return 2;
	}
	hOut = CreateFile(argv[1], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		printf("open file error\n");
		return 3;
	}

	while (ReadFile(hIn, buffer, BUF_SIZE, &nIn, NULL) && nIn > 0)
	{
		WriteFile(hOut, buffer, nIn, &nOut, NULL);
		if (nIn != nOut)
		{
			printf("Fatal write error \n");
			return 4;
		}
	}
	CloseHandle(hIn);
	CloseHandle(hOut);
	system("pause");
	return 0;
}

