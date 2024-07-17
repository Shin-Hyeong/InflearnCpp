#include "pch.h"
#include "Board.h"
#include "Player.h"

#include <stack>

void Player::Init(Board* board)
{
	// Player의 시작 위치를 미로의 출발점으로 지정
	_pos = board->GetEnterPos();
	_board = board;

	// RightHand();
	BFS();
}

void Player::Tick(uint64 DeltaTime)
{
	if (_pathIndex >= _path.size())
		return;

	_sumTick += DeltaTime;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::RightHand()
{
	// _pos = 실제 Player 위치
	// pos = Player가 이동하기 위한 경로를 시뮬레이션 하기 위한 가상 위치
	Pos pos = _pos;

	// 시작 위치
	_path.clear();
	_path.push_back(pos);

	// 목적지 위치
	Pos dest = _board->GetExitPos();

	// 앞으로 이동 좌표
	Pos front[4] =
	{
		Pos { -1, 0 },	// UP
		Pos { 0, -1 },	// LEFT
		Pos { 1, 0 },	// DOWN
		Pos { 0, 1 },	// RIGHT
	};
	int i = 0;
	// 목적지 도착하기 전까지 계속 실행
	while (pos != dest)
	{
		// 현재 바라보는 방향에서 오른쪽 방향 구하기
		// 0 - 1은 음수 이기때문에 DIR_COUNT를 더하고 나누어서 음수가 나오지 않도록 함
		int32 turnRightDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;

		// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인
		if (CanGo(pos + front[turnRightDir]))
		{
			// 오른쪽 방향(시계 방향)으로 90도 회전
			_dir = turnRightDir;

			// 앞으로 한칸 이동
			pos += front[_dir];

			// 이동하는 경로 저장
			_path.push_back(pos);
		}
		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인
		else if (CanGo(pos + front[_dir]))
		{
			// 앞으로 한칸 이동
			pos += front[_dir];

			// 이동하는 경로 저장
			_path.push_back(pos);
		}
		// 3. 
		else
		{
			// 왼쪽 방향(반시계 방향)으로 90도 회전
			// UP(0) -> LEFT(1) -> DOWN(2) -> RIGHT(3) -> UP(0)
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}

	/**
		Stack
	*/

	stack<Pos> s;

	// stack에 _path에 저장된 경로를 저장함.
	for (int i = 0; i < _path.size() - 1; i++)
	{
		// stack의 맨 위(가장 최근 위치)와 다음으로 갈 위치가 같으면 pop
		//  = 되돌아가는 길이면 pop
		if (s.empty() == false && s.top() == _path[i + 1])
		{
			s.pop();
		}
		else
		{
			s.push(_path[i]);
		}
	}

	// _path의 마지막 좌표(목적지)를 stack에 추가
	if (_path.empty() == false)
		s.push(_path.back());

	// stack에 저장된 경로를 임시 vector로 옮김
	// 목적지 -> 출발지로 저장됨
	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}

	// 역순으로 돌려서 출발지 -> 목적지로 변경
	reverse(path.begin(), path.end());

	// 임시 vector에 저장된 경로를 옮김.
	_path = path;
}

void Player::BFS()
{
	// _pos = 실제 Player 위치
	// pos = Player가 이동하기 위한 경로를 시뮬레이션 하기 위한 가상 위치
	Pos pos = _pos; 

	// 목적지 위치
	Pos dest = _board->GetExitPos();

	// 앞으로 이동 좌표
	Pos front[4] = 
	{
		Pos { -1, 0 },	// UP 
		Pos { 0, -1 },	// LEFT 
		Pos { 1, 0 },	// DOWN 
		Pos { 0, 1 },	// RIGHT 
	};

	// 발견했는지 확인하는 vector
	const int32 size = _board->GetSize(); 
	vector<vector<bool>> discovered(size, vector<bool>(size, false));

	// 발견한 정점의 Parent 정점
	// parent[A] = B; -> A는 B로 인해 발견함
	map<Pos, Pos> parent;

	// 발견한 정점(방문은 안함)를 저장해둠
	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;
	// 시작점은 자기자신이 부모임
	parent[pos] = pos;

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		// 발견해둔 정점을 이제 방문함

		// 목적지에 도달하면 멈춤
		if (pos == dest)
			break;

		for (int32 dir = 0; dir < 4; dir++)
		{
			Pos nextPos = pos + front[dir];

			// 상, 좌, 하, 우 순으로 앞으로 나갈 수 있는지 확인
			if (CanGo(nextPos) == false)
				continue;

			// 이미 발견한 정점인지 확인
			if (discovered[nextPos.y][nextPos.x] == true)
				continue;

			// 새로운 정점 발견
			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			// 새로운 정점의 Parent
			parent[nextPos] = pos;
		}
	}



	// BFS를 통해서 얻은 정보를 이동 경로(_path)에 저장함.
	// 목적지 -> 출발지로 반대로 이동하면서 해당 정점의 Parent정점을 저장하면서 최단거리를 구함.
	_path.clear();
	
	pos = dest;

	vector<Pos> path;
	while (true)
	{
		// 정점 저장
		path.push_back(pos);

		// 시작점은 자신이 곧 부모임.
		if (pos == parent[pos])
			break;

		// 정점의 Parent를 가져옴.
		pos = parent[pos];
	}

	// 목적지 ->  출발지로 되어있기 때문에 뒤집어줌.
	reverse(path.begin(), path.end());

	_path = path;

}
