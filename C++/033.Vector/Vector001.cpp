#include <iostream>
#include <vector>
using namespace std;

// STL (Standard Template Library)
// 프로그램할 때 필요한 자료구조/알고리즘등를 템플릿으로 제공하는 라이브러리

// 컨테이너(Container) : 데이터를 저장하는 객체 (자료구조 Data Structure)

// vector(동적 배열 - C#:List, C++:vector)
// ! - vector의 동작 원리 (size/capacity)
// - 중간 삽입/삭제
// - 처음/끝 삽입/삭제
// - 임의 접근

int main ()
{
    // 배열(사이즈 고정)
    // 배열의 크기를 상수만 받기 때문에 유동적으로 크기를 바꿀수 없음.
    const int MAX_SIZE = 10;
    int arr[MAX_SIZE] = {};

    for (int i = 0; i < MAX_SIZE; i++)
    {
        arr[i] = i;
    }

    for (int i = 0; i < MAX_SIZE; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    // 동적배열
    // ? 어떻게 유동적으로 사용할 수 있을까?
    // 1) 처음 할당할 때 여유분을 두고 메모리를 할당함.
    // 2) 여유분까지 사용했으면, 메모리를 추가로 할당함.
    // 배열의 메모리 증설 방법(100 -> 1000)
    int* arr2 = new int[100];
    delete arr2; arr2 = nullptr;
    // 기존의 배열을 삭제하고 새로 만듦
    int* arr3 = new int[1000];
    delete arr3; arr3 = nullptr;

    // ? 1) 여유분은 얼마만큼이 적당할까?
    // ? 2) 메모리를 추가로 할당하면 얼마만큼 할까?
    // ? 3) 메모리를 증설하게 되면 기존의 데이터는 어떻게 처리할까?

    vector<int> v1;

    // v1.size() : 실제 사용 데이터 개수
    // 1 2 3 4 5 6 7 ...

    // v1.capacity : 여유분을 포함한 용량 개수
    // 증설하는 방식은 컴파일러마다 다름.(VS 컴파일러는 1.5배씩 늘림)
    // 1 2 4 8 16 32 64 128 256 512 1024

    // [1 2 3 4 5] [ 다른 메모리 사용 중 ]
    // 더 큰 메모리 위치로 복사
    // [1 2 3 4 5 6 7 8 ...             ]
    // 기존에 위치한 메모리 위치의 데이터는 삭제
    // [         ] [ 다른 메모리 사용 중 ]
    // [1 2 3 4 5 6 7 8 ...             ]
    // 이동할 데이터가 많아지면 부담이 될 수 있음 -> 데이터 량이 많아질수록 할당해주는 메모리량이 많아짐(2^n)

    // 초반에 이동하는 횟수가 많음.
    // 설계 단계에서 어느정도 개수를 알고 있음. 초반에 capacity를 설정할 수 있음.
    // ! 처음 할당되는 메모리 량이 1개가 아닌 512로 시작함.
    v1.reserve(512);

    // 사용하고 있는 갯수를 지정할 수 있음.
    // vector에 0값이 들어감.
    v1.resize(512);
    // size가 1024인 vector에 모든 값을 1로 생성
    vector<int> v2(1024, 1);

    // capacity는 자동으로 늘어나지만 자동으로 줄어들진 않는다.
    // size가 작아져도 capacity는 유지됨.

    for (int i = 0; i < 1000; i++)
    {
        v1.push_back(100);
        cout << v1.size() << " " << v1.capacity() << endl;
    }
    // 맨 앞에 있는 데이터 확인
    cout << v1.front() << endl;

    // 맨 뒤에 있는 데이터를 확인
    cout << v1.back() ;

    // 맨 뒤에 있는 데이터를 추출    
    v1.pop_back();
    
    // v1이 가지고 있는 size, capacity를 그대로 복사
    vector<int>v3 = v1;

    // vector내 데이터 삭제 -> size : 0, capacity : 유지
    v1.clear();
    cout << v1.size() << " " << v1.capacity() << endl;

    // vector Capacity도 0으로 삭제
    // 더미(임시)의 vector를 생성 -> 더미와 v1를 스왑 -> 더미vector는 실행하면 소멸됨.
    vector<int>().swap(v1);
    cout << v1.size() << " " << v1.capacity() << endl;

    return 0;
}