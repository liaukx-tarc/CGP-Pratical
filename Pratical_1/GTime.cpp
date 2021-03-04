#include "GTime.h"

GTime::GTime()
{
	Requested_FPS = 0;
	frameToUpdate = 0;
	intervalsPerFrame = 0;
	intervalsSinceLastUpdate = 0;
}

GTime::~GTime()
{

}

void GTime::init(int fps)
{
	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&timeNow);
	QueryPerformanceCounter(&timePrevious);

	//init fps time info
	Requested_FPS = fps;

	//The number of intervals in the given

	//timer, per frame at the requested rate.
	intervalsPerFrame = ((float)timerFreq.QuadPart / Requested_FPS);
}

int GTime::framesToUpdate() {
	frameToUpdate = 0;
	QueryPerformanceCounter(&timeNow);

	//getting the delta time
	intervalsSinceLastUpdate = (float)timeNow.QuadPart - (float)timePrevious.QuadPart;
	frameToUpdate = (int)(intervalsSinceLastUpdate /intervalsPerFrame);

	//If we are not updating any frames,

	//keep the old previous timer count
	if (frameToUpdate != 0)
	{
		QueryPerformanceCounter(&timePrevious);
	}

	return frameToUpdate;
}