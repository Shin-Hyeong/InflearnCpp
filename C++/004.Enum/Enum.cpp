#include <iostream>
using namespace std;

enum ENUM_TEST
{
    ENUM_ONE = 1,
    ENUM_TWO = 2,
    ENUM_THREE //�� �������� + 1
};
//�������� �޸𸮿� ������� �ʰ� �Էµ� ���� ������ �������� ��ü�ȴ�.
//const�� ���� ����� ����µ� ����� �� �ִ�.
//const�� ��Ȳ�� ���� �޸𸮿� ����ɶ� �ִ�.
//�ڵ��� �������� ������.

int main () {

    cout << "ENUM_ONE : " << ENUM_ONE << endl;         // ENUM_ONE : 1
    cout << "ENUM_TWO : " << ENUM_TWO << endl;         // ENUM_TWO : 2
    cout << "ENUM_THREE : " << ENUM_THREE << endl;     // ENUM_THREE : 3

    //ENUM_THREE = 5; -> 3 = 5

    ENUM_TEST ENUM_ONE = static_cast<ENUM_TEST>(5);     // ���� ��ȯ

    cout << "After ENUM_ONE : " << ENUM_ONE << endl;    // After ENUM_ONE : 5

    return 0;
}