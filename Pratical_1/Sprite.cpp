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
	practical = 1;
}

bool Sprite::createSprite()
{
	//Practical 3
	HRESULT hr = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);

	hr = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/bg1.png", &texture);
	hr = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/bg2.png", &texture2);
	hr = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/bg3.png", &texture3);
	hr = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/pointer.png", &cursorTexture);

	//Rect
	spriteRect.left = spriteRect.top = 0;
	spriteRect.right = 400;
	spriteRect.bottom = 300;


	//Pratical 4
	hr = D3DXCreateTextureFromFileEx(Graphic::getInstance()->d3dDevice, "resource/numbers.bmp", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 128, 0), //change the XRGB to ignore the color
		NULL, NULL, &numberTexture);

	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			RectList[r * 4 + c].left = 32 * c;
			RectList[r * 4 + c].top = 32 * r;
			RectList[r * 4 + c].right = 32 * c + 32;
			RectList[r * 4 + c].bottom = 32 * r + 32;
		}
	}

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void Sprite::drawSprite()
{
	keyIn = LiauWindows::getInstance()->keyIn;
	if (keyIn != 0)
	{
		practical = LiauWindows::getInstance()->practical;
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

	if (practical == 3)
	{
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
			break;

		default:
			break;
		}
	}
	
	else if (practical == 4)
	{
		drawNum();
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
	if (keyIn == 188 || keyIn == 190 || keyIn==191)
	{
		if (keyIn == 188)
		{
			viewMode = 1;
		}

		else if (keyIn == 190)
		{
			viewMode = 2;
		}

		else
		{
			viewMode = 3;
		}
		
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

void Sprite::drawNum()
{
	keyIn = LiauWindows::getInstance()->keyIn;
	int weight = Graphic::getInstance()->d3dPP.BackBufferWidth / 2;
	int hight = Graphic::getInstance()->d3dPP.BackBufferHeight / 2;

	if (keyIn != 0)
	{
		if (keyIn >= 48 && keyIn <= 57)
		{
			num = keyIn - 48;
		}

		else if (keyIn == 110)
		{
			num = 10;
		}

		else if (keyIn == 187)
		{
			num = 11;
		}

		else if (keyIn == 107)
		{
			num = 12;
		}

		else if (keyIn == 109)
		{
			num = 13;
		}

		else if (keyIn == 106)
		{
			num = 14;
		}

		else if (keyIn == 111)
		{
			num = 15;
		}
	}

	Graphic::getInstance()->red = 64;
	Graphic::getInstance()->green = 128;
	Graphic::getInstance()->blue = 255;
	sprite->Draw(numberTexture, &RectList[num], &D3DXVECTOR3(16, 16, 0), &D3DXVECTOR3(weight, hight, 0), D3DCOLOR_XRGB(128, 0, 128));
}