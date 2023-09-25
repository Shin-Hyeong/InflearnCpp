#include <iostream>
using namespace std;

// 데이터 + 가공(로직, 동작)
// 객체 : 플레이어, 몬스터, GameRoom

// Knight를 설계
// - 속성 (데이터) : hp, attack, position(x, y)
// - 기능 (동작) : Move, Attack, Die.

// 설계도의 이름은 class로 시작한다.
// 설계도는 메모리에 할당되지 않고 따로 선언을 하는 과정에서 메모리에 할당된다.
// C++에서 class와 struct는 종이 한장 차이로 유사하다.
class Knight
{
public:
    // 멤버 변수
    // 멤버 변수와 일반 변수를 차이를 두기 위해 멤버변수에 선언에서 차이른 둔다
    // m_hp, mHp, _hp -> 팀마다 선언방법이 다름
    int _hp;
    int _attack;
    int _posY;
    int _posX;

public:
    // 멤버 함수
    // 멤버 함수는 같은 class내에 있는 멤버 변수를 매개변수 없이 접근할 수 있다.
    void Move(int x, int y);
    void Attack();
    // class 안에서도 함수를 정의할수 있다.
    void Die()
    {   
        // Die함수에서 멤버 변수인 hp를 매개변수 없이 접근함.
        _hp = 0;
        cout << "Die" << endl;
    }
};

// class 밖에서 함수를 정의할려면 함수명 앞에 어느 class에 속해있는지 명시해야한다.
// 반환값 클래스명::함수명(매개변수)
void Knight::Move(int y, int x)
{
    _posY = y;
    _posX = x;
    cout << "Move" << endl;
}

// Knight의 멤버 함수가 아닌 독립적인 함수.
// 특정 오브젝트를 이동시키기 위해서 오브젝트의 주소를 받아와야함.
void Move(Knight* knight, int y, int x)
{
    knight->_posY = y;
    knight->_posX = x;
}

void Knight::Attack()
{
    cout << "Attack : " << _attack << endl;
}

int main()
{   
    // class를 사용하고 싶으면 struct를 사용하는 것처럼 선언하면 된다.
    // Knight 설계도를 가지고 K1변수를 만들겠다. -> Knight 설계도는 메모리에 할당되지 않지만 K1은 메모리에 할당됨.
    // Instantiate 객체를 만든다.
    Knight K1;
    K1._hp = 100;
    K1._attack = 10;
    K1._posY = 0;
    K1._posX = 0;

    // 같은 Knight 설계도로 만들었다고 해도 K1과 독립적인 존재이다.
    Knight K2;
    K2._hp = 80;
    K2._attack = 5;
    K2._posY = 1;
    K2._posX = 1;
    
    // 멤버 함수도 사용 가능.
    // K1의 주소를 가지고 Knight::Move를 호출함.
    // 객체(K1) 기준으로 이동하는 느낌.
    K1.Move(2, 2);
    K1.Attack();
    K1.Die();

    // 멤버 함수가 아닌 독립적인 일반 함수
    // K1의 주소를 Move 함수를 호출함.
    // 함수를 기준으로 오브젝트가 이동하는 느낌.
    Move(&K1, 3, 3);

    // Knight::Move와 Move는 메모리상에선 큰 차이가 없지만
    // class내에서 적용할 수 있는 문법이 많기 때문에 class내에서 어떻게 가공하느냐에 따라 달라진다.

    return 0;
}