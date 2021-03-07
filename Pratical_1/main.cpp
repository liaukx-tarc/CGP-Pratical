#include "Windows.h"
#include "Graphic.h"
#include "GameStateManager.h"
#include "DirectInput.h"

int main()
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LiauWindows* windows = LiauWindows::getInstance();
	windows->createWindows();

	Graphic::getInstance()->createDirectX();
	DirectInput::getInstance()->CreateInput();

	while (windows->loop())
	{
		
	}

	windows->clearWindows();
	Graphic::getInstance()->clearGraphic();
	DirectInput::getInstance()->clearInput();
	
	delete windows;
	Graphic::getInstance()->releaseInsrance();
	DirectInput::getInstance()->releaseInsrance();
	GameStateManager::getInstance()->releaseInsrance();

	return 0;
}