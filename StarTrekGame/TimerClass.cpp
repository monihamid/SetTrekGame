/*
* PROJECT		: Assignment 03 SET Trek
* FILE			: TimerClass.cpp
* PROGRAMER     : Monira Sultana
* DATE			: 2017/04/14
* DESCRIPTION	: This class count start time and end time. This is a global class so other class has direct access on it.

*/
#include "TimerClass.h"



clock_t TimerClass:: start;
clock_t TimerClass:: current;
clock_t TimerClass:: difference;


/**
* \brief Initilize data field.
* \details Initilize data field.
* \param: None         
* \return Nothing
*/
void TimerClass::Init(void)
{
	start = 0;
	current = 0;
	difference = 0;
}


void TimerClass::StartTimer(void)
{
	start = clock();
}


void TimerClass::EndTimer(void)
{
	difference = clock() - start;
}


int TimerClass::GetCurrent(void)
{
	clock_t current;

	current = clock() - start;

	int milliseconds = current * 1000 / CLOCKS_PER_SEC;
	return milliseconds;
}


clock_t TimerClass::GetStart(void)
{
	return start;
}


clock_t TimerClass::GetDifference(void)
{
	return difference;

}


void TimerClass::SetStart(clock_t start)
{
	start = start;
}


void TimerClass::SetCurrrent(clock_t current)
{
	current = current;
}


void TimerClass::SetDifference(clock_t diff)
{
	diff = difference;
}

