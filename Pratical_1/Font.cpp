#include "Font.h"
#include "Graphic.h"
#include "Windows.h"

Font* Font::sInstance = NULL;

Font::Font()
{
	for (int i = 0; i < 6; i++)
	{
		font[i] = NULL;
	}
	keyIn = 0;
	fontMode = 1;
	lineCount = 1;
	for (int i = 0; i < 12; i++)
	{
		wordCount[i] = 0;
	}
	msgFull = false;
	msgNull = false;
}

Font* Font::getInstance()
{
	if (Font::sInstance == NULL)
	{
		sInstance = new Font;
	}

	return sInstance;
}

void Font::releaseInsrance()
{
	delete sInstance;
	sInstance = NULL;
}

bool Font::createFont()
{
	HRESULT hr = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);

	hr = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 25, 0, 0, 1, false,
								DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
								DEFAULT_PITCH | FF_DONTCARE, "Arial", &font[0]);

	hr = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 35, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font[1]);

	hr = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 25, 20, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font[2]);

	hr = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 25, 0, FW_BOLD, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font[3]);

	hr = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 25, 0, 0, 1, true,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font[4]);

	hr = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Times New Roman", &font[5]);

	for (int i = 0; i < 6; i++)
	{
		if (i == 0)
		{
			textRect[i].left = 0;
			textRect[i].top = 0;
			textRect[i].right = 400;
			textRect[i].bottom = 40;
		}

		else
		{
			textRect[i].left = 0;
			textRect[i].top = textRect[i - 1].bottom;
			textRect[i].right = 400;
			textRect[i].bottom = textRect[i - 1].bottom + 40;
		}	
	}

	lineRect.left = 250;
	lineRect.top = 250;
	lineRect.right = 400;
	lineRect.bottom = 300;
	

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void Font::write()
{
	keyIn = LiauWindows::getInstance()->keyIn;

	if (keyIn == 219)
	{
		fontMode = 1;
	}

	else if (keyIn == 221)
	{
		fontMode = 2;
	}

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	switch (fontMode)
	{
	case 1:
		for (int i = 0; i < 6; i++)
		{
			font[i]->DrawText(sprite, "Hello Me\n", -1, &textRect[i], 0, D3DCOLOR_XRGB(255, 0, 0));
		}

		break;
	case 2:
		inputWrite();
		font[0]->DrawText(sprite, string.c_str(), -1, &textRect[0], 0, D3DCOLOR_XRGB(255, 0, 0));
		font[0]->DrawText(sprite, lineString.c_str(), -1, &lineRect, 0, D3DCOLOR_XRGB(255, 0, 0));
		break;

	default:
		break;
	}

	sprite->End();
}

void Font::clearFont()
{
	for (int i = 0; i < 0; i++)
	{
		font[i]->Release();
		font[i] = NULL;
	}
}

void Font::inputWrite()
{
	keyIn = LiauWindows::getInstance()->keyIn;

	lineString = "Line Count: " + std::to_string(lineCount);

	if (msgFull == false)
	{
		if (keyIn >= 65 && keyIn <= 90)
		{
			msgNull = false;
			if (wordCount[lineCount] < 26)
			{
				char ch = keyIn;
				string.push_back(ch);
				wordCount[lineCount]++;
			}

			else
			{
				if (lineCount < 10)
				{
					textRect[0].bottom += 40;
					string.append("\n");
					lineCount++;

					char ch = keyIn;
					string.push_back(ch);
					wordCount[lineCount]++;
				}
				
				else
				{
					string.append("\nMassange Full");
					msgFull = true;
				}
			}

		}

		else if (keyIn == 13)
		{
			msgNull = false;
			if (lineCount < 10)
			{
				textRect[0].bottom += 40;
				string.append("\n");
				lineCount++;
			}

			else
			{
				string.append("\nMassange Full");
				msgFull = true;
			}

		}
	}

	if (keyIn == 8)
	{
		if (msgFull == true)
		{
			string.erase(string.length()-14);
			printf("\n%d\n", lineCount);
			msgFull = false;
		}

		if (lineCount == 1 && wordCount[lineCount] == 0)
		{
			msgNull = true;
		}


		if (msgNull == false)
		{
			if (wordCount[lineCount] > 0)
			{
				string.erase(string.length() - 1);
				wordCount[lineCount]--;
			}

			else
			{
				lineCount--;
				printf("\n%d\n", lineCount);

				//have word
				if (wordCount[lineCount] > 0)
				{
					string.erase(string.length() - 1);
					wordCount[lineCount]--;
				}

				//erase "\n"
				string.erase(string.length() - 1);
			}
		}
		printf("%d,%d\n", lineCount, wordCount[lineCount]);
	}
}