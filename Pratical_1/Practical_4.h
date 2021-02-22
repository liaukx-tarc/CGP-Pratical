#ifndef PRACTICAL4
#include <d3dx9.h>
#include "GameState.h"

class Practical_4 : public GameState
{
public:
	Practical_4();
	~Practical_4();

	LPD3DXSPRITE sprite;
	RECT RectList[16];
	LPDIRECT3DTEXTURE9 numberTexture;

	int num, weight, height;

	void init();
	void update();
	void draw();
	void release();


};

#endif // !PRACTICAL4

