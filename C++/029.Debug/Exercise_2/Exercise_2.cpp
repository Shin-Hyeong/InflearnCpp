#include <iostream>
using namespace std;
#include "Header.h"

// [Bug Report #2]
// Bug Report #1이 잘 해결 되었는지 확인하기 위해
// 기사 10명 생성해서 정보를 출력하고자 합니다.
// 그런데 정보를 출력하다 프로그램이 뻗는 문제가 발생하고 있습니다.
// 크래시 원인을 분석하고 알맞게 고쳐주세요!

// ! [Bug Result #2]
// 기사 10명의 정보를 출력하는 과정에서 할당된 기사보다
// 더 많은 정보를 조회할려고 함.

const int KNIGHT_COUNT = 10;

int main()
{
	Knight* knights[KNIGHT_COUNT];

	for (int i = 0; i < KNIGHT_COUNT; i++)
	{
		knights[i] = new Knight();
	}

	//for (int i = 0; i <= KNIGHT_COUNT; i++)
	for (int i = 0; i < KNIGHT_COUNT; i++)
	{
		knights[i]->PrintInfo();
		delete knights[i];
	}

	
}
