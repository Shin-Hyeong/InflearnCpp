#include <iostream>
#include "Player.h"

using namespace std;

// 전방 선언

int main ()
{
    Player p1;

    Player* p2 = new Player();

    // Player [_hp][_attack][Monster*][Player*]
    // p1의 Player* 포인터 변수에 p2의 주소를 넣음.
    p1._player = p2;

    return 0;
}