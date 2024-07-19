#pragma once
// 미리 컴파일된 헤더 -> .cpp파일에 넣어주지 않으면 문제가 발생함
// 공용으로 사용할 내용

#include <windows.h>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include "Types.h"

using namespace std;

// Cursor의 Position
struct Pos
{
	bool operator==(Pos& other)
	{
		return y == other.y && x == other.x;
	}

	bool operator!=(Pos& other)
	{
		return y != other.y || x != other.x;
	}

	bool operator<(const Pos& other) const
	{
		if (y != other.y)
			return y < other.y;
		return x < other.x;
	}

	Pos operator+(Pos& other)
	{
		Pos ret;
		ret.y = y + other.y;
		ret.x = x + other.x;
		return ret;
	}

	Pos& operator+=(Pos& other)
	{
		y += other.y;
		x += other.x;
		return *this;
	} 

	int32 y = 0;
	int32 x = 0;
};

// Cursor 이동 방향
enum Dir
{
	DIR_UP = 0,
	DIR_LEFT = 1,
	DIR_DOWN = 2,
	DIR_RIGHT = 3,

	DIR_COUNT = 4
};