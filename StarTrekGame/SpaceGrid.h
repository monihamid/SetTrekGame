#pragma once
#include "GameLevel.h"
#include <vector>
using namespace std;


class SpaceGrid: public GameLevel

{
	UploadImage* background;
	UploadImage* planet1;
	UploadImage* planet2;
	UploadImage* planet3;
	UploadImage* starShip;

	float windowWidth = 1024;
	float windowHeight = 768;
	float gridWidth = windowWidth / 10;
	float gridHeight = windowHeight / 10;

	pair<float, float> gridPair;
	vector <pair <float, float>> myVector;
	vector <pair <float, float>> pickedGrid;
	vector <string> planet;

public:

	/*void Load() override;
	void Unload() override;
	void Update() override;
	void Render() override;*/
	void SpaceGrid();	
	void PossibleSquare();
	void PlanetStore();

};
