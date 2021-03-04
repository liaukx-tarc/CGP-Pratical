#ifndef G_TIME
#include <Windows.h>

class GTime {

public:
	GTime();
	~GTime();
	void init(int);
	int framesToUpdate();

private:
	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeNow;
	LARGE_INTEGER timePrevious;
	int Requested_FPS, frameToUpdate;
	float intervalsPerFrame, intervalsSinceLastUpdate;

};
#endif // !G_TIME