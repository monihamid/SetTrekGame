#include "SpaceGrid.h"

void SpaceGrid::SpaceGrid()
{
	/*y = 0.0f;
	y = ySpeed = 0.0f;*/
	start = 0.0f;
	start = xSpeed = 5.0f;
	/*srand(time(NULL));
	x = rand() % 1024  ;
	y = rand() % 768 ;*/

	//background = new UploadImage(L"Images\\SectorBackground.bmp", gfx); //This is where we can specify our file system object!
	//planet1 = new UploadImage(L"Images\\Planet1.bmp", gfx);
	//planet2 = new UploadImage(L"Images\\Planet2.bmp", gfx);
	//planet3 = new UploadImage(L"Images\\Planet3.bmp", gfx);
	//starShip = new UploadImage(L"Images\\ShipDetail.bmp", gfx);
	//SpaceGrid();
	//PossibleSquare();
}


void Level1::Unload()
{
	/*delete background;
	delete planet1;
	delete planet2;
	delete planet3;
	delete starShip;*/


}


void Level1::Update()
{
	//ySpeed += 1.0f;
	//y += ySpeed;
	//if (y > 600)
	//{
	//	y = 600; //keep the ball from dropping below the screen
	//	ySpeed = -30.0f; //What does this do?
	//}

	//xSpeed += 0.02f;
	start += xSpeed;

	if (start > 1024)
	{
		/*Unload();
		Load();*/
		pickedGrid.clear();
		PossibleSquare();
		//PlanetStore();
		//Render();
		start = 0.0f;
		xSpeed = 5.0f;
		//creat new scren?


	}


}

void Level1::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	background->Draw(0, 0, 0 + windowWidth, 0 + windowHeight);
	//generating randon no for planet choise
	/*int i = (rand() % 3 +1);
	string ourPlanet1 =planet[i] ;*/
	for (int i = 0; i < pickedGrid.size(); i++)
	{
		planet1->Draw(pickedGrid[i].first, pickedGrid[i].second, pickedGrid[i].first + gridWidth, pickedGrid[i].second + gridHeight);
	}

	starShip->Draw(start, 300, start + gridWidth, 300 + gridHeight);

	/*planet1->Draw(x,y, x + gridWidth, y + gridHeight);
	planet2->Draw(x, y, x + gridWidth, y + gridHeight);
	planet3->Draw(x, y, x + gridWidth, y + gridHeight);
	starShip->Draw(start, 300, start + gridWidth, 300+gridHeight );*/

	/*gfx->DrawCircle(
	375.0f, y, 50.0f, 1.0f, 1.0f, 1.0f, 1.0f);*/


}

void SpaceGrid::SpaceGrid()
{

	int i = 0;
	int j = 0;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			//int count = 0;

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

void Level1::PossibleSquare()
{
	srand((unsigned)time(NULL));
	int rondomGrind;
	int target = 8;

	for (int index = 0; index<myVector.size(); index++)
	{
		//int target = 0;
		rondomGrind = (rand() % 20);
		if (rondomGrind == target)
		{
			gridPair.first = myVector[index].first;
			gridPair.second = myVector[index].second;
			pickedGrid.push_back(gridPair);
		}
		//target++;

	}
}

void Level1::PlanetStore()
{
	planet.push_back("planet1");
	planet.push_back("planet2");
	planet.push_back("planet3");

}


