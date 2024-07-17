#pragma once

#include <Windows.h>
#include "Types.h"

enum class ConsoleColor 
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED|GREEN,
	WHITE = RED | GREEN | BLUE
};
class ConsoleHelper
{
public:
	// Cursor Position 설정
	static void SetCursorPosition(int32 x, int32 y);
	// Cursor Color 설정
	static void SetCursorColor(ConsoleColor color);
	// Cursor를 보이게 할지 말지
	static void ShowConsoleCursor(bool flag);

};

