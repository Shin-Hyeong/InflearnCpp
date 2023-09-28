#include <iostream>
using namespace std;


// 멤버 변수의 초기화
// 지역 변수를 초기화하지 않으면 쓰레기값(엉뚱한 값)을 가지고 있음.

// ! 변수 초기화해야 하는 이유
// - 버그 예방에 중요
// - 포인터 등 주소값이 연루되어 있을 경우

// ! 초기화 방법
// - 생성자 내에서 초기화
// - 초기화 리스트
// - C++11(모던 C++) 문법
// -- 게임업계에선 모던 C++를 사용하지 않는 팀도 존재한다.

// 생성자내에서 초기화 VS 초기화 리스트
// - 일반 변수는 별 차이 없음
// - 멤버 타입이 class인 경우 차이가 난다.
// -- class의 타입인 경우 생성자에서 초기화하면 무조건 기본 생성자를 호출한다.
// -- 생성자 내에서 다른 생성자를 호출 하고 싶으면 선처리 영역에서 기본 생성자를 호출한 뒤에 다른 생성자를 호출하는 2중 호출이 일어남.
// -- 초기화 리스트에서 초기화하면 선처리 영역에서 사용자가 원하는 생성자만 호출하여 사용한다.
// - 정의함과 동시에 초기화가 필요한 경우 (참조타입(&), const 타입)

class Inventory
{
public:
    Inventory() { cout << "Inventory()" << endl; }
    Inventory(int size) {
        _size = size;
        cout << "Inventory(int size)" << endl;
        cout << "size : " << _size << endl;
    }

    ~Inventory() {cout << "~Inventory()" << endl; }
public:
    int _size = 10;
};

class Player
{
public:
    Player() { }
    Player(int id) { }
};

// ! Is-A(Knight Is-A Player?) : 기사는 플레이어다 -> OK -> 상속관계
// ! Is-A(Knight Is-A Inventory?) : 기사는 인벤토리이다 -> NO

// ! Has_A(Knight Has-A Inventory?) : 기사는 인벤토리를 가지고 있다 -> OK -> 포함관계 

class Knight : public Player
{
public:
    // 초기화 리스트
    // - 상속 관계에서 원하는 부모 생성자 호출할 때 필요하다
    // - 포함관계의 class의 원하는 생성자를 호출할 때 사용한다.
    // - 참조타입(&)과 Const타입은 초기화 리스트에서 정의하여서 선처리영역에서 초기화 할수 있도록한다.
    // -- 생성자에서 초기화하게 되면 생성자라는 함수에서 값을 변경하는 것과 같기 떄문
    Knight() : Player(1), _hp(100), _inventory(20), _hpRef(_hp), _hpConst(100)
    {   
        /*
        선처리 영역
        Player(int id)의 생성자 호출
        Inventory의 기본 생성자 호출

        */
        // 생성자 내에서 초기화
        _hp = 100;
        // Inventory(int size) 생성자를 호출함.
        // 선처리 영역에서 Inventory이 기본 생성자를 호출하고 Inventory(int size) 생성자를 또 호출하는 형태
        // Inventory(int size) 생성자가 호출되면서 기본 생성자는 의미가 없기 떄문에 소멸자를 호출함.
        // inventory = Inventory(20);
    }

public:
    // C++11(모던 C++) 문법
    int _hp = 100;
    // 인벤토리가 기사에 포함관계
    Inventory _inventory;

    // - 정의함과 동시에 초기화가 필요한 경우 (참조타입(&), const 타입)
    // 누군가를 무조건 가르키고 있어야하는 참조타입
    // - C++11 방식 : int& _hpRef = _hp;
    int& _hpRef;

    // 무언가를 고정값으로 가지고 있어야하는 상수타입
    // - C++11 방식 : const int _hpConst = 100;
    const int _hpConst;
};


int main()
{
    Knight k;
    cout << k._hp << endl;

    return 0;
}