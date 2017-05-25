/*
* PROJECT		: Assignment 03 SET Trek
* FILE			: InputClass.h
* PROGRAMMER	: Monira Sultana
* DATE			: 2017/04/24
* DESCRIPTION	: The header file containing the class definition for the Inputs.

*/
#pragma once



class InputClass
{
public:

	static float LeftMouseX;
	static float LeftMouseY;
	static float RightMouseX;
	static float RightMouseY;
	static float EnergyLevel;
	
	static bool IsLeftClick;
	static bool IsRightClick;

	static void Init(void);
};