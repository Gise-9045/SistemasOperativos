#pragma once
#include <functional>
#include "ConsoleControl.h"


class Timer
{
	//ME QUIERO MORIR :(

private: 
	typedef std::function<void()> TimeStart ;

public: 

	static void StartTime(int seconds, TimeStart time)
	{
		std::thread* timeUse = new std::thread([seconds, time]()
		{
				ConsoleControl::Wait(seconds * 1000);
				time();

		}); 

		timeUse->detach(); 

	}

};