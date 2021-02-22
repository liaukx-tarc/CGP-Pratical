#include "Windows.h"
#include "Graphic.h"
#include "GameStateManager.h"

int main()
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LiauWindows* windows = LiauWindows::getInstance();
	windows->createWindows();

	if (!Graphic::getInstance()->createDirectX())
	{
		return 0;
	}

	while (windows->loop())
	{
		
	}

	windows->clearWindows();
	Graphic::getInstance()->clearGraphic();

	delete windows;

	return 0;
}