#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// auto (type deduction)
// Modern C++ (C++11 이후 문법)

class Knight
{
public:
    int _hp;
};

int main ()
{
    // int a = 3;
    // float b = 3.14f;
    // double c = 1.23;
    // Knight d = Knight();
    // const char* e = "Hello";

    // 입력된 값의 type를 추론해서 변수의 type을 결정해줌.
    // Template와 같은 느낌
    auto a = 3;
    auto b = 3.14f;
    auto c = 1.23;
    auto d = Knight();
    auto e = "Hello";

    // 추론 규칙은 생각보다 복잡해질 수 있다.

    auto f = &d;            // Knight* f
    const auto test1 = b;   // const float test1

    // 이미 *표시가 있지만 e가 const char*상태이기 때문에 상태를 최대한 맞추기 위해
    // (const char*)*이 아닌 const char*으로 변경된다
    auto* test2 = e;        // const char* test2
    // a는 int 타입인데 auto*형태로 추론할려해서 오류를 일으킴.
    // auto* test3 = a;

    // ! 주의
    // ! 기본 auto는 const, &를 무시함.
    // a의 &값
    int& reference = a;
    // a의 const
    const int cst = a;

    auto test4 = reference;     // int& (X) -> int
    auto test5 = cst;           // const int (X) -> int

    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    for (vector<int>::size_type i = 0; i < v.size(); ++i)
    {   
        // v의 원소가 변화가 없음
        auto data1 = v[i];
        data1 = 100;

        // v의 모든 원소가 100으로 변경됨.
        int& data2 = v[i];
        data2 = 100;

        // auto에 &을 붙여 &를 유지시킴
        auto& data3 = v[i];
        data3 = 200;

        // map인경우 pair<int, Player*>을 auto로 짧게 사용할 수 있음.
    }

    // 타이핑이 길어지는 경우 사용하면 좋음
    // 가독성을 위해 일반적으로 안쓰는것이 좋다.
    map<int, int> m;

    pair<map<int,int>::iterator, bool> ok1 = m.insert(make_pair(1, 100));
    // auto 사용
    auto ok2 = m.insert(make_pair(2, 200));
    
    map<int,int>::iterator it1 = ok1.first;
    map<int,int>::iterator it2 = ok2.first;
    int key1 = it1->first;
    int key2 = it2->first;

    for (vector<int>::iterator it3 = v.begin(); it3 != v.end(); ++it3)
    {
        cout << (*it3) << endl;
    }

    // auto 사용
    for (auto it3 = v.begin(); it3 != v.end(); ++it3)
    {
        cout << (*it3) << endl;
    }

    return 0;
}