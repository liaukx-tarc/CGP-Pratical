#include "Windows.h"
#include "Graphic.h"
#include "Sprite.h"

//Singleton
LiauWindows* LiauWindows::sInstance = NULL;

LiauWindows* LiauWindows::getInstance()
{
	if (LiauWindows::sInstance == NULL)
	{
		sInstance = new LiauWindows;
	}

	return sInstance;
}

void LiauWindows::releaseInsrance()
{
	delete sInstance;
	sInstance = NULL;
}

LiauWindows::LiauWindows()
{
	this->g_hWnd = NULL;
	this->hInstance = GetModuleHandle(NULL);
	ZeroMemory(&wndClass, sizeof(wndClass));
	keyIn = 0;
	mouseX = 0;
	mouseY = 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int keyIn;

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == 27)
		{
			PostQuitMessage(0);
		}

		LiauWindows::getInstance()->keyIn = wParam;

		printf("wParam-%d speed-%d R-%d G-%d B-%d\n", wParam, Graphic::getInstance()->speed, 
																Graphic::getInstance()->red, 
																Graphic::getInstance()->green, 
																Graphic::getInstance()->blue);
		break;

	case WM_MOUSEMOVE:
		LiauWindows::getInstance()->mouseX = LOWORD(lParam);
		LiauWindows::getInstance()->mouseY = HIWORD(lParam);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void LiauWindows::createWindows()
{
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "Windows";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	RegisterClass(&wndClass);

	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Windows", WS_OVERLAPPEDWINDOW, 0, 100, 400, 300, NULL, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);

}

void LiauWindows::clearWindows()
{
	UnregisterClass(wndClass.lpszClassName, hInstance);
}

bool LiauWindows::loop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) break;

		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}

	Graphic::getInstance()->present();

	if (keyIn != 0)
	{
		keyIn = 0;
	}

	return msg.message != WM_QUIT;
}