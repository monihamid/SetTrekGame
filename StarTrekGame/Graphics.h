/*
* PROJECT		: Assignment 03 SET Trek
* FILE			: Graphics.h
* PROGRAMMER	: Monira Sultana
* DATE			: 2017/04/24
* DESCRIPTION	: The header file containing the class definition for the Graphics.
* This file is Supplied by Prof. Russell Foubert
*/

#pragma once
#include <Windows.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <d3d11_1.h>
#include <d2d1effects_2.h>
#include <d2d1effecthelpers.h>
#include <dwrite_1.h>

// Enabling the ComPtr
#include <wrl.h>
//#include <wrl\client.h>
using namespace Microsoft::WRL;


//-CONSTANTS
#define kWindowWidth	1024
#define kWindowHeight	768



class Graphics
{
	RECT windowSize;
	float windowWidth;
	float windowHeight;

	//Below, these are all COM interfaces we're using to create D2D resources.
	//We release them as part of the ~Graphics deconstructor... or bad things can happen
	ID2D1Factory1* factory; //The factory allows us to create many other types of D2D resources
	ID2D1DeviceContext* rendertarget; //this is typically an area in our GPU memory.. like a back buffer 
	ID2D1SolidColorBrush* brush; //Note this COM interface! Remember to release it!


	//IDwriteFactory1
	//Direct3D device
    ID3D11Device1 *Direct3DDevice;

	// Direct3D device context
	ID3D11DeviceContext1 *Direct3DContext;

	// Direct2D device
	ID2D1Device *Direct2DDevice;

	// DXGI swap chain
	IDXGISwapChain1 *DXGISwapChain;

	// Direct2D target rendering bitmap
	// (linked to DXGI back buffer which is linked to Direct3D pipeline)
	ID2D1Bitmap1 *Direct2DBackBuffer;

public:
	Graphics();

	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1DeviceContext* GetRenderTarget()
	{
		return rendertarget;
	}

	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() 
	{ 
		rendertarget->EndDraw(); 

		// Present (new for Direct2D 1.1)
		DXGI_PRESENT_PARAMETERS parameters = { 0 };
		parameters.DirtyRectsCount = 0;
		parameters.pDirtyRects = nullptr;
		parameters.pScrollRect = nullptr;
		parameters.pScrollOffset = nullptr;

		DXGISwapChain->Present1(1, 0, &parameters);
	}

	void ClearScreen(float r, float g, float b);
	//void DrawCircle(float c, float y, float radius, float r, float g, float b, float a);
	// Hrmmm... r, g, b, a? Where do we know these from?

	RECT GetWindowSize(void);
	void SetWindowSize(RECT size);
	float GetWindowWidth(void);
	float GetWindowHeight(void);
	void DrawLine(float startX, float startY, float endX, float endY, float r, float g, float b, float thick);
};

