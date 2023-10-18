#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <memory>
using namespace std;

// 오른 값(rvalue) 참조(Modern C++의 꽃)와 std::move
// Modern C++ (C++11 이후 문법)

// ! 값을 복사하는 기능이 아닌 값을 이동 시키는 기능
// 값을 가지고 있던 객체는 회손되어 소멸

// 왼값(lvalue) vs 오른값(rvalue)
// - lvalue : 단일식을 넘어서 계속 지속 되는 개체
// - rvalue : lvalue가 아닌 나머지 (임시 값, 열거형, 람다, i++ 등)

class Pet
{

};

class Knight
{
public:
    Knight ()
    {
        cout << "Knight()" << endl;
    }

    Knight(const Knight& knight)
    {
        cout << "const knight()" << endl;
    }

    // ! 이동 생성자
    Knight(Knight&& knight)
    {

    }

    ~Knight()
    {
        if(_pet)
            delete _pet;
    }

    void PrintInfo() const
    {
        // 멤버 변수를 수정 불가능
        // 읽기 전용
        // _hp = 20; -> NO
    };

    // 복사 대입 연산자
    void operator=(const Knight& knight)
    {
        cout << "operator=(const Knight)" << endl;
        _hp = knight._hp;
        
        // 깊은 복사가 일어남 -> 새로운 메모리를 할당하고 복사할 량이 많아질수록 일이 늘어남.
        if (knight._pet)
            // knight._pet과 같은 정보를 가진 객체를 생성해서 _pet에 넣어줌.
            _pet = new Pet(*knight._pet);
    }

    // ! 이동 대입 연산자
    // noexcept : 에러를 표시하지 않는다.
    // rvalue이기 때문에 원본이 회손되도 괜찮음
    void operator=(Knight&& knight) noexcept
    {
        cout << "Knight&& knight" << endl;

        _hp = knight._hp;
        // 얇은 복사 -> 깊은 복사에 비해서 일이 적음.
        // 매개변수가 가지고 있는 _pet주소를 그대로 가져옴.
        _pet = knight._pet;

        // 매개변수가 가지고 있는 _pet주소를 없애버림.
        knight._pet = nullptr;
    }

public:
    int _hp = 100;
    Pet* _pet = nullptr;
};

void TestKnight_Copy(Knight knight) { /* 값을 수정해도 원본에 영향 없음 */}
void TestKnight_LValueRef(Knight& knight) 
{
     // 값을 수정하면 원본에 영향이 감
     // ! 값을 받아서 수정하거나 복사하던가 등등 원하는데로 할 수 있음
}
void TestKnight_ConstLValueRef(const Knight& knight)
{ 
    // ! 값을 받아서 아무것도 못하고 오로지 읽기으로만 사용 가능하다.
    // lvalue가 와도 읽기용으로 사용하겠다 
    // const를 사용한 함수만 사용가능
    knight.PrintInfo();
}

// ! &&를 붙여 오른값을 받는 특별한 참조라고 표시함.
void TestKnight_RValueRef(Knight&& knight)
{
    // ! 값을 받아서 읽고 쓰기 등 원하는데로 할 수 있음.
    // ! 여기서 사용하고 객체는 사용하지 않을거라는 힌트를 가짐.
    // -> 원본값을 회손하든 말든 유지를 안해도 상관없다.
    // ! 이동 대상이 됨.

    // rvalue를 받아줌
    // 임시객체 이라도 참조형이기 때문에 원본을 수정할 수 있다.
    knight._hp = 20;
}

int main()
{
    int a = 3;
    // 3 = a;
    // 3은 수정할 수 없는 lvalue이다 = rvalue
    
    Knight k1;

    TestKnight_Copy(k1);
    TestKnight_LValueRef(k1);

    // 기본 생성자를 호출해서 생성된 객체를 바로 함수로 넘김
    // Knight()는 지속적인 개체(lvalue)인데 매개변수로 보내면 
    // 매개변수로 생성하면 함수에서만 사용하는 임시값으로 되서 오류를 일으킴
    // TestKnight_LValueRef(Knight());

    // 만약 const로 참조하면 오류는 피할 수 있음
    TestKnight_ConstLValueRef(Knight());

    // lvalue를 못넣음
    // TestKnight_RValueRef(k1);
    // rvalue만 받음
    TestKnight_RValueRef(Knight());

    // 기존에 있는 lvalue를 rvalue로 넘김
    TestKnight_RValueRef(static_cast<Knight&&>(k1));

    // k3에게 값을 넘겨줄 k2
    // k2는 이동 대입 연산자를 통해서 버려질 객체
    Knight k2;
    k2._pet = new Pet();
    k2._hp = 1000;

    Knight k3;
    // 이동 대입 연산자 호출
    // 복사보다는 값을 이동한다에 가까움
    k3 = static_cast<Knight&&>(k2);

    Knight k4;
    // 오른값 참조로 캐스팅함
    // std::move의 본래 이름 후보 중 하나가 rvalue_cast
    // std::move() = static_cast<Knight&&>()
    k4 = std::move(k3);

    // ptr를 여러곳에서 관리하면 뭐가 진짜인지 정리하기 어려움
    // 하나만 존재할 수 있는 ptr를 만들 수 있음
    std::unique_ptr<Knight> uptr = std::make_unique<Knight>();
    // std::unique_ptr<Knight> uptr2 = uptr; -> 오류 뜸

    // std::move()를 통해서 이동 대상이 되어 소유권을 넘길 수 있음.
    // uptr이 가지고 있던 모든 값을 uptr2가 가지고 uptr를 쓰레기값을 가짐.
    std::unique_ptr<Knight> uptr2 = std::move(uptr);

    return 0;
}