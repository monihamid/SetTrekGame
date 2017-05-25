/*
* PROJECT		: Assignment 03 SET Trek
* FILE			: Level1.cpp
* PROGRAMER     : Monira Sultana
* DATE			: 2017/04/14
* DESCRIPTION	: This class render the objects to the screen.
* This file is Supplied by Prof. Russell Foubert and updated by the student
*/


#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"
#include <ctime> 
#include <string>
#include <iostream>
//#include "Point.h"



/**
* \brief Basic constructor for the Level1 class.
* \details All the private data members are set to a safe value.
* \parm Nothing
* \return Nothing
*/
Level1::Level1()
{
	windowWidth = gfx->GetWindowWidth();
	windowHeight = gfx->GetWindowHeight();
	gridWidth = windowWidth / 10;
	gridHeight = windowHeight / 10;
	
	start = 0.0f;
	start = xSpeed = 0.0f;

	coldetect = false;
	m_enemyDetect = false;
	startES = windowWidth- gridWidth;     
	startES = eShipMove = windowWidth;	
	
	left  = 0.0f;
	top = 0.0f;
	planetC;
	music;
}
/**
* \brief Basic destructor for the Graphics class.
* \details it will release the objects end of the game.
*/
Level1::~Level1()
{

}

/**
* \brief Initialize rendering the images.
* \details Calls upon a D2D1 method to specify the location of image file.
* \param 
* \return Nothing
*/
void Level1::Load()
{
	background = new UploadImage(L"Images\\SectorBackground.bmp", gfx, false); //This is where we can specify our file system object!
	planet1 = new UploadImage(L"Images\\Planet1.bmp", gfx);
	planet2 = new UploadImage(L"Images\\Planet2.bmp", gfx);
	planet3 = new UploadImage(L"Images\\Planet3.bmp", gfx);
	scan = new UploadImage(L"Images\\ScanedPlanet.bmp", gfx, false);
	exlplosion = new UploadImage(L"Images\\Explosion.bmp", gfx);
	

	shield = new UploadImage(L"Images\\shield2.bmp", gfx,false);

	// Creating the Starship objects
	shipDetails = new Starship(gfx, 0, 384);
	shipBase = new Starship(gfx, 0, 384);

	enemyShip = new Starship(gfx, 1028, 384);

	// Loading the image resources
	shipDetails->InitImage(L"Images\\ShipDetail.bmp");
	shipBase->InitImage(L"Images\\ShipBase.bmp");
	enemyShip->InitImage(L"Images\\EnemyShip.bmp");


	
	planet1->ApplyChromaEffect();
	planet2->ApplyChromaEffect();
	planet3->ApplyChromaEffect();
	shield->ApplyChromaEffectBack();

	shipBase->ChromaEffect(0.0f, 1.0f, 0.0f);
	shipDetails->ChromaEffect(0.0f, 1.0f, 0.0f);
	enemyShip->ChromaEffect(0.0f, 0.0f, 1.0f);
	exlplosion->ApplyChromaEffect();
	SpaceGrid();
	PossibleSquare();
	PlanetStore();
	MusicStore();
	// Setting the 'Movement" window sizes
	movement = new Movement(windowWidth, windowHeight);

	// Initialize the TimerClass
	TimerClass::Init();

	// randonmy play the background music song (repeat mode)

	int random = rand() % 3;
	string sound = playmusic[random];

	LPCTSTR musicP = (LPCTSTR)sound.c_str();

	mciSendString(musicP, 0, 0, 0);
}
	

/**
* \brief Unload the images.
* \details Unload images from rendering.
* \param Nothing
* \return Nothing
*/
void Level1::Unload()
{
	delete background;
	delete planet1;
	delete planet2;
	delete planet3;
	delete shipDetails;
	delete enemyShip;
	delete shield;
	delete scan;
	delete exlplosion;
}


/**
* \brief This method updates the mouse point and angle forplayer ship direction.
* \details This methods updates the screen after each rendering.
* \param float
* \return Nothing
*/
void Level1::Process()
{
if (InputClass::IsLeftClick)
{
	InputClass::IsLeftClick = false;

	// where the mouse click coordinate is eg. (x, y)
	mouseEndX = InputClass::LeftMouseX;
	mouseEndY = InputClass::LeftMouseY;

	pair<float, float> startShipPoint;
	pair<float, float> mousePoint = { mouseEndX, mouseEndY };
	startShipPoint = movement->GetCurrentPositionPS();

	float angle = movement->calAngle(startShipPoint, mousePoint);
	movement->SetStarShipAngle(angle);
}

// Player "right-clicked"
if (InputClass::IsRightClick)
{
	// Start the timer for how long the laser will appear
	TimerClass::StartTimer();

	// Play the laser shot sound effect
	mciSendStringW(L"play .\\Sounds\\LaserShot.wav", nullptr, 0, nullptr);

	InputClass::IsRightClick = false;

	 
}
}

/**
* \brief This method updates the screen.
* \details This methods updates the screen after each rendering.
* \param Nothing
* \return Nothing
*/
void Level1::Update()
{
	pair <float, float> shipBStart = movement->GetCurrentPositionPS();
	pair<float, float> enemyShipMove = movement->GetEnemyShipStart();

	for (int i = 0; i < pickedGrid.size(); i++)
	{
		// Get the coordinates (x, y) of a single planet
		pair<float, float> planetCoord = { pickedGrid[i].first, pickedGrid[i].second };//planet

		string planet = gplCombination[i].second;
		planetC = planet;
		bool isCollide = movement->CheckCollosion(shipBStart, planetCoord);

		if (isCollide)
		{
			setColdetect(isCollide);
			
			mciSendStringW(L"play .\\Sounds\\Collision.wav", nullptr, 0, nullptr);
			break;
		}
		else
		{
			setColdetect(isCollide);
		}
	}
	// pick a background sound
	 srand((unsigned)time(NULL));
	 	  int random;
		 random = rand() % 3;
	for (int i = 0; i < playmusic.size(); i++)
	{
		if ( i== random)
		{
			string music = playmusic[i];
			 SetPlayMusic(music);
			
		}
	}


	//--------------------
	// Enemy Collision detection
	bool enemyCollisionDet = movement->CheckEnemyCollision(shipBStart, enemyShipMove);
	if (enemyCollisionDet)
	{
		Setm_enemyDetect(enemyCollisionDet);
		float currentEnergyLevel = shipDetails->GetEnergyLevel();
		shipDetails->SetEnergyLevel(currentEnergyLevel - 300);
	}

	pair <float, float> rightMouseClick;
	rightMouseClick.first = InputClass::RightMouseX;
	rightMouseClick.second = InputClass::RightMouseY;

	bool enemyDead = movement->CheckEnemyCollision(rightMouseClick, enemyShipMove);
	if (enemyDead)
	{
		if (!enemyShip->GetIsDead())
		{
			enemyShip->SetIsDead(true);

			// Play the explosion (Collision) sound effect
			mciSendStringW(L"play .\\Sounds\\Collision.wav", nullptr, 0, nullptr);
			
		}
	}

	//
	//----------------------

	//--------------------
	// Moving the PLAYER SHIP
	pair <float, float> mouseP;
	mouseP.first = InputClass::LeftMouseX;
	mouseP.second = InputClass::LeftMouseY;
	movement->PlayerMove(mouseP);

	
	//
	//----------------------

	//--------------------
	// Moving the ENEMEY SHIP
	if (!enemyShip->GetIsDead())
	{
		movement->enemySMove();
	}
	//
	//----------------------
		

	if (movement->GetShipDStart().first >= windowWidth || movement->GetShipDStart().second >= windowHeight 
		|| movement->GetShipDStart().first <0 || movement->GetShipDStart().second < 0 || enemyCollisionDet)
	{
		NewScene();
	}	
	if (shipDetails->GetEnergyLevel() <= 0)
	{
		mciSendStringW(L"play .\\Sounds\\gameEnd.wav", nullptr, 0, nullptr);
		exit(EXIT_FAILURE);
		
		
	}
}
/**
* \brief This method render the image.
* \details This methods render the image and display on window.
* \It displays background planets and ship.
* \param Nothing
* \return Nothing
*/
void Level1::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.0f);
	background->DrawBackground(0, 0 , windowWidth, windowHeight);
	
	for (int i = 0; i < pickedGrid.size(); i++)
	{
		 
		if (gplCombination[i].second=="planet1")
		{
			planet1->DrawPlanet(pickedGrid[i].first, pickedGrid[i].second);
		}
		if (gplCombination[i].second == "planet2")
		{
			planet2->DrawPlanet(pickedGrid[i].first, pickedGrid[i].second);
		}
		if (gplCombination[i].second == "planet3")
		{	
			planet3->DrawPlanet(pickedGrid[i].first, pickedGrid[i].second);
		}
	}
	
	
	float centerX = movement->GetCurrentPositionPS().first;
	float centerY = movement->GetCurrentPositionPS().second;

	float angle = movement->GetStarShipAngle();
	D2D1::Matrix3x2F rotate = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(centerX, centerY));

	gfx->GetRenderTarget()->SetTransform(rotate);

	shipBase->Draw(movement->GetShipBStart().first, movement->GetShipBStart().second);
	shipDetails->Draw(movement->GetShipDStart().first, movement->GetShipDStart().second);

	gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	
	//=========
	//----
	// rendering enemy ship
	float enemySX = movement->GetCurrentPositionEnemyS().first;
	float enemySY = movement->GetCurrentPositionEnemyS().second;

	pair<float, float> shipPoint = movement->GetCurrentPositionPS();
	pair<float, float> enemyPoint = movement->GetCurrentPositionEnemyS();

	float angleE = movement->calAngle( shipPoint, enemyPoint);
	movement->SetEnemyAngle(angleE);

	angleE = movement->GetEnemyAngle();	

	enemyShip->Draw(movement->GetEnemyShipStart().first, movement->GetEnemyShipStart().second);

	gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	//----
	//=========

	if (coldetect)
	{
		int i = 0;
		scan->DrawBackground(150, 90, 150+400, 90+300);
		if(planetC == "planet1")
		{
			planet1->DrawPlanet(180, 120);
		}
		if (planetC == "planet2")
		{
			planet2->DrawPlanet(180, 120);
		}
		if (planetC == "planet3")
		{
			planet3->DrawPlanet(180, 120);
		}
	}

	float xaxis = 0.0f;
	float yaxis = 0.0f;
	xaxis = movement->GetCurrentPositionPS().first -gridWidth ;
	yaxis = movement->GetCurrentPositionPS().second -gridHeight;
	if (shipDetails->GetEnergyLevel() <250)
	{	    
			
		shield->DrawBackground(xaxis, yaxis, xaxis+200, yaxis+180); 
		shipDetails->SetEnergyLevel(1000); 
		
	}
	
	//===============
	if (m_enemyDetect)
	{
		scan->DrawBackground(150, 90, 150 + 400, 90 + 300);
		
		
	}
	//================

	//Draw line with red color as lasear
	
		if (TimerClass::GetCurrent() < 500)
		{
			float rightMouseX = InputClass::RightMouseX;
			float rightMouseY = InputClass::RightMouseY;
			gfx->DrawLine(shipPoint.first, shipPoint.second, rightMouseX, rightMouseY, 1, 0, 0, 5.0f);
		}
	

	if (enemyShip->GetIsDead())
	{
		exlplosion->DrawPlanet(movement->GetEnemyShipStart().first, movement->GetEnemyShipStart().second);

	}
}

/**
* \brief This method generate all possible grib values for window (screen).
* \details This method fill up vector and store all possible grib values for window.
* \param Nothing
* \return Nothing
*/
void Level1::SpaceGrid()
{
	
	int i = 0;
	int j = 0;
	
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			
			float xa = i*gridWidth;
			float yb = j*gridHeight;
			// This code here is the pair
			//	(i, j)
			gridPair.first = xa;
			gridPair.second = yb;

			myVector.push_back(gridPair);
			
		}
	}
		
	
}
/**
* \brief This method randomly generate all possible grid values that can have a planet.
* \details This method randomly generate all possible grid values and stores in a vector that cah have a planet 
* \param Nothing
* \return Nothing
*/
void Level1::PossibleSquare()
{
	srand((unsigned)time(NULL));
	int rondomGrid;
	int target = 8;
	int index = 0;
	for ( index = 0; index < myVector.size(); index++) 
	{
		
		rondomGrid = (rand() % 20);
		if (rondomGrid == target)
		{
			gridPair.first = myVector[index].first;
			gridPair.second = myVector[index].second;
			
			pickedGrid.push_back(gridPair);
		}
		
		
	}
}
/**
* \brief This method place all planet to a vector and place grid value and planet to another vector.
* \details This method place all planet to a vector and and randomly picked planet and  corronsponding grid values
* \ in a vector that cah have a planet.
* \param Nothing
* \return Nothing
*/
void Level1::PlanetStore()
{
	srand((unsigned)time(NULL));
	planet.push_back("planet1");
	planet.push_back("planet2");
	planet.push_back("planet3");

	
	int index = 0;;
	for ( index = 0; index < pickedGrid.size(); index++)
	{
		randomPlanet = (rand() % 3);

		gridPlanet.first = index;
		gridPlanet.second = planet.at(randomPlanet);//randomPlanet;
		gplCombination.push_back(gridPlanet);
	}
}

/**
* \brief This method place all background music path as string to a vector.
* \details This method place all background music path as string to a vector.
* \param Nothing
* \return Nothing
*/
void Level1::MusicStore()
{
	
	playmusic.push_back("play Sounds\\Background.wav");
	playmusic.push_back("play Sounds\\OriginalSeriesMainTitle.wav");
	playmusic.push_back("play Sounds\\audiosprites.wav");
}
/**
* \brief This method create a new screen after collision or ships are out of boundary.
* \details This method create a new screen after collision or ships are out of boundary.
* \param Nothing
* \return Nothing
*/
void Level1::NewScene()
{
	//create new scren
	pickedGrid.clear();
	gplCombination.clear();
	PossibleSquare();
	PlanetStore();
	MusicStore();
	// Make sure mouse position is reset
	InputClass::LeftMouseX = 0;
	InputClass::LeftMouseY = 384;
	InputClass::IsLeftClick = false;

	// Reset the positions of all the ships
	pair<float, float> newPlayerPosition = { 0, 384 };
	movement->SetshipBStart(newPlayerPosition);
	movement->SetCurrentPositionPS(newPlayerPosition);

	pair<float, float> newEnemyPosition = { 1024, 384 };
	movement->SetEnemyShipStart(newEnemyPosition);
	movement->SetCurrentPositionEnemyS(newEnemyPosition);
}



float Level1:: GetWindowWidth(void)
{
	return windowWidth;
}
float Level1:: GetWindowHeight(void)
{
	return windowHeight;
}
/**
* \brief This method set value for window width.
* \details This method set value for window width.
* \param FLOAT- width
* \return Nothing
*/
void Level1::SetWindowWidth(float width)
{
	windowWidth = width;
		
}
/**
* \brief This method set value for window height.
* \details This method set value for window height.
* \param FLOAT- height
* \return Nothing
*/
void Level1::SetWindowHeight(float height)
{
	windowHeight = height;
}

void Level1::setColdetect(bool colli)
{
	coldetect = colli;
}


void Level1::Setm_enemyDetect(bool coli)
{
	m_enemyDetect = coli;

}

//Getter and Setter
string Level1::GetPlayMusic(void)
{
	return music;
}
void Level1::SetPlayMusic(string music)
{
	music = music;
}