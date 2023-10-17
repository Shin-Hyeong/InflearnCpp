#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// using
// Modern C++ (C++11 이후 문법)
// typedef 대신 사용할 수 있는 문법

// vector<int>::iterator을 VecIt라고 별칭을 주고 사용함.
typedef vector<int>::iterator VecIt;

// ID를 int로 사용할지 __int64로 사용할지 미확정일때 나중에 수정하기 용이함.
typedef int ID;

// using과 typedef의 차이
typedef __int64 ID1;
using ID2 = __int64;

// 1) 직관성이 더 높음
// - void*형태의 함수포인터
typedef void(*MyFunc)();
using MyFunc2 = void(*)();

// 2) 템플릿
// - typedef은 템플릿을 사용할 수 없음
template <typename T>
// typedef list<T> List2;
// 과거 typedef로 Template사용법
struct List2
{
    typedef list<T> type;
};

template <typename T>
using List = list<T>;


int main ()
{
    ID playerId = 0;

    List<int> li;
    li.push_back(2);

    List2<int>::type li2;
    li2.push_back(1);

    return 0;
}