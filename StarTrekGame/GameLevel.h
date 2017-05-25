/*
* PROJECT		: Assignment 03 SET Trek
* FILE			: GameLevel.h
* PROGRAMMER	: Monira Sultana
* DATE			: 2017/04/24
* DESCRIPTION	: The header file containing the class definition for the GameLevel.
* This file is Supplied by Prof. Russell Foubert
*/
#pragma once
#include "Graphics.h"
#include "InputClass.h"
#include "UploadImage.h"


class GameLevel
{
protected:
	static Graphics* gfx;

public:
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Process() = 0;
};
