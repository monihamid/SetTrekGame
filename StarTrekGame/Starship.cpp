/*
* PROJECT		: Assignment 03 SET Trek
* FILE			: StarShip.cpp
* PROGRAMER     : Monira Sultana
* DATE			: 2017/04/14
* DESCRIPTION	: This class create the movable objects USS ship and enemy ship. This is a global class so other class has direct access on it.

*/

#include "Starship.h"

/**
* \brief Basic constructor for the Starship class.
* \details All the private data members are set to a safe value.
* \parm    Graphics* graphics
*		   float startPosX			
*		   float startPosY
* \return starShip
*/
Starship::Starship(Graphics* graphics, float startPosX, float startPosY)
{
	// Get a reference to the Graphics class
	gfx = graphics;

	// Initialize other data members to default values
	bmp = nullptr;
	effect = nullptr;
	image = nullptr;

	shipAngle = 0.0f;
	energyLevel = kDefaultEnergyLevel;

	// starting position of ship
	shipDStart.first = startPosX;		// x-position of where ship starts
	shipDStart.second = startPosY;		// y-position of where ship starts

	isShooting = false;
	isDead = false;
}
/**
* \brief Basic destructor for the Graphics class.
* \details All the private data members are set to a safe value.
*/

Starship::~Starship()
{
	if (image)
	{
		delete image;
		image = nullptr;
	}
}

/**
* \brief render the image.
* \details render the image
* \param wchar_t* filename
* \param  bool shouldScale
* \Return- Nothing
*/

void Starship::InitImage(wchar_t* filename, bool shouldScale)
{
	image = new UploadImage(filename, gfx, true);
}


void Starship::ChromaEffect(float r, float g, float b)
{
	gfx->GetRenderTarget()->CreateEffect(CLSID_D2D1ChromaKey, &effect);

	// Get the bitmap resource from UploadImage
	bmp = image->GetBitmap();

	effect->SetInput(0, bmp);
	effect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(r, g, b));
	effect->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.2f);
	effect->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, false);
	effect->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, false);
}


void Starship::Draw(float left, float top)
{
	gfx->GetRenderTarget()->DrawImage(
		effect,
		D2D1::Point2F(left, top),
		D2D1::RectF(0, 0, gfx->GetWindowWidth() / 10, gfx->GetWindowHeight() / 10)
	);
}


//
// GENERAL METHODS
//
/**
* \brief calculate the angle for rotation according to distance of the two objects.
* \details Calls upon a D2D1 method to specify the location of image file.
* \param: pair startP
*         pair endP
* \return float angle
*/
void Starship::CalculateAngle(pair <float, float> startP, pair <float, float> endP)
{
	float angle;

	angle = float(atan2f(endP.second - startP.second, endP.first - startP.first) * 180 / M_PI);  //good one
	shipAngle = angle;
}


//
// MOVEMENT METHODS
//
/**
* \brief move the player ship.
* \details Calls upon a D2D1 method to specify the location of image file.
* \param: pair mouseP
*         pair endP
* \return Nothing
*/
void Starship::MoveShip(pair <float, float> mouseP)
{
	pair <float, float> playerPosition;
	playerPosition = GetCenterOfShip();

	pair<float, float> cpt;

	// MOVE SHIP AUTOMATICALLY
	if (mouseP.first == 0 && mouseP.second == 0)
	{
		
		//storing the player ship positions
		cpt.first = shipBStart.first;
		cpt.second = shipBStart.second;
		SetCenterOfShip(cpt);
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
			SetCenterOfShip(cpt);
		}
		if (playerPosition.first > mouseP.first)
		{
			shipBStart.first--;
			shipDStart.first--;

			//storing current position
			cpt.first = shipBStart.first;
			cpt.second = shipBStart.second;
			SetCenterOfShip(cpt);
		}

		if (playerPosition.second < mouseP.second)
		{
			shipBStart.second++;
			shipDStart.second++;

			//storing current position
			cpt.first = shipBStart.first;
			cpt.second = shipBStart.second;
			SetCenterOfShip(cpt);
		}
		if (playerPosition.second > mouseP.second)
		{
			shipBStart.second--;
			shipDStart.second--;

			//storing current position
			cpt.first = shipBStart.first;
			cpt.second = shipBStart.second;
			SetCenterOfShip(cpt);
		}
	}

	// Restarting the Player ship on the left-side
	if (shipBStart.first > 1024 || shipBStart.second > 768
		|| shipBStart.first < 0 || shipBStart.second < 0)
	{
		shipBStart.first = 0;
		shipBStart.first = shipBStart.first++;
		shipBStart.second = 384;
		shipDStart.first = 0;
		shipDStart.first = shipDStart.second++;
		shipDStart.second = 384;

		cpt.first = shipBStart.first;
		cpt.second = shipBStart.second;
		SetCenterOfShip(cpt);
	}
}



//
// COLLISION DETECTION METHODS
//
bool Starship::CheckPlanetCollosion(pair <float, float> shipPoint, pair <float, float> planetPoint)
{
	bool colliDet = false;

	float gridWidth = gfx->GetWindowWidth() / 10;
	float gridHeight = gfx->GetWindowHeight() / 10;

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
bool Starship::CheckEnemyCollision(pair <float, float> shipPoint, pair <float, float> enemyPoint)
{
	bool colliDet = false;

	float gridWidth = gfx->GetWindowWidth() / 10;
	float gridHeight = gfx->GetWindowHeight() / 10;

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



//
// SETTERS
//
/**
* \brief This method set value for current Position for player ship.
* \details This method set value for  current Position for player ship.
* \param pair FLOAT, FOLAT- playerShipPosition
* \return Nothing
*/
void Starship::SetCenterOfShip(pair<float, float> playerShipPosition)
{
	float gridWidth = gfx->GetWindowWidth() / 10;
	float gridHeight = gfx->GetWindowHeight() / 10;

	float centreX = playerShipPosition.first + gridWidth / 2;
	float centrY = playerShipPosition.second + gridHeight / 2;

	currentPositionPS.first = centreX;
	currentPositionPS.second = centrY;
}

void Starship::SetEnergyLevel(float energy)
{
	energyLevel = energy;
}

void Starship::SetIsDead(bool dead)
{
	isDead = dead;
}


//
// GETTERS
//
pair<float, float> Starship::GetShipDStart()
{
	return shipBStart;
}

pair<float, float> Starship::GetShipBStart()
{
	return shipBStart;
}

pair <float, float> Starship::GetCenterOfShip()
{
	return currentPositionPS;
}

float Starship::GetShipAngle(void)
{
	return shipAngle;
}

bool Starship::GetIsDead(void)
{
	return isDead;
}

float Starship::GetEnergyLevel(void)
{
	return energyLevel;
}