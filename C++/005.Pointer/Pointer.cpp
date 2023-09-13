#include <iostream>
using namespace std;

void SetHp(int* hp);

int main ()
{   
    int number = 1;
    //number�� �޸� 0x!!!�� �����.

    // TYPE* �����̸�;
    int* ptr = &number;
    // &number : number ������ �ּҸ� ������.
    //int* ptr : �ּҸ� �����ϴ� ����
    //�ڷ��� Ÿ���̶� ������� *�� ������ ����Ǵ� ���α׷��� ���߾� ũ�Ⱑ ���Ѵ�
    //x86 : 32bit (4byte),  x64 : 64bit (8byte)

    //4byte or 8byte�� ũ�⸦ �������� �ڷ����� ���̴� ����
    //�ش� �ּҷ� ���� ���� ������·� �޾ƾ��ϴ��� (��� ���·� �ִ���) �߰� ������ ��.
    //number�� int���̸� int* ptr
    //number�� float���̸� float* ptr

    //x86���� number�� int���̰� __int64* ptr�϶�
    //__int64* ptr = &number�� �ϸ� ������.
    //__int64* ptr = (__int64*)&number�� ������ ���� ������.
    //*ptr�� number�� �ּҰ� ��.
    //*ptr = 0xAABBCCDDEEFF;
    //number�� ũ���� 4byte�� �Ѵ� ���� ���ͼ� �Ҵ�� ������ �Ѿ.
    //number �޸� [CCDDEEFF], number + 4byte �޸� [0000AABB]
    //number + 4byte �޸𸮰� �߿��� ���� ���� �޸𸮿��ٸ� ġ���� ���� �߻�.


    //*ptr�� number�� �޸� �ּ� 0x!!!�� ������.
    //*ptr = 0x!!!

    int value1 = *ptr;
    //*ptr�� ������ �ִ� �ּҷ� ���� ���� value1�� ����
    //value1 = 1

    *ptr = 2;
    //*ptr�� ������ �ִ� �ּҷ� ���� ���� 2�� ����.
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