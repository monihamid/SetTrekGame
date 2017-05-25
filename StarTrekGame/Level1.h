/*
* PROJECT		: Assignment 03 SET Trek
* FILE			: Level1.h
* PROGRAMMER	: Monira Sultana
* DATE			: 2017/04/23
* DESCRIPTION	: The header file containing the class definition for the Level1.
* This file is Supplied by Prof. Russell Foubert updated by student
*/

#pragma once
#include <mmsystem.h>
#include <mciapi.h>
#include "GameLevel.h"
#include "Starship.h"
#include "Movement.h"
#include "TimerClass.h"
#include <vector>

using namespace std;



class Level1 : public GameLevel
{
	
	float startES;
	float eShipMove;
	float start;
	float xSpeed;
	int x;
	int y;
	bool coldetect;
	bool m_enemyDetect;
	string planetC;
	string music;
	
	int randomPlanet = 0;
	UploadImage* background;
	UploadImage* planet1;
	UploadImage* planet2;
	UploadImage* planet3;
	Starship* shipBase;
	Starship* shipDetails;
	Starship* enemyShip;
	UploadImage* scan;
	UploadImage* exlplosion;
	UploadImage* shield;
	Movement* movement;

	
	float top;
	float left;
	
	float mouseEndX;
	float mouseEndY;

	float windowWidth;
    float windowHeight;
	float gridWidth;
	float gridHeight;
	

	pair<float, float> gridPair;     //makes pair for picked grid value to put in to the myVector
	
	vector <pair <float, float>> myVector;   //storing all the possible grid values

	vector <pair <float, float>> pickedGrid;  //storing randomly picked grid values
	vector <string> planet;               //store planets
	
	pair< int, string>gridPlanet;       //makes pair for picked grid and planet value to put in to the gplCombination
	vector <pair <int, string>> gplCombination;  //strore picked grid value and corrosponding planet to place
	vector <string> playmusic;

public:
	//Constructor
	 Level1();
	 //destructor
	~Level1();
	void Load() override;
	void Unload() override;
	void Process() override;
	void Update() override;
	void Render() override;
	void SpaceGrid();
	void PossibleSquare();
	void PlanetStore();
	void NewScene();
	void MusicStore();
	
	//Geter
	float GetWindowWidth(void);
	float GetWindowHeight(void);
	void SetWindowWidth(float width);
	void SetWindowHeight(float height);
	void setColdetect(bool colli);
	void Setm_enemyDetect(bool coli);
	string GetPlayMusic(void);
	void SetPlayMusic(string music);
};
