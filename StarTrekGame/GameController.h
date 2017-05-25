/*
* PROJECT		: Assignment 03 SET Trek
* FILE			: GameController.h
* PROGRAMMER	: Monira Sultana
* DATE			: 2017/04/24
* DESCRIPTION	: The header file containing the class definition for the GameController.
* This file is Supplied by Prof. Russell Foubert
*/
#pragma once
#include "GameLevel.h"
#include "Graphics.h"

//This will be a Singleton class (constructor is private)

class GameController
{
	GameController() {}
	static GameLevel* currentLevel;
public:
	static bool Loading;
	static void Init();
	static void LoadInitialLevel(GameLevel* lev);
	static void SwitchLevel(GameLevel* lev);
	static void Render();
	static void Update();
	static void Process();
};
