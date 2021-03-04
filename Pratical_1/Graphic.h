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

	int red, blue, green;

	static Graphic* getInstance();
	static void releaseInsrance();

	void createDirectX();
	void present();
	void clearGraphic();

	void resetGraphic();
};

#endif // !GRAPHIC

