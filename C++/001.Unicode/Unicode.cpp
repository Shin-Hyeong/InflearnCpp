#include <iostream>
using namespace std;

int main()
{
    char ch = 'a';
    // wchar_t wch = L'안';
    // 인코딩이 UFT-8 or UFT-16이여야함.
    // 문자앞에 L를 붙여줘야함

    cout << ch << endl;
    // cout는 char 전용

    // wcout.imbue(locale("kor"));
    //  유니코드에서 한국어라는 인식시킴
    // wcout << wch << endl;

    return 0;
}