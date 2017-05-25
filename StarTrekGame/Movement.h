/*
* PROJECT		: Assignment 03 SET Trek
* FILE			: GameLevel.h
* PROGRAMMER	: Monira Sultana
* DATE			: 2017/04/24
* DESCRIPTION	: The header file containing the class definition for the GameLevel.

*/

#pragma once
#define _USE_MATH_DEFINES
#include <Windows.h>
//#include "Graphics.h"
//#include "GameLevel.h"
#include <vector>
//#include "UploadImage.h"
#include <vector>
#include <string>
#include <cmath>

using namespace std;


class Movement
{
private:
	
	float windowWidth;
	float windowHeight;
	float gridWidth;
	float gridHeight;
	pair<float, float> mouseP;

	pair<float, float> shipBStart;              //direction of shipbase
	pair<float, float> shipDStart;                  //direction of shipdetails
	pair<float, float> enemyShipStart;
	pair<float, float> currentPositionPS;      //get the current position of player ship
	pair<float, float> currentPositionEnemyS;

	float shipAngle;
	float enemyAngle;
	
	UINT winHandle;

	
public:

	 Movement(float windowWidth, float windowHeight);
	
	~Movement();

	
	void SetWindowWidth(float width);
	void SetWindowHeight(float height);
	pair<float, float> GetMouseP();
	pair<float, float> GetShipBStart();
	pair<float, float> GetShipDStart();
	pair<float, float> GetEnemyShipStart();
	pair<float, float> GetCurrentPositionPS();
	pair<float, float> GetCurrentPositionEnemyS();


	void SetMouseP(pair<float, float> mousePoint);
	void SetEnemyShipStart(pair<float, float> enemyStart);
	void SetCurrentPositionPS(pair<float, float> playerShipPosition);
	void SetCurrentPositionEnemyS(pair<float, float> enemyShipPosition);
	void SetshipBStart(pair<float, float> shipBstart);
	void SetshipDStart(pair<float, float> shipDstart);
	
	
	UINT GetWinHandle(UINT wHand);
	
	
	void PlayerMove( pair <float, float> endPoints);
	void enemySMove();
	float calAngle(pair <float, float> startP, pair <float, float> endP);
	bool CheckCollosion(pair <float, float> shipPoint, pair <float, float> planetPoint);
	bool CheckEnemyCollision(pair <float, float> shipPoint, pair <float, float> enemyPoint);
	

	//-Getters
	float GetStarShipAngle(void);
	float GetEnemyAngle(void);
	void SetEnemyAngle(float eAngle);
	float GetWindowWidth(void);
	float GetWindowHeight(void);

	//-Setters
	void SetStarShipAngle(float angle);

	void SetWinHandle(UINT wHand);
};