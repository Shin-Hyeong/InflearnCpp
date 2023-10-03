#include <iostream>
using namespace std;

// str의 주소만 넘겨줄 수 있음.
void PrintStr(char* str)
{
    cout << str << endl;
}

// 4종류의 캐스팅 
// C언어에서 (int)float 형태를 활용도에 맞게 세분화시킨 느낌.

// 1) static_cast -> 빈도가 가장 높음
// 2) dynamic_cast -> 2번째 빈도를 가짐.
// 3) const_cast -> 거의 안씀
// 4) reinterpret_cast -> 완전 타입의 형변환이 필요할 때 사용.

class Player
{
public:
    // 다형성을 위해서 virtual를 사용하기도 함.
    virtual ~Player()
    {

    }
};
class Knight : public Player
{

};
class Archer : public Player
{

};

class Dog
{

};
int main ()
{
    // ! static cast : 타입 원칙에 비춰볼 때 상식적인 캐스팅만 허용해준다.
    // 1)  int <-> float (3 <-> 3.0)
    // 2) Player* -> Knight* (부모 class -> 자식 class, 다운 캐스팅) -> 안전성 보장 X
    
    int hp = 100;
    int maxHP = 200;
    // float ratio = (float)hp / maxHP; -> C언어에 가까운 문법
    float ratio = static_cast<float>(hp) / maxHP;   // C++에 더 친화적인 문법

    // 부모->자식, 암시적인 상황에선 위험함. Player가 Knight일지 Archer일지 모르는 상황
    // 상식적으로 Player가 Knight가 될순 있음. -> static_cast로 가능.
    // p의 원본은 Archer 상태임.
    Player* p = new Archer();
    Player* p1 = new Player();
    // Knight* k1 = (Knight*)p;
    // Archer인 p를 Knight를 캐스팅됨 -> 잘못된 캐스팅
    Knight* k1 = static_cast<Knight*>(p);

    // 자식->부모, 암시적인 상황에서도 안전한 상황
    Knight* k = new Knight();
    Player* p2 = k;

    // ! dynamic_cast : 상속관계에서의 안전한 형변환
    // RTTI(RunTime Type Information) -> virtual함수 생성시 생기는 정보를 관리함(실시간으로 관리)
    // 다형성을 활용하는 방식 -> 사용하기 위해선 virtual 함수를 생성해야함.
    // - virtual 함수를 하나라도 만들면, 객체의 메모리의 가상 함수 테이블(vftable) 주소가 기입된다.
    // - static_cast과 달리 가상 함수 테이블을 확인 후 맞는 타입인지 확인 후 캐스팅 해줌.
    // ! - 만약 잘못된 타입으로 캐스팅을 했으면, nullptr로 반환함
    // 이를 이용해서 맞는 타입으로 캐스팅을 했는지 확인을 유용함.
    // ? 가상 함수 테이블을 확인하는 과정이 추가되면서 static_cast보다 느림.
    // Archer를 원본을 가지고 있는 p를 Knight로 캐스팅 할려하면 nullptr 반환
    Knight* k2 = dynamic_cast<Knight*>(p);
    // Player를 원본을 가지고 있는 p를 Knight로 캐스팅 할려하면 변환됨.
    Knight *k3 = dynamic_cast<Knight *>(p2);

    // ! const_cast : const를 붙이거나 땔때 사용함.
    // 문자열은 const char[] 형태로 이기때문에 const를 없애고 보내줘야 한다.
    // PrintStr((char*)"string");
    // const char* -> char*
    PrintStr(const_cast<char*>("string"));

    // ! reinterpret_cast : 다시 - 간주하다/생각하다
    // 가장 위험하고 강력한 형태의 캐스팅
    // - 포인터랑 전혀 관계없는 다른 타입 변환 등
    // ? k2(pointer)를 address(int64)에 넣을려고함
    // __int64 address = (__int64)k2;
    __int64 address = reinterpret_cast<__int64>(k2);

    // Dog* dog1 = static_cast<Dog*>k2; -> 상관관계가 없으니 안됨.
    // Dog* dog1 = dynamic_cast<Dog*>k2; -> 가상 함수 관계가 안되기 때문에 안됨
    Dog* dog1 = reinterpret_cast<Dog*>(k2); // 아무런 관계가 없어도 됨.

    // 코드에서 사용되는 예
    void* pointer = malloc(1000);
    // Dog* dog2 = (Dog*)p;
    Dog* dog2 = reinterpret_cast<Dog*>(pointer);

    return 0;
}