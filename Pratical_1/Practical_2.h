#ifndef PRACTICAL2
#include "GameState.h"

class Practical_2:	public GameState
{
public:
	Practical_2();
	~Practical_2();

	int keyIn, speed, mode, red, green, blue;
	bool isRMax = false;
	bool isGMax = false;
	bool isBMax = false;

	void init();
	void fixedUpdate();
	void update();
	void draw();
	void release();

	void fullscreen();
	void SetRGB();
	void MaxZero();
	void MaxDecrease();
	void MaxStop();
	void RandomRGB();
	void Speed();
};

#endif // !PRACTICAL2



