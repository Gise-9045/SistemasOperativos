#pragma once
#include <ctime>
#include <chrono>
#include "ConsoleControl.h"
#include <functional>

class Time
{
private:
	typedef std::function<void()> startTime;
	

public:
	Time() {}
	void waitTime(int a, startTime startTime);
};
