/*
* PROJECT		: Assignment 03 SET Trek
* FILE			: StarShip.h
* PROGRAMMER	: Monira Sultana
* DATE			: 2017/04/24
* DESCRIPTION	: The header file containing the class definition for the Graphics.
* This file is Supplied by Prof. Russell Foubert
*/
#pragma once
#define _USE_MATH_DEFINES
#include <Windows.h>
#include "Graphics.h"
#include "UploadImage.h"
#include "GameLevel.h"
#include <vector>
#include <string>
#include <cmath>
using namespace std;


#define kDefaultEnergyLevel		1000.0f


/*
*
*/
class Starship
{
private:

	Graphics* gfx; //Reference to the Graphics class
	ID2D1Bitmap* bmp; //This will hold our loaded and converted Bitmap file
	ID2D1Effect* effect;

	UploadImage* image;

	pair<float, float> shipBStart;              //direction of shipbase
	pair<float, float> shipDStart;              //direction of shipdetails
	pair<float, float> currentPositionPS;      //get the current position of player ship

	float shipAngle;
	float energyLevel;

	bool isDead;
	bool isShooting;

public:

	Starship(Graphics* gfx, float startPosX, float startPosY);
	~Starship();

	void InitImage(wchar_t* filename, bool shouldScale = true);
	void ChromaEffect(float r, float g, float b);

	void Draw(float left, float top);

	// General Methods
	void CalculateAngle(pair <float, float> startP, pair <float, float> endP);

	// Movement methods
	void MoveShip(pair <float, float> endPoints);

	// Collision Detection methods
	bool CheckPlanetCollosion(pair <float, float> shipPoint, pair <float, float> planetPoint);
	bool CheckEnemyCollision(pair <float, float> shipPoint, pair <float, float> enemyPoint);

	// Setters
	 // Sets the current position of the ship
	void SetCenterOfShip(pair<float, float> playerShipPosition);
	void SetEnergyLevel(float loose);
	void SetIsDead(bool dead);

	// Getters
	pair<float, float> GetShipBStart();
	pair<float, float> GetShipDStart();
	pair <float, float> GetCenterOfShip();
	float GetShipAngle(void);
	float GetEnergyLevel(void);
	bool GetIsDead(void);
};