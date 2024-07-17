#pragma once

class Board;

class Player
{
	enum
	{
		MOVE_TICK = 100
	};
public:
	// 초기화
	void Init(Board* board);
	// 프레임마다 업데이트
	void Tick(uint64 DeltaTime);

	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }

	bool CanGo(Pos pos);

private:
	void RightHand();
	void BFS();

private:
	// Player 위치
	Pos _pos{};
	// Player 이동 방향(현재 바라보고 있는 방향)
	int32 _dir = DIR_UP;
	// Player가 위치할 맵
	Board* _board = nullptr;

	// 이동해야하는 길 저장
	vector<Pos> _path;
	// 저장된 경로중 몇번째 Index 위치를 이동중인지
	uint32 _pathIndex = 0;
	//
	uint64 _sumTick = 0;
};

