
/*
* PROJECT		: Assignment 03 SET Trek
* FILE			: UploadImage.h
* PROGRAMMER	: Monira Sultana
* DATE			: 2017/03/24
* DESCRIPTION	: The header file containing the class definition for the UploadImage.
* This file is Supplied by Prof. Russell Foubert
*/
#pragma once

#include <wincodec.h> //This is the WIC codec header - we need this to decode image files
#include "Graphics.h" //This includes both Windows and D2D libraries
//Remember to add "windowscodecs.lib" to your Linker/Input/AdditionalDependencies
#pragma comment(lib, "windowscodecs.lib")		// Enables the usage of WIC
#pragma comment(lib, "d2d1.lib")

class UploadImage
{
	Graphics* gfx; //Reference to the Graphics class
	ID2D1Bitmap* bmp; //This will hold our loaded and converted Bitmap file
	ID2D1Effect* effect;

public:
	//Constructor
	UploadImage(wchar_t* filename, Graphics* gfx, bool shouldScale = true);

	//Destructor
	~UploadImage();

	//Draw bitmap to the render target
	void DrawBackground(float left, float top, float right, float bottum);
	void ApplyChromaEffectBack();
	void DrawPlanet(float left, float top);//, float right, float bottum);
	void ApplyChromaEffect();
	void ChromaEffectEnemyShip();

	ID2D1Bitmap* GetBitmap(void);
	ID2D1Effect* GetEffect(void);
};

// start new
