#include "ConsoleControl.h"

#include <conio.h>
#include <windows.h>

ConsoleControl* ConsoleControl::instance = nullptr;

void ConsoleControl::SetColor(ConsoleColor ForeColor, ConsoleColor BackColor)
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD color = (BackColor << 4) | ForeColor;
	SetConsoleTextAttribute(hstdout, color);
}

void ConsoleControl::SetPosition(short int x, short int y)
{
	COORD pos = { x, y };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(console, pos);
}

void ConsoleControl::Clear()
{
	ClearCharacter(' ', WHITE, BLACK);
}

void ConsoleControl::ClearCharacter(char character, ConsoleColor ForeColor, ConsoleColor BackColor)
{
	COORD topLeft = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD color = (BackColor << 4) | ForeColor;
	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, character, screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, color,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

void ConsoleControl::Wait(unsigned long milisecons)
{
	Sleep(milisecons);
}

int ConsoleControl::ReadNextKey()
{
	int KB_code = 0;

	if (_kbhit())
	{
		KB_code = _getch();
	}
	return KB_code;
}

int ConsoleControl::WaithForReadNextKey()
{
	int KB_code = 0;

	while (KB_code == 0)
	{
		if (_kbhit())
		{
			KB_code = _getch();
		}
	}

	return KB_code;
}

void ConsoleControl::LockMutex()
{
	GetInstance()->consoleMutex->lock();
}

void ConsoleControl::UnlockMutex()
{
	GetInstance()->consoleMutex->unlock();
}

ConsoleControl* ConsoleControl::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ConsoleControl();
	}

	return instance;
}
