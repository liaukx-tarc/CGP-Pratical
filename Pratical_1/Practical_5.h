#ifndef PRACTICAL5
#include <d3dx9.h>
#include <string>
#include "GameState.h"

class Practical_5:	public GameState
{
public:
	Practical_5();
	~Practical_5();

	LPD3DXSPRITE sprite;
	LPD3DXFONT font[6];
	RECT lineRect;
	RECT textRect[6];

	bool msgFull, msgNull;
	int keyIn, fontMode, lineCount, wordCount[12];
	std::string string, lineString;

	void init();
	void update();
	void draw();
	void release();

	void inputWrite();


};

#endif // !PRACTICAL5



