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

	bool createDirectX();
	void resetGraphic();
	void present();
	void clearGraphic();
};

#endif // !GRAPHIC

