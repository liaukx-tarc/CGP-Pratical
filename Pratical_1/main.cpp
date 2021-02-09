#include "Windows.h"
#include "Graphic.h"
#include "Sprite.h"

int main()
{
	LiauWindows* windows = LiauWindows::getInstance();
	windows->createWindows();

	if (!Graphic::getInstance()->createDirectX() || !Sprite::getInstance()->createSprite())
	{
		return 0;
	}

	while (windows->loop())
	{

	}

	windows->clearWindows();
	Graphic::getInstance()->clearGraphic();
	Sprite::getInstance()->clearSprite();

	delete windows;

	return 0;
}