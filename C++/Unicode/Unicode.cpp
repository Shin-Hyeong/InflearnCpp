#include <iostream>
using namespace std;

int main()
{
    char ch = 'a';
    //wchar_t wch = L'��';
    //���ڵ��� UFT-8 or UFT-16�̿�����.
    //���ھտ� L�� �ٿ������

    cout << ch << endl;
    // cout�� char ����

    //wcout.imbue(locale("kor"));
    // �����ڵ忡�� �ѱ����� �νĽ�Ŵ
    //wcout << wch << endl;

    return 0;
}