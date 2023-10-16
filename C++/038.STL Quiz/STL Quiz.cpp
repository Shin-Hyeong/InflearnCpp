#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <ctime>
using namespace std;

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

        for (vector<int>::iterator itFind = itBegin; itFind != itEnd; ++itFind)
        {
            int data = *itFind;

            if (data = number)
            {
                found = true;
                it = itFind;
                break;
            }
        }

        cout << found << endl;
    }

    // Q2) 11로 나뉘는 숫자가 벡터에 있는지 체크하는 기능(bool, iterator)
    {
        bool found = false;       // 있으면 true, 없으면 false
        vector<int>::iterator it; // 있으면 해당 iterator. 없으면 end()

        // TODO
        vector<int>::iterator itBegin = v.begin();
        vector<int>::iterator itEnd = v.end();

        for (vector<int>::iterator itFind = itBegin; itFind != itEnd; ++itFind)
        {
            int data = *itFind;

            if (data % 11 == 0)
            {
                found = true;
                it = itFind;
                break;
            }
        }
        cout << found << endl;
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
    }

    // Q4) 벡터에 들어가 있는 모든 숫자들에 3을 곱해주세요
    {
        vector<int>::iterator itBegin = v.begin();
        vector<int>::iterator itEnd = v.end();
        for (vector<int>::iterator it = itBegin; it != itEnd; ++it)
        {
            (*it) *= 3;
        }
    }
    return 0;
}