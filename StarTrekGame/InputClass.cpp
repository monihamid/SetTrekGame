/*
* PROJECT		: Assignment 02 SET Trek
* FILE			:InputClass.cpp
* PROGRAMMER	: Monira Sultana
* DATE			: 2017/04/14
* DESCRIPTION	:This class keep track of outcomming message and position of ship. This is a global class.
*/
#include "InputClass.h"


float InputClass::LeftMouseX;
float InputClass::LeftMouseY;
float InputClass::RightMouseX;
float InputClass::RightMouseY;
float InputClass::EnergyLevel;

bool InputClass::IsLeftClick;
bool InputClass::IsRightClick;


void InputClass::Init(void)
{
	
	LeftMouseX = 0.0;
	LeftMouseY = 0.0;
	RightMouseX = 0.0;
	RightMouseY = 0.0;
	EnergyLevel = 1000;	
	IsLeftClick = false;
	IsRightClick =false;
}	