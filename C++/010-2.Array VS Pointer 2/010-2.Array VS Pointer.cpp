#include <iostream>
using namespace std;

int& TestRef();
int* TestPointer();
void TestWrong(int* ptr);

int main ()
{
    // 주소를 담는 변수
    // 진짜 값은 주소를 따라가야 있음.
    // p는 그저 그 곳으로 이동하기 위한 포탈 역할
    // x86은 4Byte x64은 8byte
    int* p;

    // 진짜 데이터를 가지고 있음.
    // 데이터의 묶음.  데이터의 묶음이 커질수록 메모리 차지가 늘어남.
    // 1, 2, 3, 4, 5, 6, 7, 8, 0, 0
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8};

    // 배열 = 포인터를 착각하는 경향이 있다.
    // - 배열이 이름이 배열의 시작 주소값을 가르키는 TYPE* 포인터로 변환가능하기 때문.
    // arr 배열 주소를 p에 넣음.
    p = arr;

    // [TYPE형 1차원 배열]과 [TYPE*형 포인터]는 완전히 호환이 된다.
    cout << "p[0]의 값 : " << p[0] << endl;                          // 1
    cout << "arr[0]의 값 : " << arr[0] << endl;              // 1

    cout << "p[5]의 값 : " << p[5] << endl;                          // 6
    cout << "arr[0]의 값 : " << arr[5] << endl << endl;              // 6

    cout << "*p의 값 : " << *p << endl;                              // 1
    cout << "*arr의 값 : "  << *arr << endl;                 // 1

    cout << "*(p + 3)의 값 : " << *(p + 3) << endl ;                 // 4
    cout << "*(arr + 3)의 값 : " << *(arr + 3) << endl << endl;      // 4

    // 2차원 배열 vs 다중 포인터

    // [1][2][3][4]
    int arr2[2][2] = {{1, 2},{3, 4}};

    // int** pp = arr2는 오류가 나기 때문에 강제로 형변환을 시켜 어떠한 상황이 일어나는지 확인.
    // 주소2[ ] << 4Byte
    // 주소1[ 주소2 ]
    // pp[ 주소1 ]
    //int** pp = (int**)arr2;

    // 오류가 남.
    // 주소1이 arr2의 주소를 가지고 있음.
    // arr2의 주소로 넘어가면 주소2의 주소를 가지고 있는 것이 아니고 데이터 값(1)을 가지고 있음.
    //cout << (**pp) << endl;

    // TYPE name [Array Number]
    // arr2는 원형이 int(*)[2] = arr2으로 이루어져 있음.
    // int형인 [2]배열을 이룬 (*)주소를 가진다.라는 뜻

    // int(*p2)[2] = arr2;
    // *p2가 가르키는 주소를 따라가면 int()[2]으로 이루어진 배열을 만남.
    // [1][2]
    // int()[2] = arr2;
    int(*p2)[2] = arr2;

    cout << "(*p2)[0]값 : " << (*p2)[0] << endl; // 1
    cout << "(*p2)[1]값 : " << (*p2)[1] << endl; // 2

    // [3][4]를 찾는법
    // *p2가 int[2]의 크기만큼(int가 2개)을 1개로 본다.
    cout << "(*(p2 + 1))[0]값 : " << (*(p2 + 1))[0] << endl; // 3
    cout << "(*(p2 + 1))[1]값 : " << (*(p2 + 1))[1] << endl << endl; // 4

    // 포인터로 2차원 배열 간략하게 접근하는 법
    cout << "p[0][0]의 값 : " << p2[0][0] << endl;
    cout << "p[0][1]의 값 : " << p2[0][1] << endl;
    cout << "p[1][0]의 값 : " << p2[1][0] << endl;
    cout << "p[1][1]의 값 : " << p2[1][1] << endl;

    // Pointer는 a의 주소를 가지지 못함.
    // a는 지역변수여서 TestPointer를 탈출하는 순간 없어짐.
    // Pointer는 주소를 못 받음.
    int* Pointer = TestPointer();

    return 0;
}

int& TestRef()
{
    int a = 1;
    return a;
}

int* TestPointer()
{
    int a = 1;
    return &a;
}

void TestWrong(int* ptr)
{   
    // 메모리에 int [100] 짜리 배열을 할당함.
    int a[100] = {};

    // 메모리상에서 배열의 끝을 알아보기 쉽게 a[99]위치에 0xAAAAAAAA을 넣음.
    a[99] = 0xAAAAAAAA;

    // 메모리에서 배열이 끝나면 바로 다음 메모리에 배열이 끝났다는 신호로 쓰레기값을 넣어둠
    // 문자열의 \0과 같은 느낌.

    // *ptr로 배열이 끝났다는 신호를 가지는 메모리에 0x12341234를 넣음.
    // TestWrong 함수가 끝나면서 배열을 정리할때 0x12341234도 같이 정리됨.
    // Crush가 발생. 
    // 실행하면 아무런 문제 발생하지 않지만 이로 인해 스노우볼이 발생하여 훗날에 큰 문제 발생할 수 있음.
    *ptr = 0x12341234;
}