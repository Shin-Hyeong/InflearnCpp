#include <iostream>
using namespace std;

struct Player
{
    int hp; //시작 메모리(오프셋)
    int damage; //시작 메모리(오프셋) + 4byte
};

int main()
{
    int number = 1;

    // 1) 주소 연산자
    // - 해당 변수의 주소를 알려준다.
    // - 더 정확히 말하면 해당 자료형에 따라서 TYPE* 반환
    // &number의 주소는 0x0002이다
    int* pointer = &number;

    // 2) 산술 연산자 ( +, - )

    number += 1; // number = 2

    // int*
    // - * : 포인터 타입이다.
    // - int : 주소를 따라가면 int형이 있다고 가정한다.
    // [!] 포인터에서 + 나 - 등 산술 연산으로 더하거나 빼면, 숫자 만큼 더하고 빼라는 의미가 아니다.
    // 자료형 크기 만큼 이동한다.

    pointer += 1; 
    //pointer = 0x0003 ( X ) -> 0x0002 + 1
    //pointer = 0x0006 ( O ) -> 0x0002 + 4(1 * int, 자료형 크기) , 다음 메모리로 이동시킨다.


    // 3) 간접 연산자 (*)
    // - 해당 주소로 이동한다.
    *pointer = 3; // 산술 연산자로 변경하지 않았다면, number = 3

    // 4) 간접 멤버 연산자 (->)
    Player player;
    player.hp = 100;
    player.damage = 10;

    Player* playerPtr = &player;
    (*playerPtr).hp = 200; //player.hp = 200
    (*playerPtr).damage = 20; //player.damage = 20
    
    // - *(간접 연산자) 과 .(구조체의 특정 멤버를 다룰 때 사용, 어셈블리로 계산하면 오프셋에서 순서만큼 더 함.)를 합친 형태
    playerPtr->hp = 200; //(*playerPtr).hp = 200
    playerPtr->damage = 20; //(*playerPtr).damage = 20

    return 0;
}