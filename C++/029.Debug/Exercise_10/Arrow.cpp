#include "Arrow.h"
#include "Player.h"
#include <iostream>
using namespace std;

Arrow::Arrow(Player* target, int damage) 
	: _target(target), _damage(damage)
{

}

Arrow::~Arrow()
{

}

void Arrow::AttackTarget()
{
	cout << "화살이 적을 피격합니다" << endl;

	// 공격 대상이 있다면
	if (_target != nullptr)
	{
		// 데미지를 입힌다.
		_target->AddHp(-_damage);
		// PrintInfo는 가상함수로 원본이 무엇인지 확인해야함
		// Knight가 사망하면 _target이 뭔지 알 수 없음.
		_target->PrintInfo();
	}
}