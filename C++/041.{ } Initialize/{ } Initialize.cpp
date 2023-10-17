#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// 중괄호 초기화
// Modern C++ (C++11 이후 문법)
// - vector 등 container와 잘 어울림.
// - 축소 변환 방지
// - 기본 생성자 호출

// 괄호 초기화()를 기본으로 함
// - 전통적인 C++ : 거부감이 없음
// - vector 등 특이한 케이스에 대해서만 { } 사용

// 중괄호 초기화{}를 기본으로 함
// - 초기화 문법의 일치화
// - 축소 변환 방지

class Knight
{
public:
    Knight()
    {
        cout << "기본 생성자 호출" << endl;
    }

    Knight(int a, int b)
    {
        cout << "Knight(int, int)" << endl;
    }

    Knight(initializer_list<int> li)
    {
        cout << "Knight(initializer_list)" << endl;
    }
    

    void operator()()
    {
        cout << "Functor Test" << endl;
    }


public:

};

int main ()
{   
    // ! 일반 변수 초기화
    // = 초기화
    int a = 0;
    // ( )초기화
    int b(0);
    // { }초기화
    int c{0};

    // ! class 초기화
    Knight k1;
    Knight k2 = k1; // 복사 생성자 호출 (대입 연산자 X)
    Knight k3{k1};  // 복사 생성자 호출 (대입 연산자 X)
    Knight k4;      // 기본 생성자 호출
    k4 = k1;        // 대입 연산자

    // ! 배열 초기화
    int arr[] = {1, 2, 3, 4};

    // ! vector
    // push_back
    vector<int> v1; // 1 2 3
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    // () 초기화
    vector<int> v2(3, 1); // 1 1 1

    // ! - vector 등 container와 잘 어울림.
    // { } 초기화
    //  initialize_list의 생성자를 통해서 값을 받음
    vector<int> v3{1, 2, 3}; // 1 2 3

    // ! - 축소 변환 방지
    int x = 0;
    // 변환하는데 자동으로 축소 변화하는것 을 막음.
    double y1 (x);  // Ok
    // double y2 {x};  // No

    // ! - 기본 생성자 호출
    Knight k5;      // Knight 변수의 기본 생성자 호출
    Knight k6();    // Knight 함수 호출
    Knight k7{};    // Knight 변수의 기본 생성자 호출

    //  initialize_list의 생성자를 통해서 값을 받음
    Knight k8 {1, 2, 3, 4, 5};
    // (int, int) 생성자를 호출하지 않고 (initialize_list)를 호출함.
    // ! {}를 사용하면 생성자를 만들어도 initialize_list가 가장 최우선시로 호출함.
    Knight k9{1, 2};

    return 0;
}