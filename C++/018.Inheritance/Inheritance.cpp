#include <iostream>
using namespace std;

// 객체 지향의 3대 속성
// - 상속성
// - 은닉성
// - 다형성

// 상속(Inheritance) : 부모가 자식에게 유산을 물려주는 것
// 중복되는 함수, 변수를 여러번 선언하는 것 보다 하나의 class 선언하고 공통으로 사용할 내용을 넣으면 된다.

// 생성자(N개) / 소멸자(1개)

class Player
{
public:
    Player()
    {
        cout << "Player() 기본 생성자 호출" << endl;
        _hp = 0;
        _attack = 0;
        _defense = 0;
    }
    Player(int hp)
    {
        cout << "Player(int hp) 기본 생성자 호출" << endl;
        _hp = hp;
    }

    ~Player()
    {
        cout << "~Player() 소멸자 호출" << endl;
    }
    void Move() { cout << "Player_Move 호출" << endl; }
    void Attack() { cout << "Player_Attack 호출" << endl; }
    void Die() { cout << "Player_Die 호출" << endl; }

public:
    int _hp;
    int _attack;
    int _defense;
};

// Archer는 Player를 상속 받음.
// 따로 선언을 하지 않아도 Player의 기능을 사용 할 수 있음.
// 상속받은 값뿐만 아니라 Archer의 고유 기능, 변수도 생성 가능하다.
// 메모리상에선 Player의 변수가 정의된 후에 Archer가 확장팩 개념으로 이어서 붙어 정의(저장)된다.
// Player에게 상속받은 Move를 자식이 재정의해서 사용할 수 있다.
// Archer가 Player의 내용을 사용하기 때문에 Archer를 생성하면 Player부터 생성자를 호출하고 Archer를 호출한다.
// Player() 기본 생성자 호출
// Archer() 기본 생성자 호출
// ~Archer() 소멸자 호출
// ~Player() 소멸자 호출

class Archer : public Player
{
public:
    /*
        선(먼저)처리 영역
        - 여기서 Player() 생성자를 호출
    */
    Archer()
    {
        cout << "Archer() 기본 생성자 호출" << endl;
        _Arrow = 20;
    }

    // Archer(int Arrow) 뒤에 : 원하는 생성자 유형을 넣으면 된다.
    Archer(int Arrow) : Player(100) // Player(int hp) 생성자를 호출함.
    {
        cout << "Archer(int Arrow) 생성자 호출" << endl;
        _Arrow = Arrow;
    }

    ~Archer()
    {
        cout << "~Archer() 소멸자 호출" << endl;
    }
    /*
        후(나중에)처리 영역
        - 여기서 ~Player() 소멸자를 호출
    */

    // 함수를 재정의함 -> 부모님의 상속을 거부하고 새로운 내용을 만듬.
    void Move() { cout << "Archer_Move 호출" << endl; }

public:
    int _Arrow;
};

// Knight와 Mage 둘다 중복된 내용을 소지함.
class Knight
{
public: 
    void Move() { }
    void Attack() { }
    void Die() { }

public:
    int _hp;
    int _attack;
    int _defense;
};

class Mage
{
public:
    void Move() {}
    void Attack() {}
    void Die() {}

public:
    int _hp;
    int _attack;
    int _defense;
};

int main ()
{
    Archer A;
    Archer B(20);

    // 재정의한 함수 사용
    A.Move();
    // 재정의했어도 부모의 함수를 사용
    A.Player::Move();

    A.Attack();
    A.Die();

    return 0;
}