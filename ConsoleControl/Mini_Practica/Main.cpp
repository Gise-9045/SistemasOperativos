#include <iostream>
#include"ConsoleControl.h"
#include"Timer.h"
#include"QuestionManager.h"


void Answer()
{
	std::cout << "aaaaa"; 
}

int main()
{
	Question* question = new Question("cuantos dedos hay?"); 

	Timer::StartTime(4, [question]() {question->Draw();} );

	while (true)
	{

	}
}

