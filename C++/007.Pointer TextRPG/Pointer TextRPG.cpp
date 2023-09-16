#include <iostream>
using namespace std;

struct StatInfo
{
    int hp;         // +0
    int attack;     // +4
    int defence;    // +8
};

void EnterLobby();
StatInfo CreatePlayer();                // ������ ��� X
void CreateMonster(StatInfo* Info);     // ������ ��� O
bool StartBattle(StatInfo* player, StatInfo* monster);  //�÷��̾ �¸��� true, �й�� false

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    EnterLobby();

    return 0;
}

void EnterLobby()
{
    cout << "�κ� �����߽��ϴ�\n";

    StatInfo player;

    // �ӽ÷� player�� �����Ⱚ�� ����.
    player.hp = 0xbbbbbbbb;
    player.attack = 0xbbbbbbbb;
    player.defence = 0xbbbbbbbb;

    player = CreatePlayer(); //�÷��̾� ������ ���� ����

    // �����Ϸ��� �޸𸮿��� �ϴ� �۾�.
    // [�Ű�����(temp)][��ȯ��][��������(ret)]
    // �޸𸮿��� �ӽ÷� �Ű����� &temp(������ ���� ����.)�� ������.
    // �Լ����� ���� ���� ret(100, 10, 2) ���� ����.
    // ���� ���� ret�� ���� �Ű����� temp�� �Ű� ����.
    // �Լ� ������ �����鼭 �Ű����� temp���� ���� �����ͼ� player�� �Ű���.
    // ��ǻ� StatInfo temp = CreatePlayer();
    // player = temp;�� �ϰ� �ִ� ��.
    // ��������(ret) -> �Ű�����(temp) -> ����(player)
    // ���鰳�� ��������� �ִٸ� ����� �޸� ���� �߱� �� �� �ִ�.

    StatInfo monster;

    // �ӽ÷� monster�� �����Ⱚ�� ����.
    monster.hp = 0xbbbbbbbb;
    monster.attack = 0xbbbbbbbb;
    monster.defence = 0xbbbbbbbb;

    CreateMonster(&monster); //monster�� �ּҸ� ���� �Լ����� ���õ�.

    // �����Ϸ��� �޸𸮿��� �ϴ� �۾�
    // ���ÿ� monster ���� �ּ�(hp)�� ���ÿ� ������.
    // �Լ����� hp�� ���� �ּ��� �޸𸮿��� ���������� ���� ����.
    // attack�� hp�� �ּ� + 4(int)�� �޸𸮿� ���������� ���� ����.
    // defence�� hp�� �ּ� + 8(attack + 4)�� �޸𸮿� ���������� ���� ����.
    // ��������� ���Ƶ� �޸� ���� ����.

    /* ����ü���� ������ �� ��� ���� �ұ� */
    // player = monster;
    // monster�� �ּҸ� eax(��������)�� ����
    // eax�� ���� player �ּ��� ���� ����.
    // player.hp = monster.hp
    // �̿� ���� �۾��� �ݺ���.
    // ��ǻ� player.hp = monster.hp
    // player.attack = monster.attack
    // player.defence = monster.defence
    // ��������� �������� �޸� ���� �� �� ����.

    bool victory = StartBattle(&player, &monster);

    if (victory)
        cout << "�¸�!\n";
    else
        cout << "�й�\n";
}

StatInfo CreatePlayer()
{
    StatInfo ret; //��ȯ������� StatInfo ����ü��

    ret.hp = 100;
    ret.attack = 10;
    ret.defence = 2;

    return ret;
}

void CreateMonster(StatInfo *Info)
{
    cout << "���� ����\n";

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
        
        cout<< "���� HP : " << monster->hp << "\n";

        if (monster->hp == 0)
            return true; //�÷��̾� �¸�
        
        damage = monster->attack - player->defence;
        if (damage < 0)
            damage = 0;
        
        cout << "�÷��̾� HP : " << player->hp << "\n";

        player->hp -= damage;
        if (player->hp < 0)
            player->hp = 0;
        
        if (player->hp == 0)
            return false; //�÷��̾� �й� 
    }
}