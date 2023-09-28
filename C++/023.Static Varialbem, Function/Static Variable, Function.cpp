#include <iostream>
using namespace std;

// 1) struct와 class의 차이
// - struct는 기본 접근 지정자가 public이고, class는 private이다.
// - C++는 C언어에서 파생되어 발전되었기 떄문에 C언어랑 어느정도 호환성을 염두한다.
// -> struct는 그냥 구조체(데이터 묶음)을 표현하는 용도
// -> class는 객체 지향 프로그래밍의 특징을 나타내는 용도

struct TestStruct
{
    int _a;
    int _b;
};

class TestClass
{
    int _a;
    int _b;
};

// 2) static 변수와, static 함수 (static = 정적 = 고정된)

class Marine
{
public:
    // 멤버함수 : 사용하기 위해선 class객체를 붙여서 사용해야함.
    void TakeDamage(int damage)
    {
        _hp -= damage;
    }
    
    // Marine의 종속적인 변수를 건들수 없게됨. -> _hp는 건들 수 없다.
    // s_attack은 건들 수 있음.
    // 특정 객체와 관련된 함수도 호출할 수 없게됨. -> TakeDamage 호출 불가능
    static void SetAttack(int attack)
    {
        s_attack = attack;
    }

public:
    // 각각의 마린 객체에 종속됨.
    int _hp;

    // class Marine에게 종속되어서 모든 마린 객체에 일괄적으로 적용됨.
    // 전역 변수 취급됨.
    static int s_attack;    // 설계도 상에서만 존재.
};

// ? static 변수는 메모리 어디에 저장되나
// - 초기화되어 있으면 .data
// - 초기돠 안 하면 .bss
// - 함수 내에서 생성되어도 stack에서 저장되지 않고 data 영역에 저장됨.
// - 생명주기 : 프로그램 시작 / 종료 (메모리에 항상 올라가 있음)
// - 가시범위
// -- 정적 전역 변수 : 함수 밖에 선언하여서 모든 함수가 사용할 수 있음
// -- 정적 지역 변수 : 선언한 함수 내에서만 사용할 수 있음.
// --- static int s_id = 1;
// --- s_id를 처음 볼떄만 초기화하기 떄문에 매번 1로 초기화하지 않음.
int Marine::s_attack = 0; // static 변수 초기화.

int test()
{
    static int num1;
}
static int num2;

int main ()
{

    // Struct VS Class

    TestStruct ts;
    // struct는 접근 지정자가 지정되어 있지 않으면 public으로 디폴트로 되어 있음.
    ts._a = 1;

    TestClass tc;
    // class는 접근 지정자가 지정되어 있지 않으면 private로 디폴트로 되어 있음.
    // tc._a = 1;


    // static 변수, static 함수
    // s_attack = 6으로 기본 공격력 설정.
    Marine::s_attack = 6;

    Marine m1;
    m1._hp = 35;
    // 멤버 함수 호출
    m1.TakeDamage(10);
    // m1.s_attack = 6;

    Marine m2;
    m2._hp = 14;
    // 멤버 함수 호출
    m2.TakeDamage(5);
    // m2.s_attack = 6;

    // 공격력 업그레이드 후
    // 생성된 Marine마다 일일히 공격력 업그레이드를 수치 변경
    // m1.s_attack = 7;
    // m2.s_attack = 7;
    // static 변수를 이용하여 일괄적으로 처리 가능.
    Marine::s_attack = 7;

    // Marine내에 있는 static 함수 호출
    Marine::SetAttack(8);

    return 0;
}