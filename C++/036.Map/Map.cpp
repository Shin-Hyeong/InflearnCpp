#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <ctime>
#include <map>
using namespace std;

// map
// 연관 컨테이너

class Player
{
public:
    Player() : _playerId(0) {}
    Player(int playerId) : _playerId(playerId) {}
public:
    int _playerId;

};

int main ()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    // Player 타입의 객체 주소를 가지고 있는 vector
    vector<Player*> v;

    // 플레이어 10만 입장
    for (int i = 0; i < 100000; i++)
    {   
        // Player 객체를 동적 할당
        Player* p = new Player(i);
        // 동적할당한 주소를 vector에 저장
        v.push_back(p);
    }

    // 5만명 퇴장
    for (int i = 0; i < 50000; i++)
    {
        int randIndex = rand() % v.size();

        // 메모리해제
        Player* p = v[randIndex];
        delete p;

        // vector에서도 삭제
        v.erase(v.begin() + randIndex);
    }

    // ? ID가 10000인 Player를 찾아주세요
    // for문 통해서 찾을때까지 loop를 돈다.
    // vector와 같은 선형 데이터 구조는 데이터를 빠르게 찾는 마당한 방법이 없다.
    
    // ! vector, list의 치명적 단점
    // 원하는 조건에 해당하는 데이터를 빠르게 찾을 수 없다


    // ! map
    // 균형 이진 트리 (AVL)
    // - 노드 기반

    class Node
    {
    public:

    public:
        Node*   _left;
        Node*   right;

        // DATA
        // int     _key;
        // Player* _value;
        pair<int, Player*> _data;
    };

    // map<type key,type value> ->  ex) map<int, Player*>
    // key : 노드의 순서
    // value : 노드가 가지고 있는 실질적인 값.
    map<int, int> m;

    for (int i = 0; i < 100000; i++)
    {
        // insert : pair 값을 요구함 -> key와 value를 하나로 묶어서 주면 됨.
        // pair<type1,type2>(type1의 값, type2의 값)
        m.insert(pair<int, int>(i, i * 100)); // key : i, value : i * 100
    }

    for (int i = 0; i < 50000; i++)
    {
        int randValue = rand() % 50000;
        // m에 저장되어 있는 Key를 찾아서 삭제, erase엔 4가지 삭제 방법이 있음.(범위 삭제, iterator를 이용한 삭제)
        // Erase By Key
        m.erase(randValue);
    }

    // ? ID가 10000인 Player를 찾고 싶다.
    // 이진 트리를 활용하여 vector보다 빠르게 찾을 수 있다.

    // key값이 10000인 노드의 iterator를 반환함.
    map<int,int>::iterator findIt = m.find(10000);
    // 삭제되면 m.end()와 같은 값을 가짐.
    // findIt : map<int,int>::iterator 형태
    // m.end() : map<int,int>::iterator 형태
    // findIt != nullptr를 할 수 없음.
    if (findIt != m.end())
    {
        cout << "찾음" << endl;
    }
    else
    {
        cout << "못찾음" << endl;
    }

    // ? 같은 key를 삽입(insert)하거나 삭제(erase)를 하면 어떻게 될까?
    // erase는 size_t형태를 반환함.
    // size_t = unsigned int 형태를 typedef한것
    unsigned int count = 0;
    // 만약 5만명 삭제하는 코드에서 삭제가 안되고 여기에서 삭제되었다면 count는 1를 반환받음.
    count = m.erase(10000);
    // 이미 삭제되었기 때문에 count 0를 반환받음.
    count = m.erase(10000);
    // ! 동일한 key를 삭제해도 큰 문제는 없음.

    // insert는 pair<map<int,int>::iterator, bool>형태로 반환해줌.
    // iterator와 bool형태가 pair를 이룸.
    // iterator : insert한 iterator를 반환
    // bool : insert한 성공여부
    pair<map<int,int>::iterator, bool> ok;

    // make_pair(1, 100) = pair<int, int>(1, 100)와 같음.
    // key : 10000에 value 100가 추가됨.
    // ok = ((10000, 100), true)
    ok = m.insert(make_pair(10000, 100));

    // key : 10000에 value 200으로 변경안됨 -> value 100으로 유지.
    // ok = ((10000, 200), false)
    ok = m.insert(make_pair(10000, 200));
    // ! 동일한 key를 추가하면 추가된 키는 무시됨.

    // map 순회
    // v[0] ~ v[i]
    for (map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
    {
        // vector와 다르게 (*it)가 key와 value를 둘다 가지고 있는 형태
        pair<const int, int>&p = (*it);
        int key = p.first;      // int key = it->first;
        int value = p.second;   // int value = it->second;

        cout << key << "    " << value << endl;
    }

    // 특정 key가 없으면 추가, 있으면 value 수정 1
    map<int, int>::iterator findIt2 = m.find(10000);
    if (findIt != m.end())
    {
        findIt2->second = 200;
    }
    else
    {
        m.insert(make_pair(10000,10000));
    }

    // 특정 key가 없으면 추가, 있으면 value 수정 2
    // key값이 10000이 있으면 value를 300으로 수정
    // 없다면 새로 생성.
    m[10000] = 300;

    // ! [] 연산자 사용할 때 주의
    // 대입을 하지 않더라도 (Key/Value) 형태의 데이터가 추가된다.

    // key/Value를 다 날림.
    m.clear();

    // map의 key값을 확인할려함.
    for (int i = 0; i < 10; i++)
    {   
        // m[]은 기본적으로 없으면 생성하는 기능이 있기 떄문에
        // m[0] ~ m[9] 까지 새로 생성함. value는 기본값임 0이 들어감.
        cout << m[i] << endl;
    }

    // 넣기 (insert)
    // 수정 ([]) 
    // 삭제 (erase)
    // 찾기 (find, [])
    // 반복자 (map::iterator)(*it) pair<key, value>&

    map<int, int, int> m2;

    return 0;
}