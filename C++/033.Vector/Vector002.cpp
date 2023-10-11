#include <iostream>
#include <vector>
using namespace std;

// STL (Standard Template Library)
// 프로그램할 때 필요한 자료구조/알고리즘등를 템플릿으로 제공하는 라이브러리

// 컨테이너(Container) : 데이터를 저장하는 객체 (자료구조 Data Structure)

// vector(동적 배열 - C#:List, C++:vector)
// - vector의 동작 원리 (size/capacity)
// ! - 중간 삽입/삭제
// - 처음/끝 삽입/삭제
// - 임의 접근

// 반복자(Iterator)
// 포인터와 유사한 개념. 컨테이너의 원소(데이터)를가리키고, 다음/이전 원소로 이동 가능.
// ? &v[i]를 사용하면 더 간편한데 왜 Iterator를 사용하나
// vector 한정해서 &v[i]가 편리한건 맞다.
// 하지만 Iterator는 모든 Container가 가지고 있는 공통적 개념이다.
// 다른 Container v[i]와 같은 인덱스 접근이 안될 수 있음.

int main()
{
    vector<int> v1(10);

    for (int i = 0; i < static_cast<unsigned int>(v1.size()); i++)
    {
        v1[i] = i;
    }
    // iterator -> _Vector_iterator(라이브러리의 특정 class)
    vector<int>::iterator it;
    int* ptr;

    // vector의 첫번째 데이터 주소를 받아오기
    ptr = &v1[0];
    it = v1.begin();

    // *를 붙여 값에 접근할 수 있도록 맵핑한 특수한 class -> 주소값과 다른 여러가지 값을 가지고 있음.
    cout << (*ptr) << endl;
    // 포인터 변수 : 그냥 주소값을 가지는 변수 -> 주소값만 가지고 있음
    cout << (*it) << endl;
    
    // 다음 데이터로 이동 v1[0] -> v1[1]
    it++; ++it;     it--; --it;
    ptr++; ++ptr;   ptr--; --ptr;

    it += 2;    it = it -2;
    ptr += 2;   ptr = ptr - 2;

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
    vector<int>::const_iterator cit1 = v1.cbegin();

    // 역방향 반복자(뒤에서 부터 읽기)
    for (vector<int>::reverse_iterator it = v1.rbegin(); it != v1.rend(); ++it)
    {
        cout << (*it) << " ";
    }
    cout << endl;

    return 0;
}