#include <iostream>
using namespace std;
#include "Header.h"
#include <ctime>

// [Bug Report #8]
// 펫을 궁수의 생성자에서 만드는 것이
// 깔끔하지 않다는 사장님의 지적에 따라
// 일단 밖으로 빼서 펫을 생성하게 수정했습니다.

// 그런데 막상 밖으로 빼니 또 크래시가 납니다.
// 가만히 있으면 중간은 간다던데...
// 뭐가 문제일까요?

// ! [Debug Result]
// 지역변수(스택)인 pet를 다른 class의 소멸자로 소멸시킬려고 함.
// 동적할당을 하여서 생명주기 권한을 넘기면 됨.

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	while (true)
	{
		// 나중엔 궁수, 법사 등 추가 예정
		Player* p = nullptr;

		switch (rand() % 3)
		{
			case 0:
			{
				p = new Knight();
				p->_hp = 100;
				p->_attack = 100;
				break;
			}	
			case 1:
			{
				// 여기서 같이 만들어준다
				// 이런 저런 펫 정보 추가될 예정
				// Pet pet;
				Pet* pet = new Pet();

				// Archer를 만들 때 pet 정보도 넘겨준다
				// p = new Archer(&pet);
				p = new Archer(pet);
				p->_hp = 100;
				p->_attack = 100;

				break;
			}		
			case 2:
			{
				p = new Mage();
				p->_hp = 100;
				p->_attack = 100;
				break;
			}			
		}

		delete p;
	}

}
