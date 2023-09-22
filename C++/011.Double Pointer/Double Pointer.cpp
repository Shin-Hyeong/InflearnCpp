#include <iostream>
using namespace std;

void SetMessageByPtr(const char* a) // 
{
    // .data 영역에 Bye주소 [B][y][e][\0]를 생성함.
    // 매개변수 a에 Bye주소를 넣음.
    a = "Bye";

    // 매개변수가 const이기 때문에 변경 불가능.
    // *a = "Bye";
}
// 함수가 끝나면서 매개변수 a는 소멸됨.
// msg에 돌아온 것이 없음.

void SetMessageByDPtr(const char** a) // (const char*)* a
{
    *a = "Double Point Function"; // a가 가지고 있는 Bye주소 -> Double Point Function 주소로 변경.
}

void SetMessageByPtrRef(const char*& a)
{
    a = "Point Reference Fuction";
}

int main()
{
    // .data 영역    Hello주소 [H][e][l][l][o][\0]
    // msg[ Hello주소 ] << 8Byte
    const char* msg = "Hello";

    // msg는 Hello주소를 가지고 있음.
    // SetMessageByPtr의 매개변수 a에 Hello 주소를 넣어줌.
    SetMessageByPtr(msg);

    cout << msg << endl; // Hello

    // const char** pp;
    // (const char*)*pp (8 Byte) : 주소를 따라가면 const char* 형태가 있을 것으로 예상되는 변수의 주소를 가짐.
    // const char* (8 Byte) : 주소를 따라가면 char 형태로 있을 것으로 예상되는 변수의 주소를 가짐.
    // char (1 Byte)

    // 간략 설명
    // pp[ 주소 1 ]
    // 주소1 [ 주소 2 ]
    // 주소2 [  ]

    const char** pp = &msg; // msg는 무조건 const char* 형태여야 함.
    *pp = "Bye"; // msg가 가지고 있는 주소를 Bye 주소로 변경함. Hello 주소 -> Bye주소

    cout << msg << endl; // Bye

    // SetMessageByDPtr의 매개변수 a에  msg의 주소를 보냄.
    SetMessageByDPtr(&msg);

    cout << msg << endl; // Double Point Function
    // 이중 포인터 : const로 상수화 된 원본을 수정하기 할 때 사용됨.

    // 다중 포인터는 양파까기와 비슷하다.
    // const char** : *를 하나씩 까면서 타고 이동하면 된다.
    // const char** -> const char* -> const char

    // 참조 전달도 같이 사용할 수 있다.
    // SetMessageByPtrRef의 매개변수 a에 msg의 주소를 보냄.
    SetMessageByPtrRef(msg); // SetMessageByPtrRef(const char*& a)
    cout << msg << endl;     // Point Reference Fuction

    return 0;
}