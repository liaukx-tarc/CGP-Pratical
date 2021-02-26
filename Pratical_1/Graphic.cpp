#include <d3dx9.h>
#include "Graphic.h"
#include "Windows.h"
#include "GameStateManager.h"

//singleton
Graphic* Graphic::sInstance = NULL;

Graphic* Graphic::getInstance()
{
	if (Graphic::sInstance == NULL)
	{
		sInstance = new Graphic;
	}

	return sInstance;
}

void Graphic::releaseInsrance()
{
	delete sInstance;
	sInstance = NULL;
}

Graphic::Graphic()
{
	ZeroMemory(&d3dPP, sizeof(d3dPP));
	d3dDevice = NULL;
	direct3D9 = NULL;
	
}

void Graphic::createDirectX()
{
	direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = 400;
	d3dPP.BackBufferHeight = 300;
	d3dPP.hDeviceWindow = LiauWindows::getInstance()->g_hWnd;

	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, LiauWindows::getInstance()->g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

	if (FAILED(hr))
	{
		PostQuitMessage(0);
	}
}



void Graphic::resetGraphic()
{
	if (FAILED(d3dDevice->Reset(&d3dPP)))
	{
		PostQuitMessage(0);
	}
}

void Graphic::present()
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(red, green, blue), 1.0f, 0);

	d3dDevice->BeginScene();

	GameStateManager::getInstance()->draw();

	d3dDevice->EndScene();

	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Graphic::clearGraphic()
{
	Graphic::getInstance()->d3dDevice->Release();
	Graphic::getInstance()->d3dDevice = NULL;
}