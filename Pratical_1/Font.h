#ifndef FONT
#include <d3dx9.h>
#include <string>

class Font
{
private:
	static Font* sInstance;
	Font();

public:
	static Font* getInstance();
	static void releaseInsrance();

	LPD3DXSPRITE sprite;
	LPD3DXFONT font[6];
	RECT lineRect;
	RECT textRect[6];

	bool msgFull, msgNull;
	int keyIn, fontMode, lineCount, wordCount[12];
	std::string string, lineString;

	bool createFont();
	void write();
	void clearFont();

	void inputWrite();

};

#endif // !GRAPHIC

