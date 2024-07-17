#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"
#include "Player.h"

const char* TILE = "■";

Board::Board()
{

}

Board::~Board()
{

}

void Board::Init(int32 size, Player* player)
{
	_size = size;
	_player = player;

	GenerateMap();
}

void Board::Render()
{
	ConsoleHelper::SetCursorPosition(0, 0);
	ConsoleHelper::ShowConsoleCursor(false);

	for (int32 y = 0; y < 25; y++)
	{
		for (int32 x = 0; x < 25; x++)
		{
			// y, x 좌표의 Tile의 color를 설정
			ConsoleColor color = SetTileColor(Pos{ y,x });
			// 설정된 Tile의 Color를 적용함.
			ConsoleHelper::SetCursorColor(color);

			cout << TILE << " ";
		}
		cout << endl;
	}
}

// Binary Tree 미로 생성 알고리즘
// - Maze For Programmers
void Board::GenerateMap()
{
	// 먼저 벽을 세우고 
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_tile[y][x] = TileType::WALL;
			else
				_tile[y][x] = TileType::EMPTY;
		}
	}

	// EMPTY Tile에서 랜덤하게 우측 혹은 아래로 길을 뚫는 작업
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			// Wall Tile이면 패스
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			// 도착지점(y - 2, x - 2)에서 오른쪽, 아래벽이 뚫리지 않도록 함.
			if (y == _size - 2 && x == _size - 2)
				continue;

			// 미로의 맨 아래 외각 벽이 뚫리지 않도록
			if (y == _size - 2)
			{
				_tile[y][x + 1] = TileType::EMPTY;
				continue;
			}

			// 미로의 맨 왼쪽 외각 벽이 뚫리지 않도록
			if (x == _size - 2)
			{
				_tile[y + 1][x] = TileType::EMPTY;
				continue;
			}

			// 랜덤하게 벽을 뚫음
			const int32 randValue = rand() % 2;
			if (randValue == 0)
			{
				_tile[y][x + 1] = TileType::EMPTY;
			}
			else
			{
				_tile[y + 1][x] = TileType::EMPTY;
			}
		}
	}
}

ConsoleColor Board::SetTileColor(Pos pos)
{
	// Player의 위치를 노랑색으로 표시
	if (_player && _player->GetPos() == pos)
		return ConsoleColor::YELLOW;

	// 출구를 파랑색로 표시
	if (GetExitPos() == pos)
		return ConsoleColor::BLUE;

	TileType tileType = GetTileType(pos); 

	switch (tileType)
	{
	case TileType::WALL:
		return ConsoleColor::RED;
	case TileType::EMPTY:
		return ConsoleColor::GREEN;
	}

	return ConsoleColor::WHITE;
}

TileType Board::GetTileType(Pos pos)
{
	// 예외 범위 오류 처리
	if (pos.x < 0 || pos.x >= _size)
		return TileType::NONE;
	if (pos.y < 0 || pos.y >= _size)
		return TileType::NONE;

	return _tile[pos.y][pos.x];
}