#include <iostream>
using namespace std;

// 얕은 복사 vs 깊은 복사

class Pet
{
public:
    Pet()
    {
        cout << "Pet()" << endl;
    }
    ~Pet()
    {
        cout << "~Pet()" << endl;
    }
    Pet(const Pet& pet)
    {
        cout << "Pet(const Pet& pet)" << endl;
    }
};

class Knight
{
public:
    Knight()
    {
        _pet = new Pet();
    }
    Knight(const Knight& knight)
    {
        _hp = knight._hp;
        // Pet의 복사 생성자가 참조 타입이기 떄문에 주소값이 아닌 값을 넘겨줘야함
        // 깊은 복사를 이루게 하는 코드
        _pet = new Pet(*(knight._pet));
    }
    Knight& operator=(const Knight& knight)
    {
        _hp = knight._hp;
        // Pet의 복사 생성자가 참조 타입이기 떄문에 주소값이 아닌 값을 넘겨줘야함
        // 깊은 복사를 이루게 하는 코드
        _pet = new Pet(*(knight._pet));
        return *this;
    }
    ~Knight()
    {
        delete _pet;
    }


public:
    int _hp = 100;
    // 포인터가 아닌 Pet 자체를 들고 있으면
    // Knight가 생성될 때 같이 생성되고 소멸할때 같이 소멸한다.
    // 생명관리가 어려워짐 -> Knight는 죽이고 Pet는 따로 살리고 싶을 때
    // Pet이 막대한 데이터를 가지고 있으면 Knight가 그 데이터를 들고 다님.
    // Pet _pet;

    // class 내에서 다른 class를 가지고 있을 떄에는 그 자체보다 포인터로 가지고 있는 것이 좋다.
    Pet* _pet;
};

int main()
{
    // Stack
    // 기본 생성자 호출
    Knight k1;
    k1._hp = 200;

    // 같은 기사를 복사하기
    // 1) 복사 생성자 호출하기(기본 생성자 호출 X)
    Knight k2 = k1;
    Knight k3(k1);

    // 2) 기본 생성자 호출 후 복사하기
    Knight k4;  // 기본 생성자
    k4 = k1;    // 복사 대입 연산자

    // ! 얇은 복사(Shallow Copy)
    // [복사 생성자] + [복사 대입 연산자]
    // 둘 다 안 만들어주면 컴파일러가 '암시적으로' 만들어준다.
    // 컴파일러가 만든 복사는 값을 그대로 옮기는 성향을 가짐. -> 포인터와 참조값을 별도로 생성하지 않고 복사함.
    // 포인터는 주소값을 가짐 -> 주소값을 똑같이 복사 -> 동일한 객체를 가리키는 상태가 됨.
    // k1에게 주어진 pet이 k2, k3도 똑같이 소유하게 됨.

    // 멤버 데이터를 비트열 단위로 '똑같이' 복사 (메모리 영역 값을 그대로 복사)
    // Stack : k1[_hp(200), _pet(0xCC03)] -> Heap 0xCC03 Pet[ ]
    // Stack : k2[_hp(200), _pet(0xCC03)] -> Heap 0xCC03 Pet[ ]

    // ! Knight에서 Pet의 생명주기를 건들면 복사된 Knight에 영향을 줌.

    // ! 깊은 복사(Deep Copy)
    // 멤버 데이터가 참주(주소) 값이라면, 데이터를 새로 만들어준다. (원본 객체가 참조하는 대상까지 새로 만들어서 복사)
    // 포인터는 주소값을 가짐 -> 새로운 객체를 생성 -> 서로 다른 객체를 가리키는 상태가 됨.
    // Stack : k1[_hp(200), _pet(0xCC03)] -> Heap 0xCC03 Pet[ ]
    // Stack : k2[_hp(200), _pet(0xCC2D)] -> Heap 0xCC2D Pet[ ]

    // 복사 연산자와 복사 생성자를 명시적으로 만들어줘야 함.

    return 0;
}