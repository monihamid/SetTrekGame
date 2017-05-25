#pragma once
#include <Windows.h>
#include "Graphics.h"
#include "GameLevel.h"
#include "Level1.h"
#include <vector>
#include "UploadImage.h"
#include <vector>

using namespace std;

class Movement
{
private:
	float xCoordinator;
	float yCoordinator;
	POINT mouseP;

	POINT shipBStart;              //direction of shipbase
	POINT shipDStart;                  //direction of shipdetails
	POINT enemyShipStart;

	/*UploadImage* shipBase;
	UploadImage* shipDetails;
	UploadImage* enemyShip;*/

public:

	Movement();
	~Movement();

	POINT AddDistance(POINT x);
	void SetXCoordinator(int x);
	void SetYCoordinator(int y);
	POINT SetMouseP(POINT pt);

	POINT PlayerSMove(POINT shipStart, POINT mousePoint);
	void EnemySMove(POINT pt);
};