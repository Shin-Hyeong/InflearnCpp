#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// 전달 참조 (forwarding reference)

// 보편 참조 (universal reference) C++ 17 이전 보편참조라고 불렸음.
// 전달 참조 (forwarding reference) C++17

// Template와 auto같은 변형하는 자료형에서만 나타남.
// 형식 연역(type deduction)이 일어날 때 발생함.

// 오른값 참조, 왼값 참조냐에 따라 어떻게 사용할지는 달라짐
// 하나의 함수에 어떤 참조에 따라 맞게 설계함.

class Knight
{
public:
    Knight() { cout << "기본 생성자" << endl; }
    Knight(const Knight&) { cout << "복사 생성자" << endl; }
    Knight(Knight&&) noexcept { cout << "이동 생성자" << endl; }
};

void Test_RValueRef(Knight&& k) // 오른값 참조
{

}

template<typename T>
// T 앞에 const를 붙이면 전달 참조가 아니라 오른값 참조로 고정됨.
void Test_ForwardingRef(/*const*/T&& param)
{
    // 왼쪽 참조이면 복사 생성자를 호출 (깊은 복사)

    // 오른 참조이면 이동 생성자를 호출 (얇은 복사)

}

template<typename T>
// param은 오른값을 넘겨받았어도 param 자체는 왼값임.
void Test_ForwardingRef2(T&& param)
{   

    // 왼쪽 참조라면 복사
    // Test_Copy(param);                // 복사 생성자를 호출함.

    // 오른 참조라면 이동
    // Test_Copy(std::move(param));     // 이동 생성자를 호출함

    // forward : param이 왼쪽 참조면 복사, 오른참조면 이동을 시켜줌.
    Test_Copy(forward<T>(param));
}

void Test_Copy(Knight k)
{

}

int main ()
{
    Knight k1;

    // move : 오른값 캐스팅
    Test_RValueRef(std::move(k1));

    Test_ForwardingRef(k1);             // template가 왼값 참조로 인식함
    Test_ForwardingRef(std::move(k1));  // template가 k1를 오른값으로 인식함

    auto&& k2 = k1;             // auto가 왼값 참조로 인식함
    auto&& k3 = std::move(k1);  // auto가 오른값 참조로 인식함

    // ! ----------------------------------------------
    // 전달 참조를 구별하는 방법

    // 왼값 참조
    // k4는 왼값 타입을 가짐.
    Knight& k4 = k1;
    // 오른 참조
    // k5는 오른값 타입을 가짐.
    Knight&& k5 = std::move(k1);

    // ! 오른값 : 왼값이 아님 = 단일식에서 벗어나면 사용 X
    // ! 오른값 참조 : 오른값만 참조할 수 있는 참조 타입
    // Test_RValueRef(k5);
    // k5은 오른값 참조 타입으로 선언되었지만 단일식을 벗어나서도 사용가능함.
    // k5._멤버변수
    // 그래서 Test_RValueRef()에 그대로 넣지 못함.

    Test_RValueRef(std::move(k5));

    // 왼쪽 참조 : forward가 복사 생성자를 호출하도록 함
    Test_ForwardingRef2(k5);

    // 오른 참조 : forward가 이동 생성자를 호출하도록 함.
    Test_ForwardingRef2(std::move(k5));

    return 0;
}