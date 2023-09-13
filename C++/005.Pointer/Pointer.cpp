#include <iostream>
using namespace std;

void SetHp(int* hp);

int main ()
{   
    int number = 1;
    //number는 메모리 0x!!!에 저장됨.

    // TYPE* 변수이름;
    int* ptr = &number;
    // &number : number 변수의 주소를 가져옴.
    //int* ptr : 주소를 저장하는 변수
    //자료형 타입이랑 상관없이 *이 붙으면 실행되는 프로그램에 맞추어 크기가 변한다
    //x86 : 32bit (4byte),  x64 : 64bit (8byte)

    //4byte or 8byte의 크기를 가지지만 자료형을 붙이는 이유
    //해당 주소로 가서 값을 어느형태로 받아야하는지 (어느 형태로 있는지) 추가 정보를 줌.
    //number이 int형이면 int* ptr
    //number가 float형이면 float* ptr

    //x86에서 number가 int형이고 __int64* ptr일때
    //__int64* ptr = &number을 하면 오류남.
    //__int64* ptr = (__int64*)&number로 강제로 넣을 수있음.
    //*ptr에 number의 주소가 들어감.
    //*ptr = 0xAABBCCDDEEFF;
    //number의 크기인 4byte를 넘는 값이 들어와서 할당된 범위를 넘어감.
    //number 메모리 [CCDDEEFF], number + 4byte 메모리 [0000AABB]
    //number + 4byte 메모리가 중요한 값을 가진 메모리였다면 치명적 오류 발생.


    //*ptr에 number의 메모리 주소 0x!!!을 저장함.
    //*ptr = 0x!!!

    int value1 = *ptr;
    //*ptr이 가지고 있는 주소로 가서 값을 value1에 저장
    //value1 = 1

    *ptr = 2;
    //*ptr이 가지고 있는 주소로 가서 값을 2로 변경.
    //number = 2;

    int hp = 10;
    cout << "Before SetHp : " << hp << "\n"; //Before SetHp : 10
    SetHp(&hp);
    cout << "After SetHp : " << hp << endl; //After SetHp  : 100

    return 0;
}

void SetHp(int* hp)
{
    *hp = 100;
}