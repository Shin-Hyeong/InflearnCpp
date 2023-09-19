#include <iostream>
using namespace std;

enum ENUM_TEST
{
    ENUM_ONE = 1,
    ENUM_TWO = 2,
    ENUM_THREE //전 열거형의 + 1
};
//열거형은 메모리에 저장되지 않고 입력된 수로 컴파일 과정에서 대체된다.
//const와 같이 상수를 만드는데 사용할 수 있다.
//const는 상황에 따라 메모리에 저장될때 있다.
//코드의 가독성이 높아짐.

int main () {

    cout << "ENUM_ONE : " << ENUM_ONE << endl;         // ENUM_ONE : 1
    cout << "ENUM_TWO : " << ENUM_TWO << endl;         // ENUM_TWO : 2
    cout << "ENUM_THREE : " << ENUM_THREE << endl;     // ENUM_THREE : 3

    //ENUM_THREE = 5; -> 3 = 5

    ENUM_TEST ENUM_ONE = static_cast<ENUM_TEST>(5);     // 강제 변환

    cout << "After ENUM_ONE : " << ENUM_ONE << endl;    // After ENUM_ONE : 5

    return 0;
}