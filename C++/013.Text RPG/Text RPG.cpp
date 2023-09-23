#include <iostream>
#include <ctime>
using namespace std;

// main
// - EnterLobby (PlayerInfo)
// -- CreatePlayer
// -- EnterGame (MonsterInfo)
// --- CreateMonsters
// --- EnterBattle

enum PlayerType
{
    PT_Knight = 1,  // 전사
    PT_Archer = 2,  // 궁수
    PT_Mage = 3,    // 마법사
};

enum MonsterType
{
    MT_Slime = 1,   // 슬라임
    MT_Orc = 2,     // 오크
    MT_Skeleton = 3,    // 스켈레톤
};

struct StatInfo
{   
    int hp = 0;         // 체력
    int attack = 0;     // 공격력
    int defense = 0;    // 방어력
};

void EnterLobby();
void PrintMessage(const char* msg);     // const char* : 문자열 타입
void CreatePlayer(StatInfo* playerInfo);
void PrintStatInfo(const char* name, const StatInfo& info);     // StatInfo의 내용을 수정하지 못하도록 const를 붙임.
void EnterGame(StatInfo* playerInfo);
void CreateMonsters(StatInfo monsterInfo[], int count);
bool EnterBattle(StatInfo* playerInfo, StatInfo* monsterInfo);

int main ()
{
    srand((unsigned)time(nullptr));     // 랜덤 시드 생성 , nullptr = 0; NUll = 0
    EnterLobby();

    cout << "Test2" << endl;

    return 0;
}

void EnterLobby()
{
    while (true)
    {
        PrintMessage("로비에 입장했습니다");

        // Player
        StatInfo playerInfo;
        CreatePlayer(&playerInfo);  // playerInfo는 EnterLobby 지역변수임으로 밖으로 가지고 나가면 안됨.
        PrintStatInfo("Player", playerInfo);

        EnterGame(&playerInfo);
    }
}

void PrintMessage(const char* msg) 
{
    //cout << "**********************\n";
    cout << msg << "\n";
    cout << "**********************\n" << endl;
}

void CreatePlayer(StatInfo *playerInfo)
{
    bool ready = false;

    while(ready == false)
    {
        PrintMessage("캐릭터 생성창");
        cout << "[1] 기사 [2] 궁수 [3] 법사" << endl << "> ";

        int input;
        cin >> input;

        switch (input)
        {
        case PT_Knight:
            cout << "기사를 생성하였습니다.\n";
            playerInfo->hp = 100;
            playerInfo->attack = 10;
            playerInfo->defense = 5;
            ready = true;
            break;
        case PT_Archer:
            cout << "궁수를 생성하였습니다.\n";
            playerInfo->hp = 80;
            playerInfo->attack = 15;
            playerInfo->defense = 3;
            ready = true;
            break;
        case PT_Mage:
            cout << "마법사를 생성하였습니다.\n";
            playerInfo->hp = 50;
            playerInfo->attack = 25;
            playerInfo->defense = 1;
            ready = true;
            break;
        }
    }
}

void PrintStatInfo(const char *name, const StatInfo &info)
{
    cout << name << " : HP = " << info.hp << " ATK = " << info.attack << " DEF = " << info.defense << "\n";
    cout << "**********************\n" << endl;
}

void EnterGame(StatInfo *playerInfo)
{
    const int MONSTER_COUNT = 2;
    PrintMessage("게임에 입장했습니다");

    while(true)
    {   
        // monsterInfo를 EnterGame 함수 밖으로 가지고 나가면 안됨.
        StatInfo monsterInfo[MONSTER_COUNT];    // 몬스터를 2마리 생성
        CreateMonsters(monsterInfo, MONSTER_COUNT);

        for (int i = 0; i < MONSTER_COUNT; i++)
            PrintStatInfo("Monster", monsterInfo[i]);

        PrintMessage("[1] 1번 몬스터와 전투 [2] 2번 몬스터와 전투 [3] 도망");

        int input;
        cin >> input;

        if (input == 1 || input == 2)
        {   
            int index = input - 1;
            bool victory = EnterBattle(playerInfo, &monsterInfo[index]);
            if (victory == false)
                break;
        }
        else if(input == 3)
            return;
    }
}

void CreateMonsters(StatInfo monsterInfo[], int count)
{
    for (int i = 0; i < count; i++)
    {
        int randValue = 1 + rand() % 3;     // 몬스터 랜덤 생성

        switch (randValue)
        {
        case MT_Slime :
            cout << "슬라임이 나타났습니다.\n";
            monsterInfo[i].hp = 30;
            monsterInfo[i].attack = 5;
            monsterInfo[i].defense = 1;
            break;
        case MT_Orc :
            cout << "오크가 나타났습니다.\n";
            monsterInfo[i].hp = 40;
            monsterInfo[i].attack = 8;
            monsterInfo[i].defense = 2;
            break;
        case MT_Skeleton :
            cout << "스켈레톤이 나타났습니다.\n";
            monsterInfo[i].hp = 50;
            monsterInfo[i].attack = 15;
            monsterInfo[i].defense = 3;
            break;
        }
    }
}

bool EnterBattle(StatInfo *playerInfo, StatInfo *monsterInfo)
{
    while (true)
    {   
        /* 플레이어의 공격 */
        int damage = playerInfo->attack - monsterInfo->defense;     // 플레이어의 데미지 계산
        if (damage < 0)
            damage = 0;
        
        monsterInfo->hp -= damage;  // 몬스터에게 피해량 계산
        if (monsterInfo->hp < 0)
            monsterInfo->hp = 0;
        
        PrintStatInfo("Monster", *monsterInfo); // 몬스터의 상태 표시

        if (monsterInfo->hp == 0)
        {
            PrintMessage("몬스터를 처치했습니다");
            return true;
        }

        /* 몬스터의 공격 */
        damage = monsterInfo->attack - playerInfo->defense;     // 몬스터의 데미지 계산
        if (damage < 0)
            damage = 0;

        playerInfo->hp -= damage;   // 플레이어에게 피해량 계산
        if (playerInfo->hp < 0)
            playerInfo->hp = 0;

        PrintStatInfo("Player", *playerInfo);       // 플레이어의 상태 표시

        if (playerInfo->hp == 0)
        {
            PrintMessage("Game Over");
            return false;
        }
    }
}