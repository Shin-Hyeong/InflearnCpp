#include <iostream>
using namespace std;
class Knight;

// 멤버 함수 포인터

// 함수 포인터
// 전역함수(함수 밖에 선언한 함수) / 정적 함수(static이 붙은 함수)만 담을 수 있음. 호출 규약이 동일한 함수
// 1) 포인터        *
// 2) 변수의 이름   fn
// 3) 타입          함수(인자로 int 2개, int를 반환)

// 방법 1)
// int (*fn)(int, int)

// 방법 2)
// typedef int(FUNC_TYPE)(int, int);
// FUNC_TYPE* fn;

// 일반적인 포인터 함수
typedef int(*PFUNC)(int, int);

// 멤버함수를 사용하기 위한 포인터 함수
typedef int(Knight::*PMEMFUNC)(int, int);

class Knight
{
public:

    // 위치만 class내에 있을뿐 class 내에 있는 변수를 사용할 수 없음
    static int HelloKnight(int a, int b)
    {
        return a;
    }

    // 멤버 함수
    int GetHp(int a, int b)
    {
        cout << "GetHp()" << endl;
        return _hp;
    }

public:
    int _hp;

};

// 전역 함수
int Test(int a, int b)
{
    return a + b;
}

int main ()
{
    PFUNC fn;
    // 전역함수 사용 가능. -> 특정 객체랑 상관없이 호출 가능
    fn = &Test;
    // 정적함수 사용가능
    fn = &Knight::HelloKnight;

    // 멤버함수는 사용할 수없음 -> 특정 객체만이 호출할 수 있음
    //fn = &Knight::GetHp;

    Knight k1;
    // 멤버함수를 사용할 수 있는 타입
    PMEMFUNC mfn;
    
    //Knight만 사용할수 있게됨.
    mfn = &Knight::GetHp;
    // mfn이 가지고 있는 주소로 k1의 객체를 이용해서 호출
    (k1.*mfn)(1,2);

    Knight* k2 = new Knight();
    // k2가 주소값을 가지고 있기 떄문에 *를 통해서 객체를 이용할수 있도록 한다.
    ((*k2).*mfn)(2, 3);

    //(*) + (.) = (->)
    (k2->*mfn)(3,4);

    delete k2;
    return 0;
}