#include "Practical_6.h"
#include "Graphic.h"
#include "Windows.h"
#include "GameStateManager.h"

Practical_6::Practical_6()
{
	line = NULL;
	keyIn = 0;
	lineMode = 0;
	red = 255;
	green = 255;
	blue = 255;
}

Practical_6::~Practical_6()
{

}

void Practical_6::init()
{
	HRESULT hr = D3DXCreateLine(Graphic::getInstance()->d3dDevice, &line);

	if (FAILED(hr))
	{
		PostQuitMessage(0);
	}
}

void Practical_6::update()
{
	keyIn = LiauWindows::getInstance()->keyIn;
	if (keyIn == 219)
	{
		lineMode = 0;
	}

	else if (keyIn == 221)
	{
		lineMode = 1;
	}

	else if (keyIn == 220)
	{
		lineMode = 2;
	}

	else if(keyIn == 186)
	{
		lineMode = 3;
	}

	else if (keyIn == 222)
	{
		lineMode = 4;
	}

	else if (keyIn == 188)
	{
		lineMode = 5;
		red = 255;
		green = 0;
		blue = 255;
	}

	else if (keyIn == 190)
	{
		lineMode = 6;
	}
}

void Practical_6::draw()
{
	//clear line sprite
	if (GameStateManager::getInstance()->preState == 1)
	{
		D3DXCreateLine(Graphic::getInstance()->d3dDevice, &line);
		GameStateManager::getInstance()->preState = 4;
	}

	//vertical
	D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2(200, 50), D3DXVECTOR2(200, 200) };
	D3DXVECTOR2 lineVertices2[] = { D3DXVECTOR2(150, 50), D3DXVECTOR2(150, 200) };
	D3DXVECTOR2 lineVertices5[] = { D3DXVECTOR2(250, 50), D3DXVECTOR2(250, 200) };
	D3DXVECTOR2 lineVertices6[] = { D3DXVECTOR2(300, 50), D3DXVECTOR2(300, 200) };

	//horizontal
	D3DXVECTOR2 lineVertices3[] = { D3DXVECTOR2(100, 100), D3DXVECTOR2(250, 100) };
	D3DXVECTOR2 lineVertices4[] = { D3DXVECTOR2(100, 150), D3DXVECTOR2(250, 150) };
	D3DXVECTOR2 lineVertices7[] = { D3DXVECTOR2(100, 100), D3DXVECTOR2(350, 100) };
	D3DXVECTOR2 lineVertices8[] = { D3DXVECTOR2(100, 150), D3DXVECTOR2(350, 150) };

	//triangle
	D3DXVECTOR2 lineVertices9[] = { D3DXVECTOR2(30, 125), D3DXVECTOR2(60, 175), D3DXVECTOR2(30, 175),D3DXVECTOR2(30, 125) };

	line->Begin();
	switch (lineMode)
	{
	case 0:
		line->Draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 255));
		break;

	case 1:
		line->Draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 255));
		line->Draw(lineVertices2, 2, D3DCOLOR_XRGB(255, 255, 255));
		break;

	case 2:
		line->Draw(lineVertices9, 4, D3DCOLOR_XRGB(255, 255, 255));
		break;

	case 3:
		line->Draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 255));
		line->Draw(lineVertices2, 2, D3DCOLOR_XRGB(255, 255, 255));
		line->Draw(lineVertices3, 2, D3DCOLOR_XRGB(255, 255, 255));
		line->Draw(lineVertices4, 2, D3DCOLOR_XRGB(255, 255, 255));
		break;

	case 4:
		line->Draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 255));
		line->Draw(lineVertices2, 2, D3DCOLOR_XRGB(255, 255, 255));
		line->Draw(lineVertices5, 2, D3DCOLOR_XRGB(255, 255, 255));
		line->Draw(lineVertices6, 2, D3DCOLOR_XRGB(255, 255, 255));
		line->Draw(lineVertices7, 2, D3DCOLOR_XRGB(255, 255, 255));
		line->Draw(lineVertices8, 2, D3DCOLOR_XRGB(255, 255, 255));
		break;

	case 5:
		line->Draw(lineVertices, 2, D3DCOLOR_XRGB(red, green, blue));
		line->Draw(lineVertices2, 2, D3DCOLOR_XRGB(red, green, blue));
		line->Draw(lineVertices5, 2, D3DCOLOR_XRGB(red, green, blue));
		line->Draw(lineVertices6, 2, D3DCOLOR_XRGB(red, green, blue));
		line->Draw(lineVertices7, 2, D3DCOLOR_XRGB(red, green, blue));
		line->Draw(lineVertices8, 2, D3DCOLOR_XRGB(red, green, blue));
		break;

	case 6:
		line->Draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 255));
		line->Draw(lineVertices2, 2, D3DCOLOR_XRGB(255, 255, 0));
		line->Draw(lineVertices5, 2, D3DCOLOR_XRGB(100, 255, 255));
		line->Draw(lineVertices6, 2, D3DCOLOR_XRGB(255, 100, 255));
		line->Draw(lineVertices7, 2, D3DCOLOR_XRGB(100, 255, 100));
		line->Draw(lineVertices8, 2, D3DCOLOR_XRGB(255, 0, 0));
		break;

	default:
		break;
	}
	line->End();

}

void Practical_6::release()
{
	line->Release();
	line = NULL;
	
}
