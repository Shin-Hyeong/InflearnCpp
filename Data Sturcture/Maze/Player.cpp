#include "pch.h"
#include "Player.h"
#include "Board.h"

#include <stack>

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	/* TODO 탈출 경로 미리 계산 */
	// 탈출 경로를 시뮬레이션하기 위한 임시 위치 표시
	Pos pos = _pos;

	// 시작 경로 저장.
	_path.clear();
	_path.push_back(pos);

	// 도착지점
	Pos dest = board->GetExitPos();

	Pos front[4] =
	{
		// UP
		Pos {-1, 0},
		// LEFT
		Pos {0, -1},
		// DOWN
		Pos {1, 0},
		// RIGHT
		Pos {0, 1},
	};

	// 목적지까지 도착할때까지 실행
	while (pos != dest)
	{
		// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인
		// (_dir - 1) : 오른쪽 방향
		// (_dir - 1) + DIR_COUNT : 0에서 -1를 하면 음수가 나오기 때문에 양수가 나오도록 하기 위해
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;

		// Cango(현재 위치 + 바라보는 방향의 앞칸)
		if (Cango(pos + front[newDir]))
		{
			// 오른쪽 방향으로 90도 회전.
			_dir = newDir;

			// 앞으로 한 칸 이동
			pos += front[_dir];
			// 경로 저장.
			_path.push_back(pos);
		}
		// 2. 현재 바라보는 방향으로 기준으로 전진 할 수 있는지 확인
		else if (Cango(pos + front[_dir]))
		{
			// 앞으로 한 칸 이동
			pos += front[_dir];
			// 경로 저장.
			_path.push_back(pos);
		}
		else
		{
			// 왼쪽 방향으로 90도 회전.
			_dir = (_dir + 1) % DIR_COUNT;
			/*
			switch (_dir)
			{
			case DIR_UP:
				_dir = DIR_LEFT;
				break;
			case DIR_LEFT:
				_dir = DIR_DOWN;
				break;
			case DIR_DOWN:
				_dir = DIR_RIGHT;
				break;
			case DIR_RIGHT:
				_dir = DIR_UP;
				break;
			}
			*/
		}
	}
	
	stack<Pos> s;
	
	for (int i = 0; i < _path.size() - 1; i++)
	{
		// stack이 비어있지 않고, 최상위에 있는 위치랑 앞으로 가야할 위치가 동일한지 확인
		// 왔던 길을 되돌아가는 중.
		if (s.empty() == false && s.top() == _path[i + 1])
			s.pop();
		// 처음 가는 길
		else
			s.push(_path[i]);
	}
	
	// 목적지 도착
	if (_path.empty() == false)
		s.push(_path.back());

	// stack 특성상 순서가 뒤집혀서 나오기 때문에 임시 vector에 저장한다.
	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}

	// stack으로 뒤집힌 순서 다시 뒤집기
	std::reverse(path.begin(), path.end());
	// _path로 주소 변경.
	_path = path;
	
}

void Player::Update(uint64 deltaTick)
{
	// 저장된 경로를 다 지나가면 return
	if (_pathIndex >= _path.size())
		return;

	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::Cango(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;

}
