#pragma once
#include <string>
#include "ConsoleControl.h"
#include<iostream>
class Question
{
private: 

	std::string _question; 

public: 

	Question(std::string writeQuestion) : _question(writeQuestion) {};

	void Draw()
	{
		ConsoleControl::SetColor(ConsoleControl::BLUE);
		std::cout  <<_question << std::endl; 
	}

	
}; 