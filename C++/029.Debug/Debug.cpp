#include <iostream>
using namespace std;

// 디버깅
// 코드 하나씩 실행시키기 : F11 -> 함수 내부로 들어감
// 다음 프로시저(함수)까지 실행시키기 : F10 -> 함수 내부로 안들어감
// 다음 BreakPoint 까지 실행시키기 : F5

void Test2()
{
    int b = 0;
}

void Test1()
{
    int a = 5;

    // 특정 상황일 때 BreakPoint 활성화하기 -> BreakPoint에 +표시 생김
    // BreakPoint을 우클릭 - Edit BreakPoint - Expression - 원하는 조건이 참일때 BreakPoint 활성화

    // BreakPoint에서 로그(Debug Console) 출력하기 -> BreakPoint가 네모로 변함
    // 로그를 출력하게 만들면 멈추지 않고 로그만 남기고 통과된다.
    // BreakPoint을 우클릭 - Edit BreakPoint - Log Message  - 원하는 Log 입력
    Test2();
}

int main ()
{
    int number = 10;
    Test1();

    int* pointer;

    return 0;
}