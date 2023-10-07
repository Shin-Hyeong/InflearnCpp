#pragma once

// 방식 1) 클래스 밖에서 전방 선언
class Monster;

class Player
{
public:
    void KillMonster();

    void KillMonster1()
    {
        // 헤더파일에는 설계도를 알려줄 #include Monster가 없음
        // 헤더에서 다른 헤더파일을 include를 할때 순환헤더를 고려해야함
        // _target->_hp = 0;
    }

public:
    int _hp;
    int _attack;

    // 방식 2) 클래스내 전방 선언
    class Monster* _target;

    // Player를 호출하면 Player를 계속 만들어짐.
    // Player _player;
    
    // Player를 호출하면 Player를 담을 수 있는 포인터 변수를 생성함
    Player* _player;

};