#pragma once
// 실질적으로 미로를 생성

#include <Windows.h>
#include "Types.h"

enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

class ConsoleHelper
{
public:
	// Cursor 위치 설정
	static void SetCursorPostion(int32 x, int32 y);
	// Cursor 색상 설정
	static void SetCursorColor(ConsoleColor color);
	// Cursor 보여줄지 여부 설정
	static void ShowConsoleCursor(bool flag);
};