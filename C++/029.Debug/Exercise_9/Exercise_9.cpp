#include <iostream>
using namespace std;
#include "Header.h"
#include <ctime>

// [Bug Report #9]
// 궁수가 죽으면 펫도 같이 죽는 사양이 추가되었습니다.
// 그런데 왜 프로그램도 같이 죽는걸까요?
// 이유를 찾아서 고쳐주세요!

// ! [Bug Result #9]
// Archer가 사망할 때 Pet을 메모리 해제해줌.
// Archer의 소멸자를 호출할 때 Pet을 메모리를 해제해줌.
// Archer가 사망할 때 Pet의 메모리를 해제하고 _pet가 가지고 있는 주소를 없애줘야함.

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
	knight->_attack = 100;
	
	int damage = knight->GetAttackDamage();
	archer->AddHp(-damage);

	delete archer;
	delete knight;
}
