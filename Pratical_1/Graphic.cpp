#include "Graphic.h"
#include "Windows.h"
#include "Sprite.h"

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
	ZeroMemory(&d3dPP, sizeof(d3dPP));;
	d3dDevice = NULL;
	direct3D9 = NULL;
}

bool Graphic::createDirectX()
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
		return false;
	}

	return true;
}

void Graphic::fullscreen()
{
	if (LiauWindows::getInstance()->keyIn == 70)
	{
		if (d3dPP.Windowed == true)
		{
			d3dPP.Windowed = false;
			d3dPP.BackBufferWidth = 1920;
			d3dPP.BackBufferHeight = 1080;
		}

		else if (d3dPP.Windowed == false)
		{
			d3dPP.Windowed = true;
			d3dPP.BackBufferWidth = 400;
			d3dPP.BackBufferHeight = 300;
		}
		resetGraphic();
	}
}

void Graphic::resetGraphic()
{
	Sprite::getInstance()->sprite->Release();
	Sprite::getInstance()->sprite = NULL;

	if (FAILED(d3dDevice->Reset(&d3dPP) ||
		D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &Sprite::getInstance()->sprite)))
	{
		PostQuitMessage(0);
	}
}

void Graphic::present()
{
	if (LiauWindows::getInstance()->keyIn != 0)
	{
		fullscreen();
		//SetRGB();
		Sprite::getInstance()->changeView();
	}
	
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(red, green, blue), 1.0f, 0);

	d3dDevice->BeginScene();

	Sprite::getInstance()->drawSprite();

	d3dDevice->EndScene();

	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Graphic::clearGraphic()
{
	Graphic::getInstance()->d3dDevice->Release();
	Graphic::getInstance()->d3dDevice = NULL;
}

void Graphic::SetRGB()
{
	int keyIn = LiauWindows::getInstance()->keyIn;
	//Default color
	if (keyIn == 68)
	{
		Graphic::getInstance()->red = 0;
		Graphic::getInstance()->green = 0;
		Graphic::getInstance()->blue = 0;
	}

	//Change Mode
	else if (keyIn >= 49 && keyIn <= 52)
	{
		mode = keyIn - 48;

		switch (mode)
		{
		case 1:
			printf("\n(Mode: Maximum become 0)\n");
			break;

		case 2:
			printf("\n(Mode: Maximum become decrease)\n");
			break;

		case 3:
			printf("\n(Mode: Maximum/Minimum stop)\n");
			break;

		case 4:
			printf("\n(Mode: Random color)\n");
			break;

		default:
			break;
		}
	}

	Speed(keyIn);

	//change mode
	switch (mode)
	{
	case 1:
		MaxZero(keyIn);
		break;

	case 2:
		MaxDecrease(keyIn);
		break;

	case 3:
		MaxStop(keyIn);
		break;

	case 4:
		RandomRGB(keyIn);
		break;

	default:
		break;
	}

	if (red > 255)
		red = 255;

	else if (red < 0)
		red = 0;

	if (green > 255)
		green = 255;

	else if (green < 0)
		green = 0;

	if (blue > 255)
		blue = 255;

	else if (blue < 0)
		blue = 0;
}

//Mode: Maximum become zero
void Graphic::MaxZero(int keyIn)
{
	if (keyIn == 82)
	{
		red += speed;

		if (red < 0)
		{
			red = 255;
		}

		else if (red > 255)
		{
			red = 0;
		}
	}

	else if (keyIn == 71)
	{
		green += speed;

		if (green < 0)
		{
			green = 255;
		}

		else if (green > 255)
		{
			green = 0;
		}
	}

	else if (keyIn == 66)
	{
		blue += speed;

		if (blue < 0)
		{
			blue = 255;
		}

		else if (blue > 255)
		{
			blue = 0;
		}
	}
}

//Mode: Maximum decrease
void Graphic::MaxDecrease(int keyIn)
{
	if (keyIn == 82)
	{
		if (isRMax == false)
		{
			red += speed;

			if (red > 255)
			{
				isRMax = true;
			}
		}

		else
		{
			red -= speed;

			if (red < 0)
			{
				isRMax = false;
			}
		}
	}

	else if (keyIn == 71)
	{
		if (isGMax == false)
		{
			green += speed;

			if (green > 255)
			{
				isGMax = true;
			}
		}

		else
		{
			green -= speed;

			if (green < 0)
			{
				isGMax = false;
			}
		}
	}

	else if (keyIn == 66)
	{
		if (isBMax == false)
		{
			blue += speed;

			if (blue > 255)
			{
				isBMax = true;
			}
		}

		else
		{
			blue -= speed;

			if (blue < 0)
			{
				isBMax = false;
			}
		}
	}

}

//Mode: Maximum/Minimum stop
void Graphic::MaxStop(int keyIn)
{
	//red++
	if (keyIn == 82)
	{

		if (red >= 255)
		{
			printf("red is Maximum\n");
		}

		else
		{
			red += speed;
		}
	}
	//red--
	else if (keyIn == 84)
	{

		if (red <= 0)
		{
			printf("red is Minimum\n");
		}

		else
		{
			red -= speed;
		}
	}

	//green++
	else if (keyIn == 71)
	{
		if (green >= 255)
		{
			printf("green is Maximum\n");
		}

		else
		{
			green += speed;
		}
	}

	//green--
	else if (keyIn == 72)
	{
		if (green <= 0)
		{
			printf("green is Minimum\n");
		}

		else
		{
			green -= speed;
		}
	}

	//blue++
	else if (keyIn == 66)
	{
		if (blue >= 255)
		{
			printf("blue is Maximum\n");
		}

		else
		{
			blue += speed;
		}
	}

	//blue--
	else if (keyIn == 78)
	{
		if (blue <= 0)
		{
			printf("blue is Minimum\n");
		}

		else
		{
			blue -= speed;
		}
	}
}

//Mode: Random color
void Graphic::RandomRGB(int keyIn)
{
	if (keyIn == 82)
	{
		red = rand() % 255;
		green = rand() % 255;
		blue = rand() % 255;
	}
}

// +/- speed
void Graphic::Speed(int keyIn)
{
	if (keyIn == 73 && speed < 10)
	{
		printf("Speed++\n");
		speed++;
	}
			
	else if (keyIn == 79 && speed > 0)
	{
		printf("Speed--\n");
		speed--;
	}
}