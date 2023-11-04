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
	WALL,
};
class Board
{
public:
	Board();
	~Board();

	// 미로 사이즈 초기화, size는 홀수여야함.
	void Init(int32 size, Player* player);

	// 렌더링
	void Render();

	// Map를 생성하는 알고리즘
	void GenerateMap();
	// pos 위치에 어떤 TileType를 가지고 있는지 확인
	TileType GetTileType(Pos pos);
	// pos 위치에 어떤 Color를 가져야 할지 정함.
	ConsoleColor GetTileColor(Pos pos);

	// 미로의 시작점
	Pos GetEnterPos() { return Pos{ 1,1 }; }
	// 미로의 출구
	Pos GetExitPos() { return Pos{ _size - 2, _size - 2 }; }

private:
	TileType	_tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE] = {};
	int32		_size = 0;
	Player*		_player = nullptr;
};

