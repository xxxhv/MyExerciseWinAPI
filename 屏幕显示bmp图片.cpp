#include<iostream>
#include<Windows.h>
#include<malloc.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)
using namespace std;
void main()
{
	char fileName[30];                        //定义打开图像名字
	char *buf;                                //定义文件读取缓冲区
	char *p;
	int r, g, b, pix;
	HWND wnd;                                 //窗口句柄
	HDC dc;                                   //绘图设备环境句柄
	FILE *fp;                                 //定义文件指针
	FILE *fpw;                                //定义保存文件指针
	DWORD w, h;                                //定义读取图像的长和宽
	DWORD bitCorlorUsed;                      //定义
	DWORD bitSize;                            //定义图像的大小
	BITMAPFILEHEADER bf;                      //图像文件头
	BITMAPINFOHEADER bi;                      //图像文件头信息
											  //cout << "请输入要打开文件的名字：(如：e:\\1.bmp)";
											  //cin >> fileName;
	if ((fp = fopen("G:\\b3.bmp", "rb")) == NULL)
	{
		cout << "文件未找到！";
		exit(0);
	}
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);//读取BMP文件头文件
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);//读取BMP文件头文件信息
	w = bi.biWidth;                            //获取图像的宽
	h = bi.biHeight;                           //获取图像的高
	printf("%d %d", w,h);
	bitSize = bi.biSizeImage;                  //获取图像的size
	buf = (char*)malloc(w*h * 3);                //分配缓冲区大小
	fseek(fp, long(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)), 0);//定位到像素起始位置
	fread(buf, 1, w*h * 3, fp);                   //开始读取数据
	wnd = GetForegroundWindow();               
												  //获取窗口句柄
	//wnd = FindWindow("Progman", NULL);
	//wnd = GetWindow(wnd, GW_CHILD);
	//wnd = GetWindow(wnd, GW_CHILD);

	dc = GetDC(wnd);                           //获取绘图设备
	int x = 40;
	int y = 40;


	HDC disDc = GetDC(NULL);
	//创建兼容DC
	HDC nDC = CreateCompatibleDC(disDc);
	//创建画布
	HBITMAP hbitmap = CreateCompatibleBitmap(disDc, w, h);
	SelectObject(nDC, hbitmap);
	
	p = buf;
	for (int j = 0; j<h; j++)
	{
		for (int i = 0; i<w + 1; i++)
		{
			SetPixel(nDC, i, h - j, RGB(*p++, *p++, *p++));
		}
	}

	for (;;)
	{
		Sleep(5);
		//将nDC画到屏幕上
		BitBlt(disDc, x, y, w, h, nDC, 0, 0, SRCCOPY);
	}

	DeleteObject(disDc);
	DeleteDC(nDC);
		
	

	fpw = fopen("LenaSaved.bmp", "wb");
	fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, fpw);  //写入文件头
	fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, fpw);  //写入文件头信息
	p = buf;
	for (int j = 0; j<h; j++)
	{
		for (int i = 0; i<w * 3; i++)
		{
			fwrite(p++, 1, 1, fpw);
		}
	}
	fclose(fpw);
	fclose(fp);
	//return fp;
	system("pause");
}
