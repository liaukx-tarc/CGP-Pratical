#pragma once
#include <d3dx9.h>
#include "GameState.h"

class Practical_7 : public GameState
{
public:
	Practical_7();
	~Practical_7();

	HRESULT hr;

	LPD3DXSPRITE charSprite;
	RECT charRect[16];
	LPDIRECT3DTEXTURE9 charTexture;
	D3DXVECTOR2 charSize, charDirection, charPosition, charVelocity;
	D3DXMATRIX mat;
	int frameNum, charFrame, charState;
	float frameRate, frameTimer, animationSpeed, charSpeed;
	bool isMoving;

	void init();
	void fixedUpdate();
	void update();
	void draw();
	void release();
};

