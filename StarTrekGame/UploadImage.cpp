/*
* PROJECT		:  Assignment 03 SET Trek
* FILE			: UploadImage.cpp
* PROGRAMER     : Monira Sultana
* DATE			: 2017/03/14
* DESCRIPTION	: This class takes path for the image file as parameter and deaw the image in window as specified.
* This file is Supplied by Prof. Russell Foubert
*/

#include "UploadImage.h"


/**
* \brief This is the constructor for rendering the image.
* \details This methods takes file path and 2D graphics and creat
* \WIC component.
* \param wchar_t-filename
* \parm Graphics- gfx
* \return Nothing
*/

UploadImage::UploadImage(wchar_t* filename, Graphics* gfx, bool shouldScale)
{
	this->gfx = gfx; //save the gfx parameter for later
	bmp = NULL; //This needs to be NULL to start off
	effect = NULL;
	HRESULT hr;

	//Step 1: Create a WIC Factory
	
	IWICImagingFactory2 *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory, //CLS ID of the object about to be made
		NULL, //not needed here, but just denotes this isn't part of an aggregate
		CLSCTX_INPROC_SERVER, //Indicates this DLL runs in the same process
		IID_IWICImagingFactory, //Reference to an Interface that talks to the object
		(LPVOID*)&wicFactory); //This is our pointer to the WICFactory, once set up.

							   //Step 2: Create a Decoder to read file into a WIC Bitmap
	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,         //The filename we passed in already
		NULL, //This can be used to indicate other/preferred decoders. Not something we need.
		GENERIC_READ, //indicates we're reading from the file, vs writing, etc.
		WICDecodeMetadataCacheOnLoad, //Needed, but would only help if we were keeping this in WIC
		&wicDecoder); //Our pointer to the Decoder we've setup

					  //Step 3: Read a 'frame'. We're really just moving the whole image into a frame here
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame); //0 here means the first frame... or only one in our case
											 //Now, we've got a WICBitmap... we want it to be a D2D bitmap

	//Step 4: Create a WIC Converter
	IWICFormatConverter *wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);


	// Step 4.5: Scale the Bitmap to the Screen
	IWICBitmapScaler* pScaler = NULL;
	if (shouldScale)
	{
		RECT size = gfx->GetWindowSize();

		hr = wicFactory->CreateBitmapScaler(&pScaler);
		if (SUCCEEDED(hr))
		{
			hr = pScaler->Initialize(
				wicFrame,
				(size.right - size.left) / 10,
				(size.bottom - size.top) / 10,
				WICBitmapInterpolationModeFant
			);
		}

		//Step 5: Configure the Converter
		hr = wicConverter->Initialize(
			pScaler, //Our frame from above
			GUID_WICPixelFormat32bppPBGRA, //Pixelformat
			WICBitmapDitherTypeNone, //not important for us here
			NULL, //indicates no palette is needed, not important here
			0.0, //Alpha Transparency, can look at this later
			WICBitmapPaletteTypeCustom //Not important for us here
		);
	}
	else
	{
		//Step 5: Configure the Converter
		hr = wicConverter->Initialize(
			wicFrame, //Our frame from above
			GUID_WICPixelFormat32bppPBGRA, //Pixelformat
			WICBitmapDitherTypeNone, //not important for us here
			NULL, //indicates no palette is needed, not important here
			0.0, //Alpha Transparency, can look at this later
			WICBitmapPaletteTypeCustom //Not important for us here
		);
	}


	//Step 6: Create the D2D Bitmap! Finally!
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter, // the converter
		NULL, //Can specify D2D1_Bitmap_Properties here, not needed now
		&bmp //Our destination bmp we specified earlier in the header
	);


	//Let us do some private object cleanup!
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();
	if (pScaler) pScaler->Release();
}

/**
* \brief This is the destructor for UploadImage.
* \details This methods takes delet objects after use
* \return Nothing
*/
UploadImage::~UploadImage()
{
	if (bmp) bmp->Release();
	if (effect) effect->Release();
}


void UploadImage::ApplyChromaEffect()
{
	gfx->GetRenderTarget()->CreateEffect(CLSID_D2D1ChromaKey, &effect);

	effect->SetInput(0, bmp);
	effect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(0.0f, 1.0f, 0.0f));
	effect->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.2f);
	effect->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, false);
	effect->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, false);
}

void UploadImage::ApplyChromaEffectBack()
{
	gfx->GetRenderTarget()->CreateEffect(CLSID_D2D1ChromaKey, &effect);

	effect->SetInput(0, bmp);
	effect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(0.f, 0.f, 0.0f));
	effect->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.2f);
	effect->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, false);
	effect->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, false);
}

void UploadImage::ChromaEffectEnemyShip()
{
	gfx->GetRenderTarget()->CreateEffect(CLSID_D2D1ChromaKey, &effect);

	effect->SetInput(0, bmp);
	effect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(0.0f, 0.0f, 1.0f));
	effect->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.2f);
	effect->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, false);
	effect->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, false);
}
/**
* \brief This method draw the image on the screen.
* \details This methods build bitmap from WICrender the image and display on window.
* \It displays background planets and ship.
* \param float
* \param float
* \param float
* \param float
* \return Nothing
*/

void UploadImage::DrawBackground(float left, float top, float right, float bottum)
{
	gfx->GetRenderTarget()->DrawBitmap(
		bmp, //Bitmap we built from WIC
		D2D1::RectF(left, top, right, bottum),    //Destination rectangle
		0.8f, //Opacity or Alpha
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, 
		//Above - the interpolation mode to use if this object is 'stretched' or 'shrunk'. 
		//Refer back to lecture notes on image/bitmap files
		D2D1::RectF(0.0f, 0.0f, gfx->GetWindowWidth(), gfx->GetWindowHeight()) //Source Rect
	);
}


void UploadImage::DrawPlanet(float left, float top)
{
	gfx->GetRenderTarget()->DrawImage(
		effect,
		D2D1::Point2F(left, top),
		D2D1::RectF(0, 0,  gfx->GetWindowWidth() / 10, gfx->GetWindowHeight() / 10)
	);
}


// GETTERS
//
ID2D1Bitmap* UploadImage::GetBitmap(void)
{
	return bmp;
}


ID2D1Effect* UploadImage::GetEffect(void)
{
	return effect;
}