
#include "stdafx.h"
#include <iostream>
using namespace std;




int main(int argc, LPTSTR argv[])
{
	
	if (argc != 3)
	{
		printf("no file file1 file2\n");
		return 1;
	}
	if (!CopyFile(argv[1], argv[2], FALSE))
	{
		printf("copy file error\n");
		return 2;
	}
	system("pause");
	return 0;
}

