#include "Windows.h"
#include "Graphic.h"
#include "Sprite.h"
#include "Font.h"

int main()
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LiauWindows* windows = LiauWindows::getInstance();
	windows->createWindows();

	if (!Graphic::getInstance()->createDirectX() || !Sprite::getInstance()->createSprite() || !Font::getInstance()->createFont())
	{
		return 0;
	}

	while (windows->loop())
	{

	}

	windows->clearWindows();
	Graphic::getInstance()->clearGraphic();
	Sprite::getInstance()->clearSprite();
	Font::getInstance()->clearFont();

	delete windows;

	return 0;
}