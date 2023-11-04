#include "pch.h"
#include "ConsoleHelper.h"

void ConsoleHelper::SetCursorPostion(int32 x, int32 y)
{	
	// Window API 관련
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<short>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void ConsoleHelper::SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<int16>(color));
}

void ConsoleHelper::ShowConsoleCursor(bool flag)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = flag;
	::SetConsoleCursorInfo(output, &cursorInfo);
}
