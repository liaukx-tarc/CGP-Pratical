#ifndef WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "resource.h"

class LiauWindows
{
private:
	static LiauWindows * sInstance;
	LiauWindows();

public:
	HWND g_hWnd;
	WNDCLASS wndClass;
	HINSTANCE hInstance;
	int keyIn, mouseX, mouseY;

	static LiauWindows* getInstance();
	static void releaseInsrance();

	void createWindows();
	void clearWindows();
	bool loop();
	void practicalChange();

	//Practical change
	int practical;
};
#endif