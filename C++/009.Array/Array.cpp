#include <iostream>
using namespace std;

struct StatInfo
{
    int hp = 0xAAAAAAAA;
    int attack = 0xBBBBBBBB;
    int defense = 0xDDDDDDDD;
};

int main ()
{
    // TYPE 이름[개수];
    // 배열의 크기는 상수여야한다 (Visual Studio 컴파일러 기준)
    // VScode는 상수가 아니여도 컴파일 가능.
    const int monsterCount = 10;
    StatInfo monsters[monsterCount];

    // 변수는 값을 = 으로  옮길 수 있음
    int a = 10;
    int b = a;

    // 배열은 값을 = 으로 옮길 수 없다.
    // StatInfo player[10];
    // players = monsters; -> 불가능.

    // 배열의 이름은 뭔가?
    auto WhatIsIt = monsters;
    // WhatIsIt는 StatInfo* WhatIsIt 형태를 가지고 있음.
    // monsters는 특정 값을 가지고 있는 것이 아니고 배열의 시작 주소를 가짐.
    // 정확히는 시작 위치를 가르키는 TYPE* 포인터 변수
    
    /* 포인터의 덧셈 */
    // StatInfo[] StatInfo[] StatInfo[] StatInfo[] StatInfo[]
    StatInfo* monster_0 = monsters;
    // monster_0[] StatInfo[] StatInfo[] StatInfo[] StatInfo[]
    monster_0->hp = 100;
    monster_0->attack = 10;
    monster_0->defense = 1;
    // monster_0[(100, 10, 1)] StatInfo[] StatInfo[] StatInfo[] StatInfo[]

    // 포인터의 덧셈은 진짜 그 수를 더하는 것이 아니라 StatInfo 타입 만큼 이동하는 의미
    // monster_0[(100, 10, 1)] monster_1[] StatInfo[] StatInfo[] StatInfo[]
    StatInfo* monster_1 = monsters + 1;
    monster_1->hp = 200;
    monster_1->attack = 20;
    monster_1->defense = 2;
    // monster_0[(100, 10, 1)] monster_1[(200, 20, 2)] StatInfo[] StatInfo[] StatInfo[]

    // 주소 전달과 참조 전달은 변환 가능하다.
    // monster_0[(100, 10, 1)] monster_1[(200, 20, 2)] StatInfo[] StatInfo[] StatInfo[]
    StatInfo& monster_2 = *(monsters + 2);
    // monster_0[(100, 10, 1)] monster_1[(200, 20, 2)] monster_2[] StatInfo[] StatInfo[]
    monster_2.hp = 300;
    monster_2.attack = 30;
    monster_2.defense = 3;
    // monster_0[(100, 10, 1)] monster_1[(200, 20, 2)] monster_2[(300, 30, 3)] StatInfo[] StatInfo[]

    // [주의] &차이로 완전 다른 의미가 될 수 있다.
    // monster_0[(100, 10, 1)] monster_1[(200, 20, 2)] monster_2[(300, 30, 3)] StatInfo[] StatInfo[]
    StatInfo temp = *(monsters + 2);
    // temp [(300, 30, 3)]
    temp.hp = 400;
    temp.attack = 40;
    temp.defense = 4;
    // monster_0[(100, 10, 1)] monster_1[(200, 20, 2)] monster_2[(300, 30, 3)] StatInfo[] StatInfo[]
    // temp [(400, 40, 4)]
    // 배열의 내용물과 상관없이 별도의 StatInfo 구조체를 만들어서 데이터를 가져오는 것임.
    
    // 자동화로 배열의 내용을 채우기
    for (int i = 0; i < monsterCount; i++)
    {
        StatInfo& monster = *(monsters + i);
        monster.hp = 100 * (i + 1);
        monster.attack = 10 * (i + 1);
        monster.defense = (i + 1);
    }
    // *(monsters + i) 너무 불편하고 가독성이 떨어짐.
    // 인덱스를 사용한다. 배열은 0번부터 시작한다. N번째 인덱스에 해당하는 데이터에 접근하려면 배열이름[N]
    // *(monsters + i) = monsters[i]

    for (int i = 0; i < monsterCount; i++)
    {
        monsters[i].hp = 100 * (i + 1);
        monsters[i].attack = 10 * (i + 1);
        monsters[i].defense = (i + 1);
    }

    int hp = monsters[3].hp; // hp = 400

    // ! 배열의 초기화 문법
    // 지역 변수에서 배열을 초기화 하지 않으면 쓰레기값을 가짐.
    // 1) 0으로 초기화 하기
    int numbers[5] = {}; // {0, 0, 0, 0, 0}
    // 2) 배열의 일부만 초기화 하기
    int numbers_1[10] = { 1, 2, 3, 4, 5}; // {1, 2, 3, 4, 5, 0, 0, 0, 0, 0}
    // 3) 초기화한 크기로 배열 만들기
    int numbers_2[] = { 1, 2, 3, 4}; // numbers_2[4] 
    // 3) 3번의 응용
    char helloStr[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
    cout << helloStr << endl;

    return 0;
}