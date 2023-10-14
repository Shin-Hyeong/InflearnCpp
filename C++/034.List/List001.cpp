#include <iostream>
#include <list>
using namespace std;

// list
// ! vector : 동적 배열 형태
// ! list : 노드(연결 리스트) 형태

// list : 단일/이중/원형 연결 리스트

// [1][2][3][4][5] X
// 리스트는 메모리에 연속적으로 저장되지 않음.
// [1] -> [2] -> [3] -> [4] -> [5]
// 각 노드에 다음 노드를 가리키는 주소값을 가짐.

// Node0[_data(4byte), _next(4 or 8 byte)] -> Node1[_data(4byte), _next(4 or 8 byte)] ->
class Node
{
public:
    // 주소를 타고 가면 자신과 같은 노드형태가 있을거다.
    Node*   _next;
    Node*   _prev;
    int     _data;
};

// 단일 리스트 : 노드의 연결이 한방향으로 이루어짐.
// [1] -> [2] -> [3] -> [4] -> [5]

// 이중 리스트 : 노드의 연결이 양방향으로 이루어짐.
// STL list를 사용하면 이중 리스트형태를 사용함.
// [1] <-> [2] <-> [3] <-> [4] <-> [5]

// 원형 리스트 : 노드의 연결이 원형으로 이루어짐.
// [1] <-> [2] <-> [3] <-> [4] <-> [5] <-> [1]

// - list의 동작 원리
// - 중간 삽입/삭제 (GOOD/GOOD)
// - 처음/끝 삽입/삭제 (GOOD/GOOD)
// - 임의 접근 (li[3] -> 지원안함.)

int main ()
{
    list<int> li;

    for (int i = 0; i < 100; ++i)
    {  
        // 맨 뒤에 삽입
        li.push_back(i);
    }
    // 맨 앞에 삽입 -> 라이브러리에 존재 -> vector에 비해 효율적이다
    li.push_front(10);

    // list의 원소 갯수
    int size = li.size();

    //li.capacity(); -> 동적 할당이 아니기 때문에 필요한 만큼 자리를 잡아둘 필요가 없음.

    // 맨 앞 원소 확인
    int first = li.front();

    // 맨 뒤 원소 확인
    int last = li.back();

    // 임의 접근 -> list는 연속적으로 저장되지 않아서 없음.
    // li[3] = 10;

    // list의 시작 주소
    list<int>::iterator itBegin = li.begin();
    // list의 마지막 주소
    list<int>::iterator itEnd = li.end();

    // [1(li.begin()이 가르키는 위치)] <-> [2] <-> [3] <-> [4] <-> [5] <-> [li.end()가 가르키는 위치] <-> [1]

    // li.begin()에서 앞으로 가면 논리적으론 li.end()가 나오는게 정상이지만 오류를 나타냄.
    // list<int>::iterator itTest1 = --itBegin; -> 오류

    // li.end()에서 앞 노드로 이동하는건 가능
    list<int>::iterator itTest2 = --itEnd;

    // li.end()에서 다음 노드로 가면 논리적으론 li.begin()가 나오는게 정상이지만 오류를 나타냄.
    // list<int>::iterator itTest3 = ++itEnd; -> 오류

    // ! .end()는 list(단일/이중)가 끝나는 지점을 나타내기 위함

    // 노드의 이동은 한번에 여러번 이동하는 것은 지원안하고 한 노드씩 이동하는 것만 지원함.
    // list<int>::iterator it2 = itBegin + 10; -> 지원 안함
    // list<int>::iterator it2 = ++itBegin; -> 지원

    // it의 주소 이동
    for (list<int>::iterator it = li.begin(); it != li.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    // ! 중간 삽입/삭제
    // 데이터가 연속적으로 저장되지 않고 각각의 노드형태로 이루어져 있기 때문에
    // 중간 삽입/삭제가 이루어지면 노드를 연결하는 주소값을 변경하여 삽입/삭제를 할 수 있다.

    // 중간값 삽입
    li.insert(itBegin, 100);

    // 중간값 삭제
    li.erase(li.begin());

    // 맨 앞 값 삭제
    li.pop_front();

    // 원하는 원소값 삭제
    li.remove(5);

    // ? 임의 접근이 안 되는데 중간 삽입/삭제는 빠르다?
    // 50번 인덱스에 있는 데이터 삭제
    // ! 50번째 인덱스를 찾는 건 느림.
    list<int>::iterator it = li.begin();
    for (int i = 0; i < 50; i++)
    {
        ++it;
    }

    // ! 하지만 찾은 인덱스를 삭제해서 49번 인덱스와 51번 인덱스가 서로 연결 시키는건 빠름.
    li.erase(it);

    return 0;
}