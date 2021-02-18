#ifndef GRAPHIC
#include <d3d9.h>

class Graphic
{
private:
	static Graphic* sInstance;
	Graphic();

public:
	D3DPRESENT_PARAMETERS d3dPP;
	IDirect3DDevice9 * d3dDevice;
	IDirect3D9 * direct3D9;

	int red, blue, green, speed, mode;
	bool isRMax = false;
	bool isGMax = false;
	bool isBMax = false;
	static Graphic* getInstance();
	static void releaseInsrance();

	bool createDirectX();
	void fullscreen();
	void resetGraphic();
	void present();
	void clearGraphic();

	void SetRGB();
	void MaxZero(int keyIn);
	void MaxDecrease(int keyIn);
	void MaxStop(int keyIn);
	void RandomRGB(int keyIn);
	void Speed(int keyIn);

	//practical change
	int practical;
	int prePractical;

};

#endif // !GRAPHIC

