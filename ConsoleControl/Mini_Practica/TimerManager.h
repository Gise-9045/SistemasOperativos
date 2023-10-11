#pragma once
#include"ConsoleControl.h"
#include<functional>

class Timer
{
public:
	typedef std::function<void()> OnTimeElapsed; 
	typedef std::function<bool()> OnTimeElapsedLoop;

public: 
	static void StartTimer(unsigned long timeRequiredMilisecons ,  OnTimeElapsed onTimeElapse)
	{

		std::thread* thread = new std::thread([timeRequiredMilisecons, onTimeElapse]()
		{
				
		}

	}

	static void StartTimerLoop(unsigned long timeRequiredMilisecons, OnTimeElapsed onTimeElapse)
	{

	}

};

