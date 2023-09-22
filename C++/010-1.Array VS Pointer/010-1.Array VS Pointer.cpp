#include <iostream>
using namespace std;

// 배열은 함수 인자로 넘기면, 컴파일러가 알아서 포인터로 치환한다(Char[] -> char*)
// 즉 배열의 내용 전체를 넘기는게 아니라, 시작주소(포인터)만 넘긴다.
void Test(char a[])
{
    a[0] = 'x';
}

int main()
{
    // 문자열 = 문자 배열
    "Hello World"; // -> const char*[12] 형태를 가짐.
    // test1 : 포인터 변수(8Byte)
    // .data 영역 / 시작주소 [H][e][l][l][o][][W][o][r][l][d][\0]
    // test1는 시작주소를 가짐.
    const char* test1 = "Hello World";

    // test2 : char형 배열(12byte)
    // .data 영역 / 배열 시작 주소 [H][e][l][l][o][][W][o][r][l][d][\0]
    // test2 주소 [][][][][][][][][][][][]
    // 4Byte씩 나누어서 test2배열에 저장됨.
    // [H][e][l][l][][][][][][][][]
    // [H][e][l][l][o][][W][o][][][][]
    // [H][e][l][l][o][][W][o][r][l][d][\0]
    char test2[] = "Hello World"; 
    // test2는 test3와 같다고 볼 수 있다.
    char test3[] = {'H','e','l','l','o',' ','W','o','r','l','d','\0'};

    // [R][e][l][l][o][][W][o][r][l][d][\0]
    // 실질적인 데이터 수정 가능.
    test2[0] = 'R';

    // 문자열의 주소를 가지고 있기 때문에 test1[0] = 'R'으로 수정 불가능.

    // 문자열 : .data 영역에 있는 문자열의 주소로 가서 문자열을 읽음.
    // 배열 : .data 영역에 있는 문자들을 배열 메모리에 저장함.

    // 배열을 함수의 매개변수로 넘기면?
    // 배열의 내용이 바뀜.
    Test(test2);

    //xello World
    cout << test2 << endl;


    return 0;
}