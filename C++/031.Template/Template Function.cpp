#include <iostream>
using namespace std;

// 템플릿 기초
// 템플릿 : 함수나 클래스를 찍어내는 틀
// 1) 함수 템플릿
// 2) 클래스 템플릿

class Knight
{
public:

public:
    int _hp = 100;
};

// T라고 하는 이름을 가진 템플릿을 생성
template <typename T> // template<class T>으로도 선언가능.
void Print(T a)
{
    cout << a << endl;
}

// 템플릿 특수화
// 특정 매개변수에 대해서는 별도처리를 하고 싶은 경우
// 템플릿 함수는 명시적 특수화만 가능함.
template <>
// class Knight가 매개변수일 경우 사용.
void Print(Knight a)
{
    cout << "Knight !!!!!!!!" << endl;
    cout << a._hp << endl;
}

// 여러 인자값을 받을때 인자의 타입이 서로 다를 때
template<typename T1, typename T2>
void Print(T1 a, T2 b)
{
    cout << a << " " << b << endl;
}

// 반환값과 인자가 여러개여도 사용 가능함.
template <typename T> // template<class T>으로도 선언가능.
T Add(T a, T b)
{
    return a + b;
}

//연산자 오버로딩 (전역함수 버전)
ostream& operator<<(ostream& os, const Knight& k)
{
    os << k._hp;
    return os;
}


int main ()
{
    Print(50);              // int
    Print(51.0f);           // float
    Print(52.0);            // double
    Print("Hello World");   // const char*

    // <>안에 자료형을 넣으면 템플릿이 인자를 치환해서 사용함.
    Print<int>(55.4f);      // int

    // 반환값과 인자에 여러번 사용 가능
    Print<int>(Add(1, 2));
    Print<float>(Add(1.1f, 2.23f));

    // 인자의 값이 서로 다를때 사용도 사용 가능
    Print("Hollow", 3);     // const char*, int
    Print(4.8, 3);          // double, int

    Knight k1;
    // Print함수가 class를 받으면 어떤 것을 출력해야할지 모름
    // 연산자 오버로딩을 통해서 원하는 정보를 출력하도록 만들 수 있음.
    Print(k1);

    return 0;
}