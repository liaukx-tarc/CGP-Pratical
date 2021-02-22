#include "Practical_4.h"
#include "Graphic.h"
#include "Windows.h"
#include "GameStateManager.h"

Practical_4::Practical_4()
{
	sprite = NULL;
	num = 1;
	weight = 0;
	height = 0;
}

Practical_4::~Practical_4()
{
}

void Practical_4::init()
{
	HRESULT hr = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);
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
		PostQuitMessage(0);
	}

	weight = Graphic::getInstance()->d3dPP.BackBufferWidth / 2;
	height = Graphic::getInstance()->d3dPP.BackBufferHeight / 2;
}

void Practical_4::update()
{
	int keyIn = LiauWindows::getInstance()->keyIn;

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
}

void Practical_4::draw()
{
	if (GameStateManager::getInstance()->preState == 1)
	{
		D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);
		GameStateManager::getInstance()->preState = 2;
	}

	Graphic::getInstance()->red = 64;
	Graphic::getInstance()->green = 128;
	Graphic::getInstance()->blue = 255;

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(numberTexture, &RectList[num], &D3DXVECTOR3(16, 16, 0), &D3DXVECTOR3(weight, height, 0), D3DCOLOR_XRGB(128, 0, 128));
	sprite->End();
}

void Practical_4::release()
{
	sprite->Release();
	sprite = NULL;
}