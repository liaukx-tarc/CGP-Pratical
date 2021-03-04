#include "Practical_2.h"
#include "Windows.h"
#include "Graphic.h"

Practical_2::Practical_2()
{
	red = 0;
	green = 0;
	blue = 0;
	keyIn = 0;
	speed = 1;
	mode = 1;
}

Practical_2::~Practical_2()
{
}

void Practical_2::init()
{
}

void Practical_2::fixedUpdate()
{
}

void Practical_2::update()
{
	keyIn = LiauWindows::getInstance()->keyIn;
	fullscreen();
	SetRGB();
	Graphic::getInstance()->red = red;
	Graphic::getInstance()->green = green;
	Graphic::getInstance()->blue = blue;
}

void Practical_2::draw()
{

}

void Practical_2::release()
{

}

void Practical_2::fullscreen()
{
	if (keyIn == 70)
	{
		D3DPRESENT_PARAMETERS d3dPP;

		if (Graphic::getInstance()->d3dPP.Windowed == true)
		{
			d3dPP.Windowed = false;
			d3dPP.BackBufferWidth = 1920;
			d3dPP.BackBufferHeight = 1080;
		}

		else if (Graphic::getInstance()->d3dPP.Windowed == false)
		{
			d3dPP.Windowed = true;
			d3dPP.BackBufferWidth = 400;
			d3dPP.BackBufferHeight = 300;
		}

		Graphic::getInstance()->d3dPP.Windowed = d3dPP.Windowed;
		Graphic::getInstance()->d3dPP.BackBufferWidth = d3dPP.BackBufferWidth;
		Graphic::getInstance()->d3dPP.BackBufferHeight = d3dPP.BackBufferHeight;

		Graphic::getInstance()->resetGraphic();
	}
}

void Practical_2::SetRGB()
{
	//Default color
	if (keyIn == 68)
	{
		red = 0;
		green = 0;
		blue = 0;
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

	Speed();

	//change mode
	switch (mode)
	{
	case 1:
		MaxZero();
		break;

	case 2:
		MaxDecrease();
		break;

	case 3:
		MaxStop();
		break;

	case 4:
		RandomRGB();
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

	if (keyIn != 0)
	{
		printf("speed-%d R-%d G-%d B-%d\n", speed,
											Graphic::getInstance()->red,
											Graphic::getInstance()->green,
											Graphic::getInstance()->blue);
	}
}

//Mode: Maximum become zero
void Practical_2::MaxZero()
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
void Practical_2::MaxDecrease()
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
void Practical_2::MaxStop()
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
void Practical_2::RandomRGB()
{
	if (keyIn == 82)
	{
		red = rand() % 255;
		green = rand() % 255;
		blue = rand() % 255;
	}
}

// +/- speed
void Practical_2::Speed()
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