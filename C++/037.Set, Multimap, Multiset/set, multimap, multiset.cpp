#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>
using namespace std;

// set, multimap, multiset
#include <set>

// ! set :  map(key, value)에서 key를 value로 이용하고 싶을때 set를 사용한다 (key = value 일때)
// ! multimap : map 에서 중복 key를 허용
// ! multiset : set 에서 중복 key를 허용

// multimap, multiset은 사실상 거의 사용하지 않음.
// set 경우 map에서 key값들을 set에 저장해두었다가 검색해서 찾는 형식

int main ()
{
    // key = value
    set<int> s;

    // ! 넣기 (pair 필요 X)
    s.insert(10);
    s.insert(30);
    s.insert(20);
    s.insert(50);
    s.insert(40);
    s.insert(70);
    s.insert(90);
    s.insert(80);
    s.insert(100);

    // ! 빼기
    s.erase(40);

    // ! 찾기
    set<int>::iterator findIt = s.find(50);
    if (findIt == s.end())
    {
        cout << "못 찾음" << endl;
    }
    else
    {
        cout << "찾음" << endl;
    }

    // ! 순회
    for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
    {
        cout << (*it) << " "; // 10 20 30 50 70 80 90 100
    }


    // ! 임의 접근
    // map은 key를 찾아서 value를 바꾸는 형식이였지만 
    // set은 key가 곧 value이기 때문에 임의 접근 연산자로 접근할 수 없다.
    // s[10] = 5;

    cout << endl << "-------------------------------------------------------" << endl;

    multimap<int, int> mm;

    // ! 넣기
    mm.insert(make_pair(1, 100));   // 삭제
    mm.insert(make_pair(1, 200));   // 삭제
    mm.insert(make_pair(1, 300));   // 삭제
    mm.insert(make_pair(2, 400));   // 삭제
    mm.insert(make_pair(2, 500));
    mm.insert(make_pair(2, 600));
    mm.insert(make_pair(3, 700));


    // ! 뺴기
    // key가 1인 multimap을 모두 날림.
    // count는 erase로 삭제한 갯수를 받음. 
    unsigned int count = mm.erase(1);
    cout << count << endl;  // 3

    // 특정 노드만 삭제 -> 찾아서 삭제
    // key값이 2인 노드 중 첫번째꺼만 삭제
    multimap<int, int>::iterator itFind = mm.find(2);
    // 다음 노드를 삭제하고 싶으면
    // ++itFind;
    if (itFind != mm.end())
        mm.erase(itFind);

    // ! 순회
    // - 특정 키값을 가지고 있는 범위
    // equal_range : pair<iterator, iterator> 형태로 이루어진 반환값을 줌.
    // key가 2을 가진 노드 시작주소(mm.begin())와 끝나는 주소 다음(mm.end()느낌)을 가르킴.
    pair<multimap<int,int>::iterator, multimap<int,int>::iterator> itPair;
    itPair = mm.equal_range(2);
    
    // equal_range는 시작점과 끝나는점을 알려주는데 따로따로 받을 수 있다.
    // 노드의 시작점        itPair.first
    multimap<int, int>::iterator itBegin = mm.lower_bound(2);
    // 노드의 끝나는 점     itPair.second
    multimap<int, int>::iterator itEnd = mm.upper_bound(2);

    for (multimap<int,int>::iterator it = itPair.first; it != itPair.second; ++it)
    {
        cout << "equal_range : " << it->first << " " << it->second << endl;
    }

    for (multimap<int, int>::iterator it = itBegin; it != itEnd; ++it)
    {
        cout << "lower/upper_bound : " << it->first << " " << it->second << endl;
    }

    // ! 임의 접근
    // 검색을 하기 위한 key값이 여러개이기 떄문에
    // 특정 key에 대한 value들을 변경되는걸 막기 위해
    // mm[1] = 500;

    cout << "-------------------------------------------------------" << endl;

    multiset<int> ms;

    // ! 넣기
    ms.insert(100); // <- ms.find(100)
    ms.insert(100);
    ms.insert(100);
    ms.insert(200);
    ms.insert(200);

    // ! 찾기
    // 100인 노드를 다 찾는게 아니고 100인 노드를 첫번째 노드만 찾음.
    multiset<int>::iterator itFind2 = ms.find(100);

    // 100인 노드 범위로 찾기
    pair<multiset<int>::iterator, multiset<int>::iterator> itPair2;
    itPair2 = ms.equal_range(100);

    for (multiset<int>::iterator it = itPair2.first; it != itPair2.second; ++it)
    {
        cout << (*it) << endl;
    }

    // equal_range는 시작점과 끝나는점을 알려주는데 따로따로 받을 수 있다.
    // 노드의 시작점        itPair2.first
    multiset<int>::iterator itBegin2 = ms.lower_bound(100);
    // 노드의 끝나는 점     itPair2.second
    multiset<int>::iterator itEnd2 = ms.upper_bound(100);

    for (multiset<int>::iterator it = itBegin2; it != itEnd2; ++it)
    {
        cout << (*it) << endl;
    }

    return 0;
}