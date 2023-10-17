#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// enum class (scoped enum)
// Modern C++ (C++11 이후 문법)

// enum : 열거형
// 기본 enum 사이즈 : 4byte
// unscoped enum (범위없는) -> 같은 이름(PT_Knight, PT_Archer, PT_Mage)을 다른 곳에서 사용못함
enum PlayerType : char // char -> PlayerType 사이즈를 1byte 형태로 변경
{
    PT_Knight,
    PT_Archer,
    PT_Mage
};

// enum class
// 1) 이름공간 관리 (scoped)
// 2) 암묵적인 변환 금지

// enum class 안에서만 유효함.
enum class ObjectType1
{
    Player,
    Monster,
    Projectile
};

enum class ObjectType2
{
    Player,
    Monster,
    Projectile
};

int main ()
{   
    // value에 0값 넣음
    double value = PT_Knight;

    // 암묵적 변환금지
    // int p1 = ObjectType1::Player;

    // 명시적으로는 변환 가능.
    int p1 = static_cast<int>(ObjectType1::Player);
    int p2 = static_cast<int>(ObjectType2::Player);

    // 변환금지의 단점
    int choice = 2;
    // if (choice == ObjectType1::Monster) -> 안됨
    // 귀찮아짐.
    if (choice == static_cast<int>(ObjectType1::Monster))
    {

    }

    unsigned int bitFlag;                                       // 0000 0000
    bitFlag = (1 << 2);                                         // 0000 0100
    bitFlag = (1 << PT_Knight);                                 // 0000 0001
    bitFlag = (1 << static_cast<int>(ObjectType1::Monster));    // 0000 0010


    return 0;
}