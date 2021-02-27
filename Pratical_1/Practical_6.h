#ifndef PRACTICAL6
#include <d3dx9.h>
#include <vector>
#include <stdio.h>
#include "GameState.h"

#define LINE_SIZE 100

class Practical_6: public GameState
{
public:
	Practical_6();
	~Practical_6();

	LPD3DXLINE line;
	D3DXVECTOR2 lineList[LINE_SIZE][2];

	LPD3DXSPRITE sprite;
	LPD3DXFONT font;
	RECT textRect[3];

	int keyIn, lineMode, size, mouseX, mouseY, mouseButton[3], mode, colorMode;
	bool drawing, firstPoint;

	int red[6] = { 255,255,0,0,255,127 };
	int green[6] = { 255,0,255,0,255,0 };
	int blue[6] = { 255,0,0,255,0,255 };

	void init();
	void update();
	void draw();
	void release();

	void clickDraw();
	void dragDraw();
	void dragDrawView();
};

#endif // !PRACTICAL6



