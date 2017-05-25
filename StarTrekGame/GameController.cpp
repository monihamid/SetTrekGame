/*
* PROJECT		:  Assignment 02 SET Trek
* FILE			: GameController.cpp
* PROGRAMER     : Monira Sultana
* DATE			: 2017/04/13
* DESCRIPTION	: This class initiate and control the game.
* This file is Supplied by Prof. Russell Foubert
*/

#include "GameController.h"

GameLevel* GameController::currentLevel;
bool GameController::Loading;

/**
* \brief This is the starting point of game
* \details This methods initiate the game
* \param Nothing
* \return Nothing
*/

void GameController::Init()
{
	Loading = true;
	currentLevel = 0;
}

/**
* \brief This is the controller of game
* \details This methods initiate the game sets the game level
* \param GameLevel lev
* \return Nothing
*/
void GameController::LoadInitialLevel(GameLevel* lev)
{
	Loading = true; //This can help us avoid loading activity while rendering
	currentLevel = lev;
	currentLevel->Load();
	Loading = false;
}

/**
* \brief This is the controller of game
* \details This methods will switch the game level
* \param GameLevel lev
* \return Nothing
*/
void GameController::SwitchLevel(GameLevel* lev)
{
	Loading = true;
	currentLevel->Unload();
	lev->Load();
	delete currentLevel;
	currentLevel = lev;
	Loading = false;
}


/**
* \brief This is one of the controller of game
* \details This methods do not render screen if it is loading
* \param Nothing
* \return Nothing
*/
void GameController::Render()
{
	if (Loading) return;       //nice! Do not update or render if the scene is loading.
	currentLevel->Render();
}
/**
* \brief This is one of the controller of game
* \details This methods update screen if the screen it is loading
* \param Nothing
* \return Nothing
*/
void GameController::Update()
{
	if (Loading) return; // Do not update or render if the scene is loading.
	currentLevel->Update();
}

/**
* \brief This is one of the controller of game
* \details This methods update screen if the screen it is loading
* \param Nothing
* \return Nothing
*/
void GameController::Process()
{
	if (Loading) return;
	currentLevel->Process();
}