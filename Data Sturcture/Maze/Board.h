#pragma once
#include "ConsoleHelper.h"

class Player;

enum
{
	BOARD_MAX_SIZE = 100
};

enum class TileType
{
	NONE = 0,
	EMPTY,
	WALL
};

class Board
{
public:
	Board();
	~Board();

	void Init(int32 size, Player* player);
	void Render();

	// 알고리즘에 의해 맵을 생성
	void GenerateMap();

	// 해당 Position의 Tile Color를 설정함
	ConsoleColor SetTileColor(Pos pos);

	// 해당 Position의 위치의 TileType를 가져옴
	TileType GetTileType(Pos pos);

	// 미로 출발점
	Pos GetEnterPos() { return  Pos{ 1,1 }; }
	// 미로의 도착점
	Pos GetExitPos() { return Pos{ _size - 2, _size - 2 }; }

	int32 GetSize() { return _size; }

private:
	// 맵의 최대 사이즈
	TileType	_tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE] = {};
	// 실질적으로 사용할 맵 사이즈
	int32		_size = 0;
	// 맵에 참가한 player
	Player* _player = nullptr;
};

