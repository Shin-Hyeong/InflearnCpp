#pragma once
// #include "Player.h"
// 전방 선언 : Player가 등장할 것이라 예고함. 구현은 따로 할 수 있게해줌.
// ! 헤더 파일에서 선언을 못찾으면 우선적으론 전방 선언
// ! 상속 관계이면 #include "헤더파일"
// ! .cpp파일에서는 그냥 #include를 하면 됨/
class Player;

// is - a(상속) : Game is Player? -> No
// has - a(포함) : Game has Player? -> Ok

class Game
{
public:
    // 선언만 하고 구현은 .cpp 파일에서 함.
    Game();
    ~Game();

    // 게임 처음 시작할 때 초기화 시키는 함수 (BeginPlay, Start)
    void Init();

    // 매 프레임마다 실행시키는 함수 (Tick, Update)
    void Update();

    // 플레이어 생성하는 함수
    void CreatePlayer();

private:
    // 객체로 생성
    // class Game를 설계하기 위해서 반드시 class Player가 필요해짐.
    // 의존성이 높아짐
    // Player가 나중에 Knight, Archer, Mage로 변했을 때 쉽게 넣어 줄 수 없음.
    // Player의 용량이 크질수록 Game에도 그대로 용량에 영향을 줌
    // Player _player;

    // 포인터 변수로 생성
    // 운영체제의 따라 다름(4 or 8 byte)
    // Player의 용량이 커져도 Game에 영향이 없음.
    // class Player가 완성이 되지 않아도 class Game을 완성시킬 수 있음.
    Player* _player;

public:


};