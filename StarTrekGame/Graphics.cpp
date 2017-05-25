/*
* PROJECT		: Assignment 03 SET Trek
* FILE			: Graphics.cpp
* PROGRAMMER	: Monira Sultana (7308182)
* DATE			: 2017/04/14
* DESCRIPTION	: The CPP file contains the implementation for the Graphics class. Examples
*			like instantiating D2D1 COM objects, initialization, etc.
* This file is Supplied by Prof. Russell Foubert. Monira edited with Kathy,s Code. The link is bellow
*https://katyscode.wordpress.com/2013/01/23/migrating-existing-direct2d-applications-to-use-direct2d-1-1-functionality-in-windows-7/
*/

#include "Graphics.h"

//https://msdn.microsoft.com/en-us/library/windows/desktop/hh706316(v=vs.85).aspx

/***********************************************************************************
The intent of the Graphics class is to handle our DirectX calls, and to be largely responsible
for managing the rendertarget.
******************************************************************************************/
/**
* \brief Basic constructor for the Graphics class.
* \details All the private data members are set to a safe value.
* \parm Nothing
* \return Nothing
*/

Graphics::Graphics()
{
	factory = NULL;
	rendertarget = NULL;
	brush = NULL;

	Direct3DDevice = NULL;
	Direct3DContext = NULL;
	Direct2DDevice = NULL;
	DXGISwapChain = NULL;
	Direct2DBackBuffer = NULL;
}

/**
* \brief Basic destructor for the Graphics class.
* \details All the private data members are set to a safe value.
*/

Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();
	if (brush) brush->Release();

	if (Direct3DDevice) Direct3DDevice->Release();
	if (Direct3DContext) Direct3DContext->Release();
	if (Direct2DDevice) Direct2DDevice->Release();
	if (DXGISwapChain) DXGISwapChain->Release();
	if (Direct2DBackBuffer) Direct2DBackBuffer->Release();
}

//Provide some comments for each of the methods below.
//Be sure you get a sense of what is happening, and resolve any issues you have understanding these
// methods, their parameters, returns and so on.

/**
* \brief Initialize creating the object.
* \details Calls upon a D2D1 method to clear the screen.
* \param HWND windowHandle 
* \return Nothing
*/
bool Graphics::Init(HWND windowHandle)
{
	

	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (hr != S_OK) return false;

	//----------------------

	// Set feature levels supported by our application
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	// This flag adds support for surfaces with a different color channel ordering
	// than the API default. It is required for compatibility with Direct2D.
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	// Create Direct3D device and context
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;
	D3D_FEATURE_LEVEL returnedFeatureLevel;

	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creationFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION,
		&device, &returnedFeatureLevel, &context);

	device.Get()->QueryInterface(__uuidof(ID3D11Device1), (void **)&Direct3DDevice);
	context.Get()->QueryInterface(__uuidof(ID3D11DeviceContext1), (void **)&Direct3DContext);

	ComPtr<IDXGIDevice> dxgiDevice;
	Direct3DDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&dxgiDevice);

	factory->CreateDevice(dxgiDevice.Get(), &Direct2DDevice);

	// Here we create the device context!
	Direct2DDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &rendertarget);


	//-------------------------
	// Get the GPU we are using
	ComPtr<IDXGIAdapter> dxgiAdapter;
	dxgiDevice->GetAdapter(&dxgiAdapter);

	// Get the DXGI factory instance
	ComPtr<IDXGIFactory2> dxgiFactory;
	dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

	// Describe Windows 7-compatible Windowed swap chain
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	swapChainDesc.Width = 0;
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	// Create DXGI swap chain targeting a window handle (the only Windows 7-compatible option)
	dxgiFactory->CreateSwapChainForHwnd(Direct3DDevice, windowHandle, &swapChainDesc, nullptr, nullptr, &DXGISwapChain);

	// Get the back buffer as an IDXGISurface (Direct2D doesn't accept an ID3D11Texture2D directly as a render target)
	ComPtr<IDXGISurface> dxgiBackBuffer;
	DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));

	// Get screen DPI
	FLOAT dpiX, dpiY;
	factory->GetDesktopDpi(&dpiX, &dpiY);

	// Create a Direct2D surface (bitmap) linked to the Direct3D texture back buffer via the DXGI back buffer
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), dpiX, dpiY);

	rendertarget->CreateBitmapFromDxgiSurface(dxgiBackBuffer.Get(), &bitmapProperties, &Direct2DBackBuffer);

	// Set surface as render target in Direct2D device context
	rendertarget->SetTarget(Direct2DBackBuffer);

	// Creating the brush object
	rendertarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);

	return true;
}





/**
* \brief Clear the redner target (client screen) with a RGB color.
* \details Calls upon a D2D1 method to clear the screen.
* \param r - float - The red channel
* \param g - float - The green channel
* \param b - float - The blue channel
*/
void Graphics::ClearScreen(float r, float g, float b)
{
	rendertarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawLine(float startX, float startY, float endX, float endY, float r, float g, float b, float thick)
{
	brush->SetColor(D2D1::ColorF(r, g, b, 1.0f));

	D2D1_POINT_2F startPoint = D2D1::Point2F(startX, startY);
	D2D1_POINT_2F endPoint = D2D1::Point2F(endX, endY);

	rendertarget->DrawLine(startPoint, endPoint, brush, thick);
}


/**
* \brief Get the window size
* \return RECT - The window size
*/
RECT Graphics::GetWindowSize(void)
{
	return windowSize;
}

/**
* \brief Set the window size
*/
void Graphics::SetWindowSize(RECT size)
{
	windowSize = size;
	windowWidth = size.right - size.left;
	windowHeight = size.bottom - size.top;
}


float Graphics::GetWindowWidth(void)
{
	return windowWidth;
}
float Graphics::GetWindowHeight(void)
{
	return windowHeight;
}

