#pragma once

class Board;

class Player
{
	enum
	{	
		// 몇 ms마다 이동할지 지정.
		MOVE_TICK = 100
	};
public:
	void Init(Board* board);

	// 프레임마다 실행
	void Update(uint64 deltaTick);

	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }
	
	// pos가 EMPTY이면 이동 가능.
	bool Cango(Pos pos);

private:

	// Player의 현재 위치
	Pos _pos = {};
	int32 _dir = DIR_UP;
	// 내가 있는 board의 위치
	Board* _board = nullptr;

	vector<Pos> _path;
	uint32 _pathIndex = 0;
	uint64 _sumTick = 0;
};

