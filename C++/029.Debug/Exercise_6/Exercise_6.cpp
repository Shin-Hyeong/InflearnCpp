#include <iostream>
using namespace std;
#include "Header.h"

// [Bug Report #6]
// 반격 시스템이 도입되어,
// 기사는 자신을 공격한 대상을 똑같이 공격합니다.
// 기사 2을 생성해서 위 사양을 테스트하는데...
// 바로 크래시가 나고 있습니다.
// 또 뭐가 문제인지 원인을 찾아주세요!

// ! [Bug Result #6]
// 반격하는 대상을 찾는 과정에서 OnDamaged에서 자기 자신을 부르는 무한 재귀함수가 발생함.
// 재귀함수에서 탈출할 수 있는 코드를 추가하거나
// 재귀함수를 제거하고 반격하는 코드를 추가한다.

int main()
{
	Knight* k1 = new Knight();
	k1->_hp = 100;
	k1->_maxHp = 100;
	k1->_attack = 100;

	Knight* k2 = new Knight();
	k2->_hp = 100;
	k2->_maxHp = 100;
	k2->_attack = 100;

	// k2가 k1를 공격함
	k1->OnDamaged(k2);

	delete k1;
	delete k2;
}
