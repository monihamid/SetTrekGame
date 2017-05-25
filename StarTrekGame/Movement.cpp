
/*
* PROJECT		: Assignment 03 SET Trek
* FILE			: Movement.cpp
* PROGRAMER     : Monira Sultana
* DATE			: 2017/04/14
* DESCRIPTION	: This class calculate value of tan0 and move the playership and enemyship.
*/

#include "GameController.h"
#include "Level1.h"
#include "Movement.h"
#include <ctime> 
#include <string>
#include <iostream>
#include <vector>
#include <math.h> 
#include <cmath>


/**
* \brief Basic constructor for the Movement class.
* \details All the private data members are set to a safe value.
* \parm Nothing
* \return Nothing
*/

Movement::Movement(float width, float height)
{
	
	mouseP.first =0;
	mouseP.second = 0;
	
	currentPositionPS;      //current position of player ship
	windowWidth = width;
	windowHeight = height;
	gridWidth = windowWidth / 10;
	gridHeight = windowHeight / 10;

	shipBStart.first = 0;                  //direction of shipbase
	shipBStart.second = 384;

					//direction of shipbase
	shipDStart.first = 0;                  //direction of shipbase
	shipDStart.second = 384;
	
	
	enemyShipStart.first = 1024;             
	enemyShipStart.second = 384;              
	


	shipAngle = 0.0f;
	enemyAngle = 0.0f;

	winHandle = 0;
}

/**
* \brief Basic destructor for the Movement class.
* \details it will release the objects end of the game.
*/
Movement::~Movement()
{


}

//setter

void Movement::SetWindowWidth(float width)
{
	windowWidth = width;
}
//getter
float Movement::GetWindowWidth(void)
{

	return windowWidth;
}

void Movement::SetWindowHeight(float height)

{
	windowHeight = height;
}

float Movement::GetWindowHeight(void)
{

	return windowHeight;
}


/**
* \brief move the player ship.
* \details Calls upon a D2D1 method to specify the location of image file.
* \param: pair mouseP
*         pair endP
* \return Nothing
*/

void Movement::PlayerMove( pair<float, float> mouseP)
{

	pair <float, float> playerPosition;
	playerPosition = GetCurrentPositionPS();
	
	pair<float, float> cpt;
	

	// MOVE SHIP AUTOMATICALLY
	if ( mouseP.first == 0 && mouseP.second==0)
	{
		

		//storing the player ship positions
		cpt.first = shipBStart.first;
		cpt.second = shipBStart.second;
		SetCurrentPositionPS(cpt);
	 }
	else
	{

		if (playerPosition.first < mouseP.first)
		{
			shipBStart.first++;
			shipDStart.first++;
			
			//storing current position
			cpt.first = shipBStart.first;
			cpt.second = shipBStart.second;
			SetCurrentPositionPS(cpt);
		}
		if (playerPosition.first > mouseP.first)
		{
			shipBStart.first--;
			shipDStart.first--;
			
			//storing current position
			cpt.first = shipBStart.first;
			cpt.second = shipBStart.second;
			SetCurrentPositionPS(cpt);
		}

		if (playerPosition.second < mouseP.second)
		{
			shipBStart.second++;
			shipDStart.second++;
			
			//storing current position
			cpt.first = shipBStart.first;
			cpt.second = shipBStart.second;
			SetCurrentPositionPS(cpt);
		}
		if (playerPosition.second > mouseP.second)
		{
			shipBStart.second--;
			shipDStart.second--;

			//storing current position
			cpt.first = shipBStart.first;
			cpt.second = shipBStart.second;
			SetCurrentPositionPS(cpt);
		}
	}

	// Restarting the Player ship on the left-side
	if (shipBStart.first > 1024 || shipBStart.second >768
		|| shipBStart.first <0 || shipBStart.second<0)
	{
		shipBStart.first = 0;
		shipBStart.first = shipBStart.first++;
		shipBStart.second = 384;
		shipDStart.first = 0;
		shipDStart.first = shipDStart.second++;
		shipDStart.second = 384;

		cpt.first = shipBStart.first;
		cpt.second = shipBStart.second;
		SetCurrentPositionPS(cpt);

	}
}

/**
* \brief This method set value for enemyShipStart.
* \details This method set value for enemyShipStart.
* \param pair FLOAT, FOLAT- enemyStart
* \return Nothing
*/
void Movement::SetEnemyShipStart(pair<float, float> enemyStart)
{

	enemyShipStart.first = enemyStart.first;
	enemyShipStart.second = enemyStart.second;

}

pair<float, float> Movement::GetCurrentPositionEnemyS()
{
	return currentPositionEnemyS;
}

void Movement::SetCurrentPositionEnemyS(pair<float, float> enemyShipPosition)
{
	currentPositionEnemyS = enemyShipPosition;

}
/**
* \brief This method move the enemy ship.
* \details This method move the enemyship and follow the player ship

* \param Nothing
* \return Nothing
*/
void Movement::enemySMove()
{
	
	pair <float, float> playerPosition;
	playerPosition = GetCurrentPositionPS(); 


	// MOVING enemey LEFT or RIGHT
	if (enemyShipStart.first < playerPosition.first)
	{
		enemyShipStart.first++;

		currentPositionEnemyS.first = enemyShipStart.first;
	}
	if (enemyShipStart.first > playerPosition.first)
	{
		enemyShipStart.first--;
		currentPositionEnemyS.first = enemyShipStart.first;
	}

	// MOVING enemy UP or DOWN
	if (enemyShipStart.second > playerPosition.second)
	{
		enemyShipStart.second--;
		currentPositionEnemyS.second = enemyShipStart.second;
	}
	if (enemyShipStart.second < playerPosition.second)
	{
		enemyShipStart.second++;
		currentPositionEnemyS.second = enemyShipStart.second;
	}
	if (enemyShipStart.first >1024 && enemyShipStart.second > 768 || enemyShipStart.first <0 && enemyShipStart.second <0 )
	{
		enemyShipStart.first = 1028;               
		enemyShipStart.second =384;
	}


	
}



UINT Movement::GetWinHandle(UINT wHand)
{
	return winHandle;
}

/**
* \brief This method set value for winHandle.
* \details This method set value for winHandle.
* \param pair FLOAT, FOLAT- enemyStart
* \return Nothing
*/
void Movement::SetWinHandle(UINT wHand)
{
	winHandle = wHand;
}

/**
* \brief This method set value for SetMouseP.
* \details This method set value for SetMouseP.
* \param pair FLOAT, FOLAT- mousePoint
* \return Nothing
*/
void Movement::SetMouseP(pair<float, float> mousePoint)
{
	mouseP.first = mousePoint.first;
	mouseP.second = mousePoint.second;

}

pair <float, float> Movement:: GetCurrentPositionPS()
{
	return currentPositionPS;

}
/**
* \brief This method set value for current Position for player ship.
* \details This method set value for  current Position for player ship.
* \param pair FLOAT, FOLAT- playerShipPosition
* \return Nothing
*/
void Movement::SetCurrentPositionPS(pair<float, float> playerShipPosition)
{
	float Width = gridWidth;
	float centreX = playerShipPosition.first + gridWidth / 2;
	float centrY = playerShipPosition.second + gridHeight / 2;

	currentPositionPS.first = centreX;
	currentPositionPS.second = centrY;
}

/**
* \brief This method get value for mouse Position after button click.
* \details This method set value for  current Position for player ship.
* \param pair FLOAT, FOLAT- playerShipPosition
* \return Nothing
*/
pair<float, float> Movement::GetMouseP()
{
	return mouseP;
}

//getter

pair<float, float> Movement::GetShipDStart()
{
	return shipBStart;
}
pair<float, float> Movement::GetShipBStart()
{
	return shipBStart;
}

pair<float, float> Movement:: GetEnemyShipStart()
{

	return enemyShipStart;
}
/**
* \brief This method checks the qulition between planet and playere ship.
* \details This method checks the qulition between planet and playere ship and also enemy ship. 
* \param pair FLOAT, FOLAT- shipPoint, planetPoint
* \return bool collidet
*/ 
bool Movement::CheckCollosion(pair <float, float> shipPoint, pair <float, float> planetPoint)
{
	bool colliDet = false;

	float shipCenterX = shipPoint.first;
	float shipCenterY = shipPoint.second;

	float planetLeft = planetPoint.first;
	float planetRight = planetPoint.first + gridWidth;
	float planetTop = planetPoint.second;
	float planetBottom = planetPoint.second + gridHeight;

	float planetCenterX = (planetLeft + planetRight) / 2;
	float planetCenterY = (planetTop + planetBottom) / 2;

	float planetBoundaryX = (gridWidth / 2.0f);
	float planetBoundaryY = (gridHeight / 2.0f);


	if ((shipCenterX > planetCenterX - planetBoundaryX) && (shipCenterX < planetCenterX + planetBoundaryX)
		&& (shipCenterY > planetCenterY - planetBoundaryY) && (shipCenterY < planetCenterY + planetBoundaryY))
	{
		

		colliDet = true;
	}



	return colliDet;
}

/**
* \brief This method checks the qulition between planet and enemy ship.
* \details This method checks the qulition between planet and playere ship and also enemy ship.
* \param pair FLOAT, FOLAT- shipPoint, planetPoint
* \return bool collidet
*/
bool Movement::CheckEnemyCollision(pair <float, float> shipPoint, pair <float, float> enemyPoint)
{
	bool colliDet = false;

	float shipCenterX = shipPoint.first;
	float shipCenterY = shipPoint.second;

	float enemyLeft = enemyPoint.first;
	float enemyRight = enemyPoint.first + gridWidth;
	float enemyTop = enemyPoint.second;
	float enemyBottom = enemyPoint.second + gridHeight;

	float enemyCenterX = (enemyLeft + enemyRight) / 2;
	float enemyCenterY = (enemyTop + enemyBottom) / 2;

	float enemyBoundaryX = (gridWidth / 2.0f);
	float enemyBoundaryY = (gridHeight / 2.0f);

	if ((shipCenterX + enemyBoundaryX > enemyCenterX - enemyBoundaryX) && (shipCenterX - enemyBoundaryX < enemyCenterX + enemyBoundaryX)
		&& (shipCenterY + enemyBoundaryY > enemyCenterY - enemyBoundaryY) && (shipCenterY - enemyBoundaryY < enemyCenterY + enemyBoundaryY))
	{
		
		colliDet = true;
	}

	return colliDet;
}


/**
* \brief calculate the angle for rotation according to distance of the two objects.
* \details Calls upon a D2D1 method to specify the location of image file.
* \param: pair startP
*         pair endP
* \return float angle
*/
float Movement::calAngle(pair <float, float> startP, pair <float, float> endP)
{
	float angle;

	angle = float(atan2f(endP.second - startP.second, endP.first - startP.first) * 180 / M_PI);  //good one
		
	return angle;
}

//-Getters
float Movement::GetStarShipAngle(void)
{
	return shipAngle;
}

float Movement::GetEnemyAngle(void)
{
	return enemyAngle;
}
void Movement::SetEnemyAngle(float eAngle)
{

	enemyAngle = eAngle;
}

//-Setters
void Movement::SetStarShipAngle(float angle)
{
	shipAngle = angle;
}

void Movement::SetshipBStart(pair<float, float> shipBstart)

{
	shipBStart = shipBstart;
}
void Movement::SetshipDStart(pair<float, float> shipDstart)
{
	shipDstart = shipDstart;
}