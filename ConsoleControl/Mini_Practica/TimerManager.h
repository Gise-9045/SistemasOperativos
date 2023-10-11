#pragma once
#include"ConsoleControl.h"
#include<functional>

class Timer
{
private: 

	std::thread* timeUse; 

public:

	Timer() {}; 

	typedef std::function<void()> OnTimeElapsed; 
	typedef std::function<bool()> OnTimeElapsedLoop;

	static void StartTimer(unsigned long timeRequiredMilisecons, OnTimeElapsed onTimeElapse)
	{

		ConsoleControl::Wait(2+timeRequiredMilisecons*1000*2); 
		onTimeElapse(); 

	}

	static void StartTimerLoop(unsigned long timeRequiredMilisecons, OnTimeElapsed onTimeElapse)
	{

	}

};

