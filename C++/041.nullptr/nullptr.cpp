#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// nullptr
// Modern C++ (C++11 이후 문법)

// C++11 이전 nullptr 사용하기 위해선
// NULL와 0을 사용함.

// 왜 nullptr를 사용하나
// 1) 함수 오버로딩과 관련됨.
// - 함수 타입에 대해 오작동을 피하기 위해

class Knight
{
public:
    // 멤버 함수
    void Test()
    {

    }
};

Knight* FindKnight()
{
    // TODO
    return nullptr;
}


void Test(int a)
{
    cout << "Test(int)" << endl;
}

void Test(void* ptr)
{
    cout << "Test(*)" << endl;
}

// ! nullptr 구현
const class
{

public:
    // 어떤 타입의 포인터와도 치환 가능
    template<typename T>
    operator T* () const
    {
        return 0;
    }

    // 클래스 C, 포인터 T
    // 클래스 C의 멤버 포인터 T에게 반환
    // 어떤 타입의 멤버 포인터와도 치환 가능
    template<typename C, typename T>
    operator T C::*() const
    {
        return 0;
    }

private:
    // 주소값& 추출하는 것을 막는다
    // &nullptr 방지
    void operator&() const;

// class를 선언하자마자 _Nullptr를 구현함.
// Nullptr _Nullptr; 과 같음.
} _Nullptr;


int main ()
{   

    // 1) 함수 오버로딩 오동작 방지
    Test(0);        // Test(int)
    Test(NULL);     // Test(int)
    Test(nullptr);  // Test(*)

    // auto를 사용해 반환값이 가시적으로 안보임
    auto knight = FindKnight();

    // knight가 일반 변수인지 포인터 변수인지 가시성 떨어짐
    if (knight == 0) {}
    // nullptr를 사용함으로써 knight가 포인터 변수임으로 확인가능.
    if (knight == nullptr) {} 
   
    // nullptr 타입
    // nullptr_t를 반환함.
    auto who = nullptr;

    nullptr_t amI = nullptr;

    // 직접 구현한 Nullptr
    Test(_Nullptr); // Test(*)

    // 멤버 함수 호출
    void (Knight::*memFunc)();
    memFunc = &Knight::Test;

    // 멤버 함수를 반환 하는 operator T C::*() const를 호출함.
    if (memFunc = _Nullptr) {}

    return 0;
}