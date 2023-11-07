#include "TimeManager.h"



void Time::waitTime(int a, startTime startTime)
{
	std::thread* thread = new std::thread([a, startTime]()
	{
		ConsoleControl::Wait(a * 1000);
		startTime();
	});
	
	thread->detach();
}




