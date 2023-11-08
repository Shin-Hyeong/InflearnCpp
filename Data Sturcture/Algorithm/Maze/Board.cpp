#include "pch.h"
#include "Board.h"
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
    ConsoleHelper::SetCursorPostion(0, 0);
    ConsoleHelper::ShowConsoleCursor(false);

    for (int32 y = 0; y < 25; y++)
    {
        for (int32 x = 0; x < 25; x++)
        {
            ConsoleColor color = GetTileColor(Pos{ y,x });
            ConsoleHelper::SetCursorColor(color);

            cout << TILE << " ";
        }
        cout << endl;
    }
}

// Binary Tree 미로 생성 알고리즘
// - Mazes For Programmers
void Board::GenerateMap()
{
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {   
            // WALL 생성
            if (x % 2 == 0 || y % 2 == 0)
                _tile[y][x] = TileType::WALL;
            // 이동이 가능한 빈칸
            else
                _tile[y][x] = TileType::EMPTY;
        }
    }

    // 랜덤으로 EMPTY의 우측 혹은 아래로 길을 뚫는 작업
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {   
            // WALL인 구간은 넘어감.
            if (x % 2 == 0 || y % 2 == 0)
                continue;

            // 출구 칸은 벽이 안뚫리도록 함
            if (y == _size - 2 && x == _size - 2)
                continue;
            
            // 맨 아래 벽을 뚫리지 않도록 함.
            if (y == _size - 2)
            {
                _tile[y][x + 1] = TileType::EMPTY;
                continue;
            }

            // 맨 오른쪽 벽이 뚫리지 않도록 함
            if (x == _size - 2)
            {
                _tile[y + 1][x] = TileType::EMPTY;
                continue;
            }
            
            // EMPTY에서 랜덤하게 아래나 오른쪽 칸을 EMPTY로 변경
            const int32 randValue = ::rand() % 2;
            if (randValue == 0)
                _tile[y][x + 1] = TileType::EMPTY;
            else
                _tile[y + 1][x] = TileType::EMPTY;
        }
    }
}

TileType Board::GetTileType(Pos pos)
{   
    // _size를 넘어간 Tile은 NONE으로 지정
    if (pos.x < 0 || pos.x >= _size)
        return TileType::NONE;
    if (pos.y < 0 || pos.y >= _size)
        return TileType::NONE;
    
    // _size 범위 내에 있으면 해당 tile의 TileType를 반환
    return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
    // Player 위치 색상은 YELLOW
    if (_player != nullptr && _player->GetPos() == pos)
        return ConsoleColor::YELLOW;


    // 출구를 파랑색으로 함.
    if (GetExitPos() == pos)
        return ConsoleColor::BLUE;


    TileType tileType = GetTileType(pos);

    switch (tileType)
    {
        // EMPTY 이면 GREEN
    case TileType::EMPTY:
        return ConsoleColor::GREEN;
        // WALL 이면 RED
    case TileType::WALL:
        return ConsoleColor::RED;
    }

    return ConsoleColor::WHITE;
}
