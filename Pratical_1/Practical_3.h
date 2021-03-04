#ifndef PRACTICAL3
#include <d3dx9.h>
#include "GameState.h"

class Practical_3: public GameState
{
public:
	Practical_3();
	~Practical_3();

	//Practical 3
	RECT spriteRect;

	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DTEXTURE9 texture2;
	LPDIRECT3DTEXTURE9 texture3;
	LPDIRECT3DTEXTURE9 cursorTexture;
	LPD3DXSPRITE sprite;

	int viewMode, changeMode;
	int spriteX, spriteY, mouseX, mouseY, keyIn, bgTexture, cursorColor;

	void init();
	void fixedUpdate();
	void update();
	void draw();
	void release();

	void changeView();
	void moveSprite();
	void cursorDraw();
	void backgroundChange();
	void cursorColorChange();
};

#endif // !PRACTICAL2
