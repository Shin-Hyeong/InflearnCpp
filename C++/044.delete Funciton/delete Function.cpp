#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// delete (삭제된 함수)
// Modern C++ (C++11 이후 문법)

// 암묵적으로 있는 특정 함수를 사용하지 못하도록 하는 것
// ex) &nullptr

// Q1) 복사연산자가 실행되지 않도록 막기
class Knight
{
public:
    // public에서 하는게 관례
    // 막고 싶은 함수 뒤에 = delete
    // 완전히 막을 수 있음.
    void operator=(const Knight& k) = delete;

// 기존 방식 실행시키고 싶지 않는 함수를 private에 정의하지 않고 선언만 함.
// 복사 연산자를 구현하면 Knight내에서는 사용가능한 반쪽짜리 막음.
private:
    // void operator=(const Knight& k)
    // {
         // TODO 복사 연산자 구현
    // }

    // Admin class에서는 사용할 수 있도록 허용됨. -> 완전 막지 못함.
    friend class Admin;

public:
    int _hp = 100;
};

class Admin
{
public:
    void CopyKnight(const Knight& k)
    {
        Knight k1;
        // k1 = k;
    }
};

int main ()
{
    Knight k1;
    Knight k2;

    // 복사 연산자
    // k1 = k2;

    return 0;
}