#pragma once

class Knight
{
public:
	Knight();
	Knight(int hp);
	~Knight();

	void PrintInfo();

	void AddHp(int value);
	bool IsDead();

public:
	//int _hp;
	__int64 _hp;
	int _attack;
};

