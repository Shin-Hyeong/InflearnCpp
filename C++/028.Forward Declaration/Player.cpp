#include "Player.h"
#include "Monster.h"

void Player::KillMonster()
{   
    // _target에 Monster의 설계도 내용이 없음.
    // #include Monster를 해줘야 Monster 설계도(class)를 통해
    // _hp의 위치를 확인할 수 있음.
    _target->_hp = 0;
}