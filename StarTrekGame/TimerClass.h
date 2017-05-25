

/*
* PROJECT		: Assignment 02 SET Trek
* FILE			:TimerClass.h
* PROGRAMMER	: Monira Sultana
* DATE			: 2017/04/13
* DESCRIPTION	: This file contain defination for Timer class
*/
#pragma once
#include <time.h>


class TimerClass
{
public:
	
	static clock_t start;
	static clock_t current;
	static clock_t difference;

	static void Init(void);

	static void StartTimer(void);
	static void EndTimer(void);
	static int GetCurrent(void);

	clock_t GetStart(void);
	clock_t GetDifference(void);
	void SetStart(clock_t start);
	void SetCurrrent(clock_t current);
	void SetDifference(clock_t diff);

};
