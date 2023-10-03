#include<iostream>
#include "ConsoleControl.h"


void Ejemplos()
{
	ConsoleControl::SetColor(ConsoleControl::CYAN);

	std::cout << "Hello World!" << std::endl;

	ConsoleControl::SetColor(ConsoleControl::WHITE);

	ConsoleControl::SetPosition(5, 3);
	std::cout << "SSSSSSSS";

}

void LeerInputTeclas()
{
	int keycode = ConsoleControl::WaithForReadNextKey(); 

	std::cout << "La key Code es : " << keycode; 
}

int main()
{
	LeerInputTeclas(); 

}