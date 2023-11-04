#pragma once

class Board;

class Player
{
public:
	void Init(Board* board);

	// 프레임마다 실행
	void Update(uint64 deltaTick);

	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }
	

private:
	Pos _pos = {};
	int32 _dir = DIR_UP;
	// 내가 있는 board의 위치
	Board* _board = nullptr;
};

