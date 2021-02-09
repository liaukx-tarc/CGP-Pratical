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
	LPDIRECT3DTEXTURE9 cursorTexture;

	LPD3DXSPRITE sprite;
	
	int viewMode;

	static Sprite* getInstance();
	static void releaseInsrance();
	int spriteX, spriteY, keyIn;

	bool createSprite();
	void drawSprite();
	void clearSprite();
	void changeView();
	void moveSprite();
	void cursorDraw();

};


#endif // !SPRITE

