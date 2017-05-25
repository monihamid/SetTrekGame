/*
* PROJECT		:  Assignment 03 SET Trek
* FILE			: main.cpp
* PROGRAMER     : Monira Sultana
* DATE			: 2017/04/14
* DESCRIPTION	: The main entry point for the game.
* This file is Supplied by Prof Russell Foubert
*/
#include <Windows.h>
#include <windowsx.h>
#include "Graphics.h"
#include "Level1.h"
#include "GameController.h"
#include "Movement.h"
#include "InputClass.h"


Graphics* graphics;

HWND g_main_window_handle = NULL;		// globally track main window
HINSTANCE hinstance_app = NULL;
UINT message;



/**
* \brief This is for handling any Window events.
* \details  - The Window Process must be defined before Main. This is a call back function. We do 
*  not need to call it, it called automatically when needed.
* \param hwnd - HWND - A handle to the window.
* \param uMsg - UINT - the message.
* \param wParam - WPARAM - Additional message information.
* \param lParam - LPARAM -Additional message information.
* \return LRESULT- DefWindowProc 
*/

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//set the cursor value to 
	//if (lParam = GetAsyncKeyState(VK_LBUTTON)) //check if mouse button click or 
	//{
	//	POINT cusrsorPosition;
	//	Movement movement;
	//	GetCursorPos(&cusrsorPosition);    //get cussor position
	//	movement.SetMouseX(cusrsorPosition.x);
	//	movement.SetMouseY( cusrsorPosition.y);

	//}
	if (uMsg == WM_DESTROY) 
	{ 
		PostQuitMessage(0);
	   return 0; 
	
	}

	if (uMsg == WM_LBUTTONDOWN)
	{
		InputClass::LeftMouseX = float(GET_X_LPARAM(lParam));
		InputClass::LeftMouseY = float(GET_Y_LPARAM(lParam));
		InputClass::IsLeftClick = true;

		message = uMsg;
	}
	
	if (uMsg == WM_RBUTTONDOWN)
	{
		InputClass::RightMouseX = float(GET_X_LPARAM(lParam));
		InputClass::RightMouseY = float(GET_Y_LPARAM(lParam));
		InputClass::IsRightClick = true;
		message = uMsg;
	}
	

		// We've moved this down to the message handling loop below

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/**
* \brief The wWinMain is the main entry point for the application.
* \details It dedines the window size all of it's features
* \param hInstance - HINSTANCE - The handle instance to the client window
* \param prevInstance - HINSTANCE - The previous handle instance to a window
* \param cmd - LPWSTR - The command line arguments
* \param nCmdShow - int - Describes how the Window will be shown
* \return int : The return for main
*/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	//Do a bit of reading - What is this Window Class used for? 
	// What are the major parameters below?
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW; //Alert - This is useful here... what does it do?

	RegisterClassEx(&windowclass);


	RECT rect = { 0, 0, kWindowWidth, kWindowHeight };//Do these numbers look significant to you? What are they?
	AdjustWindowRectEx(&rect, WS_OVERLAPPED, false, WS_EX_OVERLAPPEDWINDOW);
	

	//Below is another important process to understand... what are we doing?
	//Why is this connected to rect we just defined above?
	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "SET Trek Game", WS_OVERLAPPEDWINDOW, 100, 100,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
	if (!windowhandle)
	{
		return -1;
	}

	g_main_window_handle = windowhandle;  //saving the value of window handle

	float width = 0;
	float height = 0;
	if (GetClientRect(windowhandle, &rect))
	{
		 width = float(rect.right - rect.left);
		 height = float(rect.bottom - rect.top);
	} 


	graphics = new Graphics();
	graphics->SetWindowSize(rect);
	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return -1;
	}

	InputClass::Init();

	GameLevel::Init(graphics);
	ShowWindow(windowhandle, nCmdShow);

	Level1* myLevel = new Level1();
	myLevel->SetWindowWidth(width);
	myLevel->SetWindowHeight(height);

	GameController::LoadInitialLevel(new Level1());

#pragma region GameLoop
	//Below, we have essentially an infinite loop that will keep the window running and will dispatch/show messages
	//As many people will tell you, most Windows you see are just infinite loops waiting for some kind of work-flow or 
	//system-based interuption.

	//Note - Our message handling has changed from the first demo code.
	//Here, we use a PeekMessage to avoid locking the graphics/windoProc
	//when a message has to be dispatched.

	MSG message;
	message.message = WM_NULL; //Do not have this set to WM_QUIT, which has a specific context
	//POINT cusrsorPosition;
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			//This allows us to send a message to the WindowProc IF there is one
			DispatchMessage(&message);
		else
		{
			if (InputClass::IsLeftClick || InputClass::IsRightClick)
			{
				GameController::Process();
				InputClass::IsLeftClick = false;
				InputClass::IsRightClick = false;
			}
			GameController::Update();

			//Render Routine... This is very modular. GameController now handles the rendering
			graphics->BeginDraw();
			GameController::Render();
			graphics->EndDraw();		
			
			
			
			
		}
		
	}

#pragma endregion
	delete graphics;
	
	return 0;
}

