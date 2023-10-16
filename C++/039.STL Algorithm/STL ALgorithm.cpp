#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <ctime>
using namespace std;

// Algorithm
#include <algorithm>

// 자료구조 : 데이터를 저장하는 구조
// 알고리즘 : 데이터를 어떻게 사용할 것인가?

// find
// find_if
// count
// count_if
// all_of
// any_of
// none_of
// for_each
// remove
// remove_if

int main ()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    vector<int> v;

    for (int i = 0; i < 100; i++)
    {
        int num = rand() % 100;
        v.push_back(num);
    }

    // Q1) number라는 숫자가 벡터에 체크하는 기능(bool, iterator)
    {
        int number = 50;

        bool found = false;     // 있으면 true, 없으면 false
        vector<int>::iterator it = v.end();   // 있으면 해당 iterator. 없으면 end()

        // TODO
        vector<int>::iterator itBegin = v.begin();
        vector<int>::iterator itEnd = v.end();

        // ! Find() : 지정한 범위에서 원하는 값의 첫번째로 만나는 위치를 찾아줌.
        // 매개변수로 _First(검색에 포함됨.), _Last(검색에 포함되지 않음.), 검색할 Value를 받음.
        // iterator를 반환함. -> vector에서 list, Deque로 변경되도 같은 문법
        vector<int>::iterator itFind = find(v.begin(), v.end(), number);
        if(itFind == v.end())
        {
            cout << "못 찾음" << endl;
        }
        else
        {
            cout << "찾음" << endl;
        }
    }

    // Q2) 11로 나뉘는 숫자가 벡터에 있는지 체크하는 기능(bool, iterator)
    {
        bool found = false;       // 있으면 true, 없으면 false
        vector<int>::iterator it; // 있으면 해당 iterator. 없으면 end()

        // TODO
        vector<int>::iterator itBegin = v.begin();
        vector<int>::iterator itEnd = v.end();

        // struct와 class 차이는 값을 저장할 수 있냐없냐의 차이
        // 나누었을 때 11로 나누어지는 숫자에 대해서 bool값을 반환하는 함수 객체
        struct CanDivideBy11
        {
            bool operator()(int n)
            {
                return (n % 11) == 0;
            }
        };

        // ! find_if() : 지정한 범위에서 원하는 조건에 맞는 값의 첫번째로 만나는 위치를 찾아줌.
        // 매개변수로 _First(검색에 포함됨.), _Last(검색에 포함되지 않음.), 함수 객체(bool형태) Pred를 받음.
        vector<int>::iterator itFind = find_if(v.begin(), v.end(), CanDivideBy11());
        if (itFind == v.end())
        {
            cout << "못 찾음" << endl;
        }
        else
        {
            cout << "찾음" << endl;
        }
    }

    // Q3) 홀수 인 숫자의 개수는? (count)
    {
        int count = 0;

        // TODO
        vector<int>::iterator itBegin = v.begin();
        vector<int>::iterator itEnd = v.end();

        for (vector<int>::iterator it = itBegin; it != itEnd; ++it)
        {
            int data = *it;

            if (data % 2 == 1)
                ++count;
        }
        cout << count << endl;

        struct IsOdd
        {
            bool operator()(int n)
            {
                return (n % 2) != 0;
            }
        };

        // ! count_if : count에 조건을 줄 수 있는 것.
        // 매개변수로 _First(검색에 포함됨.), _Last(검색에 포함되지 않음.), 함수 객체(bool형태) Pred를 받음.
        // 정수를 반환해줌.
        count = count_if(v.begin(), v.end(), IsOdd());
        

        // ! all_of() : 지정한 범위의 모든 값들이 조건에 대해서 true인지 확인
        // bool를 반환해줌
        bool b1 = all_of(v.begin(), v.end(), IsOdd());

        // ! any_of() : 지정한 범위의 값들 중 하나라도 조건에 대해서 true인지 확인
        // bool를 반환해줌
        bool b2 = any_of(v.begin(), v.end(), IsOdd());

        // ! none_of() : 지정한 범위의 모든 값들이  조건에 대해서 false인지 확인
        // bool를 반환해줌
        bool b3 = none_of(v.begin(), v.end(), IsOdd());

        cout << count << " " << b1 << " " << b2 << " " << b3 << endl;
    }

    // Q4) 벡터에 들어가 있는 모든 숫자들에 3을 곱해주세요
    {
        vector<int>::iterator itBegin = v.begin();
        vector<int>::iterator itEnd = v.end();
        for (vector<int>::iterator it = itBegin; it != itEnd; ++it)
        {
            (*it) *= 3;
        }

        struct MultiplyBy3
        {
            void operator()(int& n)
            {
                n = n * 3;
            }
        };

        // ! for_each() : 지정된 모든 범위에 원하는 행동을 시킴.
        // 어디서 어디까지 무엇을 하라
        for_each(v.begin(), v.end(), MultiplyBy3());
    }

    // Q5) 벡터에 들어가 있는 홀수를 일괄 삭제
    {   
        // 찾을 때마다 erase해서 다시 값들을 나열하는것은 매우 비효율적
        // for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        // {
        //     if ((*it % 2) != 0)
        //         it = v.erase(it);
        //     else
        //         ++it;
        // }   
        v.clear();

        // 1 4 2 5 9 7 2
        v.push_back(1);
        v.push_back(4);
        v.push_back(3);
        v.push_back(5);
        v.push_back(9);
        v.push_back(7);
        v.push_back(2);

        // ! remove : 특정한 범위에서 특정 값들을 앞쪽으로 이동시킴.
        // | 1 4 2 5 5 7 2
        // 1 : 삭제                         1 | 4 2 5 9 7 2
        // 4 : 이동                         4 4 | 2 5 9 7 2
        // 2 : 이동                         4 2 2 | 5 9 7 2
        // 5 : 이동                         4 2 5 9 | 9 7 2
        // 9 : 이동                         4 2 5 9 7 | 7 2
        // 7 : 이동                         4 2 5 9 7 7 | 2
        // 2 : 이동                         4 2 5 9 7 2 2 |
        // return 필요없는 위치를 반환       4 2 5 9 7 2 | 2
        // 4 2 5 9 7 2 2
        // 매개변수로 _First(검색에 포함됨.), _Last(검색에 포함되지 않음.), 삭제할 Value를 받음.
        vector<int>::iterator it1 = remove(v.begin(), v.end(), 1);
        // 마지막 2만 삭제
        v.erase(it1, v.end());

        struct IsOdd
        {
            bool operator()(int n)
            {
                return (n % 2) != 0;
            }
        };

        // ! remove_if : 특정한 범위에서 특정 조건에 따른 값들을 앞쪽으로 이동시킴.
        // | : 커서
        // | 1 4 2 5 5 7 2
        // 1 : 홀수 -> 패스                   1 | 4 2 5 9 7 2
        // 4 : 짝수 -> 맨 앞으로 이동          4 4 | 2 5 9 7 2
        // 2 : 짝수 -> 4 다음 자리로 이동      4 2 2 | 5 9 7 2
        // 5 : 홀수 -> 패스                   4 2 2 5 | 9 7 2
        // 9 : 홀수 -> 패스                   4 2 2 5 9 | 7 2
        // 7 : 홀수 -> 패스                   4 2 2 5 9 7 | 2
        // 2 : 짝수 -> 2 다음 자리로 이동      4 2 2 5 9 7 2 |
        // return 필요없는 위치를 반환         4 2 2 | 5 9 7 2
        // 4 2 2 5 9 7 2
        // 매개변수로 _First(검색에 포함됨.), _Last(검색에 포함되지 않음.), 함수객체 Pred를 받음.
        vector<int>::iterator it2 = remove_if(v.begin(), v.end(), IsOdd());
        // 4 2 2 | 5 9 7 2 -> 5 9 7 2 삭제
        // 4 2 2만 남음.
        v.erase(it2, v.end());
    }
    return 0;
}