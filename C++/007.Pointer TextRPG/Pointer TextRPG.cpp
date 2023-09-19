#include <iostream>
using namespace std;

struct StatInfo
{
    int hp;         // +0
    int attack;     // +4
    int defence;    // +8
};

void EnterLobby();
StatInfo CreatePlayer();                // 포인터 사용 X
void CreateMonster(StatInfo* Info);     // 포인터 사용 O
bool StartBattle(StatInfo* player, StatInfo* monster);  //플레이어가 승리시 true, 패배시 false

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    EnterLobby();

    return 0;
}

void EnterLobby()
{
    cout << "로비에 입장했습니다\n";

    StatInfo player;

    // 임시로 player에 쓰레기값을 넣음.
    player.hp = 0xbbbbbbbb;
    player.attack = 0xbbbbbbbb;
    player.defence = 0xbbbbbbbb;

    player = CreatePlayer(); //플레이어 정보를 리턴 받음

    // 컴파일러가 메모리에서 하는 작업.
    // [매개변수(temp)][반환값][지역변수(ret)]
    // 메모리에서 임시로 매개변수 &temp(쓰레기 값을 가짐.)를 생성함.
    // 함수에서 지역 변수 ret(100, 10, 2) 값을 가짐.
    // 지역 변수 ret의 값을 매개변수 temp로 옮겨 받음.
    // 함수 밖으로 나오면서 매개변수 temp에서 값을 가져와서 player에 옮겨짐.
    // 사실상 StatInfo temp = CreatePlayer();
    // player = temp;를 하고 있는 셈.
    // 지역변수(ret) -> 매개변수(temp) -> 변수(player)
    // 수백개의 멤버변수가 있다면 상당한 메모리 낭비를 야기 할 수 있다.

    StatInfo monster;

    // 임시로 monster에 쓰레기값을 넣음.
    monster.hp = 0xbbbbbbbb;
    monster.attack = 0xbbbbbbbb;
    monster.defence = 0xbbbbbbbb;

    CreateMonster(&monster); //monster의 주소를 보내 함수에서 세팅됨.

    // 컴파일러가 메모리에서 하는 작업
    // 스택에 monster 시작 주소(hp)를 스택에 저장함.
    // 함수에서 hp는 시작 주소의 메모리에서 직접적으로 값을 넣음.
    // attack은 hp의 주소 + 4(int)의 메모리에 직접적으로 값을 넣음.
    // defence는 hp의 주소 + 8(attack + 4)의 메모리에 직접적으로 값을 넣음.
    // 멤버변수가 많아도 메모리 낭비가 적음.

    /* 구조체끼리 복사할 때 어떻게 복사 할까 */
    // player = monster;
    // monster의 주소를 eax(레지스터)에 저장
    // eax의 값을 player 주소의 값에 넣음.
    // player.hp = monster.hp
    // 이와 같은 작업을 반복함.
    // 사실상 player.hp = monster.hp
    // player.attack = monster.attack
    // player.defence = monster.defence
    // 멤버변수가 많을수록 메모리 낭비가 될 수 있음.

    bool victory = StartBattle(&player, &monster);

    if (victory)
        cout << "승리!\n";
    else
        cout << "패배\n";
}

StatInfo CreatePlayer()
{
    StatInfo ret; //반환해줘야할 StatInfo 구조체형

    ret.hp = 100;
    ret.attack = 10;
    ret.defence = 2;

    return ret;
}

void CreateMonster(StatInfo *Info)
{
    cout << "몬스터 생성\n";

    Info->hp = 40;
    Info->attack = 8;
    Info->defence = 1;
}

bool StartBattle(StatInfo* player, StatInfo* monster)
{
    while (true)
    {
        int damage = player->attack - monster->defence;
        if (damage < 0)
            damage = 0;

        monster->hp -= damage;
        if (monster->hp < 0)
            monster->hp = 0;
        
        cout<< "몬스터 HP : " << monster->hp << "\n";

        if (monster->hp == 0)
            return true; //플레이어 승리
        
        damage = monster->attack - player->defence;
        if (damage < 0)
            damage = 0;
        
        cout << "플레이어 HP : " << player->hp << "\n";

        player->hp -= damage;
        if (player->hp < 0)
            player->hp = 0;
        
        if (player->hp == 0)
            return false; //플레이어 패배 
    }
}