#include <iostream>
using namespace std;
#include "Header.h"
#include <ctime>

// [Bug Report #10]
// 궁수라며면 자고로 화살을 쏴야겠죠.
// Arrow는 자신을 목표 대상물을 target으로 관리하고
// Arrow를 만들 때 설정한 데미지 만큼 target의 체력을 깎습니다.
// 테스트를 위해 화살 10개를 생성해서 기사를 피격했는데...
// C++이 늘 그렇지만 되는 일이 없고 또 크래시가 납니다.
// 뭐가 문제일까요?

// ! [Bug Result #10]
// 화살은 무조건 10개를 발사함. 하지만 Knight는 화살 8발이면 사망함
// Knight는 사망하면 메모리 해제됨 -> 화살 2발은 _target이 없는 상태로 발사함.
// Knight가 사망해도 메모리 해제하지 않도록 하거나 사망을 확인하는 코드를 추가함.

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	Archer* archer = new Archer(new Pet());
	archer->_hp = 100;
	archer->_maxHp = 100;
	archer->_attack = 20;

	Knight* knight = new Knight();	
	knight->_hp = 150;
	knight->_maxHp = 150;
	knight->_attack = 10;
	
	Arrow* arrows[10] = {};
	for (int i = 0; i < 10; i++)
	{
		// 기사를 타겟으로, 궁수의 공격력을 지닌 상태
		Arrow* arrow = new Arrow(knight, archer->_attack);
		arrows[i] = arrow;
	}

	for (int i = 0; i < 10; i++)
	{
		arrows[i]->AttackTarget();

		// 기사가 죽었으면 소멸시켜준다
		// 화살 10개를 발사하고 있는데 _target인 Knight가 메모리 해제로 사라짐.
		// if (knight != nullptr)
		// {
		// 	if (knight->IsDead())
		// 	{
		// 		delete knight;
		// 		knight = nullptr;
		// 	}
		// }	

		delete arrows[i];
		arrows[i] = nullptr;
	}
	delete knight;
	knight = nullptr;
}
