#include <iostream>
using namespace std;

int main()
{
    char ch = 'a';
    wchar_t wch = L'��';
    // UFT-8 or UFT-16���� L�� �ٿ������

    cout << ch << endl;
    // cout�� char ����

    wcout.imbue(locale("kor"));
    // �����ڵ忡�� �ѱ����� �νĽ�Ŵ
    wcout << wch << endl;

    return 0;
}