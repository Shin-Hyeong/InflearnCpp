#include <iostream>
#include <vector>
using namespace std;

// STL (Standard Template Library)
// 프로그램할 때 필요한 자료구조/알고리즘등를 템플릿으로 제공하는 라이브러리

// 컨테이너(Container) : 데이터를 저장하는 객체 (자료구조 Data Structure)

// vector(동적 배열 - C#:List, C++:vector)
// - vector의 동작 원리 (size/capacity)
// - 중간 삽입/삭제
// - 처음/끝 삽입/삭제
// - 임의 접근

// ! 반복자(Iterator)
// 포인터와 유사한 개념. 컨테이너의 원소(데이터)를가리키고, 다음/이전 원소로 이동 가능.
// ? &v[i]를 사용하면 더 간편한데 왜 Iterator를 사용하나
// vector 한정해서 &v[i]가 편리한건 맞다.
// 하지만 Iterator는 모든 Container가 가지고 있는 공통적 개념이다.
// 다른 Container v[i]와 같은 인덱스 접근이 안될 수 있음.

int main()
{
    vector<int> v1(10);
    vector<int> v2(10);

    for (int i = 0; i < static_cast<unsigned int>(v1.size()); i++)
    {
        v1[i] = i;
        v2[i] = i;
    }
    // iterator -> _Vector_iterator(라이브러리의 특정 class)
    vector<int>::iterator it;
    int* ptr;

    // vector의 첫번째 데이터 주소를 받아오기
    ptr = &v1[0];
    it = v1.begin();

    // 포인터 변수 : 그냥 주소값을 가지는 변수 -> 주소값만 가지고 있음
    cout << (*ptr) << endl;
    // ! *를 붙여 값에 접근할 수 있도록 맵핑한 특수한 class -> 주소값과 다른 여러가지 값을 가지고 있음.
    cout << (*it) << endl;
    
    // 다음 데이터로 이동 v1[0] -> v1[1]
    ptr++; ++ptr;   ptr--; --ptr;
    it++; ++it;     it--; --it;

    ptr += 2;   ptr = ptr - 2;
    it += 2;    it = it -2;

    // vector의 시작점 -> vector 0번째 요소를 가르킴
    vector<int>::iterator itBegin = v1.begin();

    // vector의 종료점 -> vector의 마지막 요소의 다음 주소를 나타냄.
    // v1[9] -> 다음주소[end가 가르키는 주소(쓰레기 값)]
    vector<int>::iterator itEnd = v1.end();

    // v1 vector의 시작주소부터 데이터가 없는 주소까지 실행
    // it++보다 ++it가 성능이 조금 더 좋음. (임시 변수에 저장하는 과정이 추가됨.)
    // it++ : it를 임시 변수에 복사 -> it 증가 -> 임시변수를 반환 -> it의 값은 그대로지만 다시 it를 보면 증가 함.
    // ++it : it 증가 -> it를 반환 -> 증가된 it값을 바로 사용함

    // iterator를 사용하기
    for (vector<int>::iterator it = v1.begin(); it != v1.end(); ++it)
    {
        cout << (*it) << " ";
    }
    cout << endl;

    int* ptrBegin = &v1[0]; // v1.begin().Ptr; -> begin()이 가지고 있는 주소를 가져옴.
    int* ptrEnd = ptrBegin + 10; // v1.end()._Ptr -> end()이 가지고 있는 주소를 가져옴.

    // 포인터를 사용하기
    for(int* ptr = ptrBegin; ptr != ptrEnd; ++ptr)
    {
        cout << (*ptr) << " ";
    }
    cout << endl;

    // const int* -> 데이터를 수정하지 않고 읽기 전용
    // cbegin -> const begin
    vector<int>::const_iterator cit1 = v1.cbegin();

    // 역방향 반복자(뒤에서 부터 읽기)
    // rbegin -> reverse begin
    for (vector<int>::reverse_iterator it = v1.rbegin(); it != v1.rend(); ++it)
    {
        cout << (*it) << " ";
    }
    cout << endl;

    // vector : 동적 배열 = 배열
    // 원소가 하나의 메모리 블록에 연속하게 저장된다.

    // !  - 중간 삽입/삭제 (BAD)
    // 중간 삽입
    // 원하는 자리의 뒷 원소들을 다 한자리씩 뒤로 이동시키고
    // 중간에 빈 자리에 값을 넣는 형태
    // [0][1][2][3][4][][] -> [0][1][][2][3][4][] -> [0][1][5][2][3][4][]

    // 중간 삭제
    // 원하는 자리를 삭제하고 삭제된 원소 뒤의 원소들을 1칸씩 앞으로 이동시켜야한다.
    // [0][1][2][3][] -> [0][][2][3][] -> [0][2][3][][]

    // ! - 처음 / 끝 삽입 / 삭제 (BAD / GOOD)
    // 처음 원소를 삽입/삭제하는 것은 중간 삽입/삭제와 같은 형식으로 작동한다.
    // 맨 뒷 원소를 삽입/삭제하는 것은 다른 원소들에게 영향을 주지 않기 때문에 수정 작업 중 좋다.

    // v1 vector의 맨 뒤 원소에 1추가
    v1.push_back(1);
    // v1 vector의 맨 뒤 원소를 삭제
    v1.pop_back();

    // ! insert와 erase는 iterator를 반환함.
    // iterator : 포인터와 유사한 개념. 컨테이너의 원소(데이터)를가리키고, 다음/이전 원소로 이동 가능
    // insert : 값을 삽입한 위치를 가르킴.
    // erase : 값을 삭제한 위치를 가르킴. 

    // 중간값을 삽입
    // [0][1][2][3][4][][] -> [0][1][5][2][3][4][]
    // 삽입 도중 Vector의 Capacity가 작아지면 더 넓은 위치로 이동함
    // insertIt는 v1.begin() + 2 위치를 가르킴.
    vector<int>::iterator insertIt = v1.insert(v1.begin() + 2, 5);
    cout << &insertIt << endl;

    // 중간값 삭제
    // [0][1][5][2][3][4][] -> [0][1][2][3][4][][]
    // eraseIt1는 v1.begin() + 2 위치를 가르킴.
    vector<int>::iterator eraseIt1 = v1.erase(v1.begin() + 2);
    cout << &eraseIt1 << endl;

    // 중간 범위 삭제
    // [0][1][2][3][4][][] ->[0][1][4][][][][]
    // 삭제 시작 주소부터 끝 주소의 앞까지 삭제함
    // eraseIt2는 v1.begin() + 2 위치를 가르킴.
    vector<int>::iterator eraseIt2 = v1.erase(v1.begin() + 2, v1.begin() + 4);
    cout << &eraseIt2 << endl;

    // vector를 스캔하면서 3이라는 데이터가 있으면 일괄 삭제하고 싶다.
    for (vector<int>::iterator it = v2.begin(); it != v2.end();)
    {
        int data = *it;
        if (data == 3)
        {
            // it를 포인터 방식대로 삭제하면 it가 가지고 있는 Container(v2) 정보도 같이 삭제해버림.
            // 삭제된 it는 Container(v2)의 소속이 아니게 되어 어떠한 활동도 하면 안됨.
            // v2.clear()도 마찬가지
            // v2.erase(it);

            // erase가 반환해주는 삭제된 주소 위치를 가져와야 한다.
            it = v2.erase(it);
        }

        // 삭제된 주소에 앞으로 땅겨지면서 다음 차례에 검사해야할 원소가 들어옴.
        // ++it가 for문에 있으면 삭제된 원소 주소로 이동된 원소는 검사를 하지 못함.
        // else로 따로 생성하여 삭제된 원소 주소도 다시 검사하도록 함.
        else
        {
            ++it;
        }
    }

    // ! - 임의 접근 (Random Access)
    // ? 3번째 데이터는 어디 있습니까?
    // 사용자가 원하는 vector의 원소에 값을 수정할 수 있음
    v1[3] = 3; 

    return 0;
}