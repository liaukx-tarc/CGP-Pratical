#ifndef PRACTICAL6
#include <d3dx9.h>
#include "GameState.h"

class Practical_6: public GameState
{
public:
	Practical_6();
	~Practical_6();

	LPD3DXLINE line;
	int keyIn, lineMode, red, green, blue;

	void init();
	void update();
	void draw();
	void release();

};

#endif // !PRACTICAL6



