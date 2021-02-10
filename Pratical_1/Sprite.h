#ifndef SPRITE
#include <d3dx9.h>

class Sprite
{
private:
	static Sprite* sInstance;
	Sprite();

public:
	RECT spriteRect;

	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DTEXTURE9 texture2;
	LPDIRECT3DTEXTURE9 texture3;
	LPDIRECT3DTEXTURE9 cursorTexture;

	LPD3DXSPRITE sprite;
	
	int viewMode,changeMode;

	static Sprite* getInstance();
	static void releaseInsrance();
	int spriteX, spriteY, keyIn, bgTexture, cursorColor;

	bool createSprite();
	void drawSprite();
	void clearSprite();
	void changeView();
	void moveSprite();
	void cursorDraw();
	void backgroundChange();
	void cursorColorChange();

};


#endif // !SPRITE

