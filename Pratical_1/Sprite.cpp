#include "Sprite.h"
#include "Graphic.h"
#include "Windows.h"

Sprite* Sprite::sInstance = NULL;

Sprite * Sprite::getInstance()
{
	if (Sprite::sInstance == NULL)
	{
		sInstance = new Sprite;
	}

	return sInstance;
}

void Sprite::releaseInsrance()
{
	delete sInstance;
	sInstance = NULL;
}

Sprite::Sprite()
{
	texture = NULL;
	sprite = NULL;
	viewMode = 1;
	spriteX = 0;
	spriteY = 0;
	keyIn = 0;
	changeMode = 1;
	bgTexture = 1;
	cursorColor = 1;
}

bool Sprite::createSprite()
{
	HRESULT hr = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);

	hr = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/bg1.png", &texture);
	hr = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/bg2.png", &texture2);
	hr = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/bg3.png", &texture3);
	hr = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/pointer.png", &cursorTexture);

	//Rect
	spriteRect.left = spriteRect.top = 0;
	spriteRect.right = 400;
	spriteRect.bottom = 300;

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void Sprite::drawSprite()
{
	if (keyIn != 0)
	{
		switch (keyIn)
		{
		case 219:
			changeMode = 1;
			break;

		case 221:
			changeMode = 2;
			break;

		default:
			break;
		}
	}

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	switch (changeMode)
	{
		//move sprite mode
	case 1:
		moveSprite();
		cursorDraw();
		break;

		//change background and cursor color mode
	case 2:
		backgroundChange();
		cursorColorChange();
	default:
		break;
	}

	sprite->End();
}

void Sprite::clearSprite()
{
	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;
}

void Sprite::changeView()
{
	int keyIn = LiauWindows::getInstance()->keyIn;
	if (keyIn >= 55 && keyIn <= 57)
	{
		viewMode = keyIn - 54;
		switch (viewMode)
		{
		case 1:
			printf("(View: Fix)\n\n");
			Graphic::getInstance()->d3dPP.BackBufferWidth = 400;
			Graphic::getInstance()->d3dPP.BackBufferHeight = 300;
			break;
		case 2:
			printf("(View: Smaller)\n\n");
			Graphic::getInstance()->d3dPP.BackBufferWidth = 200;
			Graphic::getInstance()->d3dPP.BackBufferHeight = 100;
			break;
		case 3:
			printf("(View: Bigger)\n\n");
			Graphic::getInstance()->d3dPP.BackBufferWidth = 500;
			Graphic::getInstance()->d3dPP.BackBufferHeight = 400;
			break;

		default:
			break;
		}

		Graphic::getInstance()->resetGraphic();
	}
}

void Sprite::moveSprite()
{
	keyIn = LiauWindows::getInstance()->keyIn;
	if (keyIn >= 37 && keyIn <= 40)
	{
		int bufferH = Graphic::getInstance()->d3dPP.BackBufferHeight;
		int bufferW = Graphic::getInstance()->d3dPP.BackBufferWidth;

		if (keyIn == 37)
		{
			if (spriteX >= 10)
			{
				spriteX -= 10;
			}
		}

		else if (keyIn == 38)
		{
			if (spriteY >= 10)
			{
				spriteY -= 10;
			}
		}

		else if (keyIn == 39)
		{

			if ((bufferW - spriteRect.right) > 0 && bufferW - spriteRect.right - 10)
			{
				spriteX += 10;
			}
		}

		else if (keyIn == 40)
		{
			if (bufferH - spriteRect.bottom > 0 && spriteY <= bufferH - spriteRect.bottom - 10)
			{
				spriteY += 10;
			}
		}
		printf("X:%d	Y:%d\n", spriteX, spriteY);
	}

	sprite->Draw(texture, &spriteRect, NULL, &D3DXVECTOR3(spriteX, spriteY, 0), D3DCOLOR_XRGB(255, 255, 255));
}

void Sprite::cursorDraw()
{
	int mouseX = LiauWindows::getInstance()->mouseX;
	int mouseY = LiauWindows::getInstance()->mouseY;
	sprite->Draw(cursorTexture, NULL, NULL, &D3DXVECTOR3(mouseX, mouseY, 0), D3DCOLOR_XRGB(255, 255, 255));
}

void Sprite::backgroundChange()
{
	keyIn = LiauWindows::getInstance()->keyIn;

	if (keyIn != 0)
	{
		switch (keyIn)
		{
		case 38:
			bgTexture--;
			break;

		case 40:
			bgTexture++;
			break;

		default:
			break;
		}

		if (bgTexture < 1)
		{
			bgTexture = 3;
		}

		else if (bgTexture > 3)
		{
			bgTexture = 1;
		}
	}

	switch (bgTexture)
	{
	case 1:
		sprite->Draw(texture, &spriteRect, NULL, &D3DXVECTOR3(spriteX, spriteY, 0), D3DCOLOR_XRGB(255, 255, 255));
		break;

	case 2:
		sprite->Draw(texture2, &spriteRect, NULL, &D3DXVECTOR3(spriteX, spriteY, 0), D3DCOLOR_XRGB(255, 255, 255));
		break;

	case 3:
		sprite->Draw(texture3, &spriteRect, NULL, &D3DXVECTOR3(spriteX, spriteY, 0), D3DCOLOR_XRGB(255, 255, 255));
		break;
	default:
		break;
	}
}

void Sprite::cursorColorChange()
{
	keyIn = LiauWindows::getInstance()->keyIn;
	int mouseX = LiauWindows::getInstance()->mouseX;
	int mouseY = LiauWindows::getInstance()->mouseY;

	if (keyIn != 0)
	{
		switch (keyIn)
		{
		case 37:
			cursorColor--;
			break;

		case 39:
			cursorColor++;
			break;

		default:
			break;
		}

		if (cursorColor < 1)
		{
			cursorColor = 4;
		}

		else if (cursorColor > 4)
		{
			cursorColor = 1;
		}
	}
	switch (cursorColor)
	{
	case 1:
		sprite->Draw(cursorTexture, NULL, NULL, &D3DXVECTOR3(mouseX, mouseY, 0), D3DCOLOR_XRGB(255, 255, 255));
		break;

	case 2:
		sprite->Draw(cursorTexture, NULL, NULL, &D3DXVECTOR3(mouseX, mouseY, 0), D3DCOLOR_XRGB(255, 0, 0));
		break;

	case 3:
		sprite->Draw(cursorTexture, NULL, NULL, &D3DXVECTOR3(mouseX, mouseY, 0), D3DCOLOR_XRGB(0, 255, 0));
		break;

	case 4:
		sprite->Draw(cursorTexture, NULL, NULL, &D3DXVECTOR3(mouseX, mouseY, 0), D3DCOLOR_XRGB(0, 0, 255));
		break;

	default:
		break;
	}
}