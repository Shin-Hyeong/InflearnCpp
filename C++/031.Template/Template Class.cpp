#include <iostream>
#include <ctime>
using namespace std;

// 템플릿 기초
// 템플릿 : 함수나 클래스를 찍어내는 틀
// 1) 함수 템플릿
// 2) 클래스 템플릿

// typename T를 붙이면 어떤 타입도 다 넣을 수 있음
// 무조건 typename을 붙여야 하는 것은 아니다.

// int SIZE를 추가해서 class내에 하드코딩을 줄일 수 있다.
// class를 생성할 때 SIZE의 값을 넘겨주면 된다.
// int SIZE = 10을 하여 기본값을 설정할 수 있다.
// template<>안에 들어가는건 골라줘야 하는 목록
template<typename T, int SIZE = 10>
class RandomBox
{
public:
    T GetRandomData()
    {
        int idx = rand() % SIZE;
        return _data[idx];
    }

public:
    T _data[SIZE];
};

// 템플릿 특수화
// RandomBox를 double형태로 생성하게 되면 템플릿 특수화를 통해서 아래 class가 이용됨.
template <int SIZE>
class RandomBox<double, SIZE>
{
public:
    double GetRandomData()
    {
        cout << "RandomBox Double" << endl;
        int idx = rand() % SIZE;
        return _data[idx];
    }

public:
    double _data[SIZE];
};

int main ()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    // _data배열이 5인 int
    RandomBox<int, 5> rb1;
    for (int i = 0; i < 10; i++)
    {
        rb1._data[i] = i;
    }
    int value1 = rb1.GetRandomData();
    cout << value1 << endl;

    // _data배열이 20인 int
    const int index = 20;
    RandomBox<int, index> rb2;
    for (int i = 0; i < index; i++)
    {
        rb2._data[i] = i;
    }
    int value2 = rb2.GetRandomData();
    cout << value2 << endl;
    // rb1과 rb2는 완전 서로 다른 class로 취급된다
    // rb1 = rb2는 오류가 뜨게 됨.

    // 만약 _data를 여러 타입으로 구할려고 하면 template를 사용한다.
    // _data배열이 5인 float
    RandomBox<float, 5> rb3;
    for (int i = 0; i < 10; i++)
    {
        rb3._data[i] = i + 0.5f;
    }
    float value3 = rb3.GetRandomData();
    cout << value3 << endl;

    // _data배열이 10인 double
    RandomBox<double, 10> rb4;
    for (int i = 0; i < 10; i++)
    {
        rb4._data[i] = i + 0.51;
    }
    double value4 = rb4.GetRandomData();
    cout << value4 << endl;

    return 0;
}