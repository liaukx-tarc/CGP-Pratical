#include "Practical_7.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "Graphic.h"
#include "DirectInput.h"

Practical_7::Practical_7()
{
	charSprite = NULL;
	charTexture = NULL;
	ZeroMemory(&mat, sizeof(mat));
	ZeroMemory(&charSize, sizeof(charSize));
	ZeroMemory(&charSize, sizeof(charDirection));
	ZeroMemory(&charSize, sizeof(charPosition));
	ZeroMemory(&charSize, sizeof(charVelocity));
	ZeroMemory(&charRect, sizeof(charRect));

	charFrame = 0;
	frameNum = 0;
	charState = 0;
	frameRate = 1.0f / frameNum;
	frameTimer = 0;
	animationSpeed = 0;
	charSpeed = 0;

	isMoving = false;
}

Practical_7::~Practical_7()
{

}

void Practical_7::init()
{
	hr = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &charSprite);
	hr = D3DXCreateTextureFromFileEx(Graphic::getInstance()->d3dDevice, "resource/militia.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), //change the XRGB to ignore the color
		NULL, NULL, &charTexture);

	if (FAILED(hr))
	{
		PostQuitMessage(0);
	}

	charSize.x = 32;
	charSize.y = 48;

	charFrame = 0;
	frameNum = 4;
	animationSpeed = 12;
	frameRate = 1.0f / animationSpeed;
	frameTimer = 0;

	charSpeed = 0;
	charDirection.y = 1;

	charRect->top = 0;
	charRect->bottom = charRect->top + charSize.y;
	charRect->left = charSize.x * charFrame;
	charRect->right = charRect->left + charSize.x;
}

void Practical_7::fixedUpdate()
{
	if (isMoving)
	{
		charSpeed++;
	}

	if (charSpeed > 0)
	{
		animationSpeed = charSpeed / 2;
		animationSpeed = max(animationSpeed, 4);
		animationSpeed = min(animationSpeed, 20);
		frameRate = 1.0f / animationSpeed;
		frameTimer += 1.0f / 60;

		if (!isMoving)
		{
			charSpeed--;
			charSpeed = max(charSpeed, 0);
			animationSpeed = min(charSpeed, 40);
		}
	}

	charVelocity = charDirection * (charSpeed / 60.0f);
	charPosition += charVelocity;

	if (frameTimer >= frameRate)
	{
		frameTimer -= frameRate;
		charFrame++;
		charFrame %= frameNum;
	}

	charRect->top = charSize.y * charState;
	charRect->bottom = charRect->top + charSize.y;
	charRect->left = charSize.x * charFrame;
	charRect->right = charRect->left + charSize.x;

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, 0, &charPosition);
}

void Practical_7::update()
{
	if (DirectInput::getInstance()->diKeys[DIK_UP] && DirectInput::getInstance()->diKeys[DIK_LEFT])
	{
		charState = 1;
		charDirection.x = -1;
		charDirection.y = -1;
		isMoving = true;
	}

	else if (DirectInput::getInstance()->diKeys[DIK_DOWN] && DirectInput::getInstance()->diKeys[DIK_RIGHT])
	{
		charState = 2;
		charDirection.x = 1;
		charDirection.y = 1;
		isMoving = true;
	}

	else if (DirectInput::getInstance()->diKeys[DIK_UP])
	{
		charState = 3;
		charDirection.x = 0;
		charDirection.y = -1;
		isMoving = true;
	}

	else if (DirectInput::getInstance()->diKeys[DIK_DOWN])
	{
		charState = 0;
		charDirection.x = 0;
		charDirection.y = 1;
		isMoving = true;
	}

	else if (DirectInput::getInstance()->diKeys[DIK_LEFT])
	{
		charState = 1;
		charDirection.x = -1;
		charDirection.y = 0;
		isMoving = true;
	}

	else if (DirectInput::getInstance()->diKeys[DIK_RIGHT])
	{
		charState = 2;
		charDirection.x = 1;
		charDirection.y = 0;
		isMoving = true;
	}

	else
	{
		isMoving = false;
	}
}

void Practical_7::draw()
{
	if (GameStateManager::getInstance()->preState == 1)
	{
		D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &charSprite);
		GameStateManager::getInstance()->preState = 5;
	}

	Graphic::getInstance()->red = 0;
	Graphic::getInstance()->green = 0;
	Graphic::getInstance()->blue = 0;

	charSprite->Begin(D3DXSPRITE_ALPHABLEND);
	charSprite->SetTransform(&mat);
	charSprite->Draw(charTexture, charRect, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_XRGB(255, 255, 255));
	charSprite->End();
}

void Practical_7::release()
{
	charSprite->Release();
	charSprite = NULL;

	charTexture->Release();
	charTexture = NULL;
}
