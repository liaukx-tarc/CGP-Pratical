#include "Practical_6.h"
#include "Graphic.h"
#include "Windows.h"
#include "GameStateManager.h"
#include "DirectInput.h"

Practical_6::Practical_6()
{
	line = NULL;
	keyIn = 0;
	lineMode = 0;
	colorMode = 0;

	ZeroMemory(&mouseButton, sizeof(mouseButton));

	ZeroMemory(&lineList, sizeof(lineList));
	size = 0;

	drawing = false;
	firstPoint = false;
	mouseX = 0;
	mouseY = 0;
	mode = 0;
}

Practical_6::~Practical_6()
{

}

void Practical_6::init()
{
	HRESULT hr = D3DXCreateLine(Graphic::getInstance()->d3dDevice, &line);

	hr = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);

	hr = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 20, 0, FW_BOLD, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			textRect[i].left = 0;
			textRect[i].top = 0;
			textRect[i].right = 400;
			textRect[i].bottom = 20;
		}

		else
		{
			textRect[i].left = 0;
			textRect[i].top = textRect[i - 1].bottom;
			textRect[i].right = 400;
			textRect[i].bottom = textRect[i - 1].bottom + 20;
		}
	}

	if (FAILED(hr))
	{
		PostQuitMessage(0);
	}
}

void Practical_6::fixedUpdate()
{
}

void Practical_6::update()
{
	keyIn = LiauWindows::getInstance()->keyIn;

	for (int i = 0; i < 3; i++)
	{
		mouseButton[i] = DirectInput::getInstance()->mouseButton[i];

	}

	mouseX = LiauWindows::getInstance()->mouseX;
	mouseY = LiauWindows::getInstance()->mouseY;

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
		colorMode = 1;
	}

	else if (keyIn == 190)
	{
		lineMode = 6;
	}

	else if (keyIn == 191)
	{
		lineMode = 7;
		colorMode = 0;
	}

	if (keyIn == 38)
	{
		mode--;
	}

	else if(keyIn == 40)
	{
		mode++;
	}

	else if (keyIn == 37)
	{
		colorMode--;
	}

	else if (keyIn == 39)
	{
		colorMode++;
	}

	if (mode >= 3)
	{
		mode = 0;
	}

	else if (mode < 0)
	{
		mode = 2;
	}

	if (colorMode >= 6)
	{
		colorMode = 0;
	}

	else if (colorMode < 0)
	{
		colorMode = 5;
	}
}

void Practical_6::draw()
{
	if (GameStateManager::getInstance()->preState == 1)
	{
		D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);
		GameStateManager::getInstance()->preState = 4;
	}

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
		line->Draw(lineVertices, 2, D3DCOLOR_XRGB(red[colorMode], green[colorMode], blue[colorMode]));
		line->Draw(lineVertices2, 2, D3DCOLOR_XRGB(red[colorMode], green[colorMode], blue[colorMode]));
		line->Draw(lineVertices5, 2, D3DCOLOR_XRGB(red[colorMode], green[colorMode], blue[colorMode]));
		line->Draw(lineVertices6, 2, D3DCOLOR_XRGB(red[colorMode], green[colorMode], blue[colorMode]));
		line->Draw(lineVertices7, 2, D3DCOLOR_XRGB(red[colorMode], green[colorMode], blue[colorMode]));
		line->Draw(lineVertices8, 2, D3DCOLOR_XRGB(red[colorMode], green[colorMode], blue[colorMode]));
		break;

	case 6:
		line->Draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 255));
		line->Draw(lineVertices2, 2, D3DCOLOR_XRGB(255, 255, 0));
		line->Draw(lineVertices5, 2, D3DCOLOR_XRGB(100, 255, 255));
		line->Draw(lineVertices6, 2, D3DCOLOR_XRGB(255, 100, 255));
		line->Draw(lineVertices7, 2, D3DCOLOR_XRGB(100, 255, 100));
		line->Draw(lineVertices8, 2, D3DCOLOR_XRGB(255, 0, 0));
		break;

	case 7:
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		switch (mode)
		{
		case 0:
			font->DrawText(sprite, "Click-n-click\n", -1, &textRect[0], 0, D3DCOLOR_XRGB(255, 255, 255));
			clickDraw();
			break;

		case 1:
			font->DrawText(sprite, "Hold-n-Release\n", -1, &textRect[0], 0, D3DCOLOR_XRGB(255, 255, 255));
			dragDraw();
			break;

		case 2:
			font->DrawText(sprite, "Hold-n-Drag\n", -1, &textRect[0], 0, D3DCOLOR_XRGB(255, 255, 255));
			dragDrawView();
			break;

		default:
			break;
		}
		
		font->DrawText(sprite, "Up/Down to change drawing mode\n", -1, &textRect[1], 0, D3DCOLOR_XRGB(255, 255, 255));
		font->DrawText(sprite, "Left/Right to change color\n", -1, &textRect[2], 0, D3DCOLOR_XRGB(255, 255, 255));
		sprite->End();
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

	font->Release();
	font = NULL;

	sprite->Release();
	sprite = NULL;
}

void Practical_6::clickDraw()
{
	if (size < LINE_SIZE)
	{
		if (mouseButton[0] == 1 && !drawing)
		{
			lineList[size][0] = D3DXVECTOR2(mouseX / 2.7, mouseY / 2.4); //my scene is 1080x720 but buffer is 400x300 so need to fix
			drawing = true;
		}

		else if (mouseButton[0] == 1 && drawing)
		{
			lineList[size][1] = D3DXVECTOR2(mouseX / 2.7, mouseY / 2.4);
			drawing = false;
			size++;
		}
	}

	else
	{
		printf("Over\n");
	}

	for (int i = 0; i < size; i++)
	{
		line->Draw(lineList[i], 2, D3DCOLOR_XRGB(red[colorMode], green[colorMode], blue[colorMode]));
	}
}

void Practical_6::dragDraw()
{
	if (size < LINE_SIZE)
	{
		if (mouseButton[0] == 1 && !drawing)
		{
			lineList[size][0] = D3DXVECTOR2(mouseX / 2.7, mouseY / 2.4); //my scene is 1080x720 but buffer is 400x300 so need to fix
			drawing = true;
		}
		
		else if (mouseButton[0] == 0 && drawing)
		{
			lineList[size][1] = D3DXVECTOR2(mouseX / 2.7, mouseY / 2.4); //my scene is 1080x720 but buffer is 400x300 so need to fix
			drawing = false;
			size++;
		}
	}

	else
	{
		printf("Over\n");
	}

	for (int i = 0; i < size; i++)
	{
		line->Draw(lineList[i], 2, D3DCOLOR_XRGB(red[colorMode], green[colorMode], blue[colorMode]));
	}
}

void Practical_6::dragDrawView()
{
	if (size < LINE_SIZE)
	{
		if (mouseButton[0] == 1 && !drawing)
		{
			lineList[size][0] = D3DXVECTOR2(mouseX / 2.7, mouseY / 2.4); //my scene is 1080x720 but buffer is 400x300 so need to fix
			drawing = true;
			firstPoint = true;
		}

		else if (mouseButton[0] == 2 && drawing)
		{
			firstPoint = false;
			lineList[size][1] = D3DXVECTOR2(mouseX / 2.7, mouseY / 2.4); //my scene is 1080x720 but buffer is 400x300 so need to fix
		}

		else if (mouseButton[0] == 0 && drawing)
		{
			size++;
			drawing = false;
		}
	}

	else
	{
		printf("Over\n");
	}

	for (int i = 0; i < size; i++)
	{
		line->Draw(lineList[i], 2, D3DCOLOR_XRGB(red[colorMode], green[colorMode], blue[colorMode]));
	}

	if (!firstPoint)
	{
		line->Draw(lineList[size], 2, D3DCOLOR_XRGB(red[colorMode], green[colorMode], blue[colorMode]));
	}
}