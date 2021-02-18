#ifndef SPRITE
#include <d3dx9.h>

class Sprite
{
private:
	static Sprite* sInstance;
	Sprite();

public:
	static Sprite* getInstance();
	static void releaseInsrance();

	//Practical 3
	RECT spriteRect;

	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DTEXTURE9 texture2;
	LPDIRECT3DTEXTURE9 texture3;
	LPDIRECT3DTEXTURE9 cursorTexture;
	LPD3DXSPRITE sprite;
	
	int viewMode,changeMode;
	int spriteX, spriteY, keyIn, bgTexture, cursorColor;

	bool createSprite();
	void drawSprite();
	void clearSprite();
	void changeView();
	void moveSprite();
	void cursorDraw();
	void backgroundChange();
	void cursorColorChange();

	//Practical 4
	RECT RectList[16];
	LPDIRECT3DTEXTURE9 numberTexture;

	int num;

	void drawNum();

	//practical change
	int practical;
};


#endif // !SPRITE

