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
    // TYPE �̸�[����];
    // �迭�� ũ��� ��������Ѵ� (Visual Studio �����Ϸ� ����)
    // VScode�� ����� �ƴϿ��� ������ ����.
    int monsterCount = 10;
    StatInfo monsters[monsterCount];
    
    // ������ ���� = ����  �ű� �� ����
    int a = 10;
    int b = a;

    // �迭�� ���� = ���� �ű� �� ����.
    // StatInfo player[10];
    // players = monsters; -> �Ұ���.

    // �迭�� �̸��� ����?
    auto WhatIsIt = monsters;
    // WhatIsIt�� StatInfo* WhatIsIt ���¸� ������ ����.
    // monsters�� Ư�� ���� ������ �ִ� ���� �ƴϰ� �迭�� ���� �ּҸ� ����.
    // ��Ȯ���� ���� ��ġ�� ����Ű�� TYPE* ������ ����
    
    /* �������� ���� */
    // StatInfo[] StatInfo[] StatInfo[] StatInfo[] StatInfo[]
    StatInfo* monster_0 = monsters;
    // monster_0[] StatInfo[] StatInfo[] StatInfo[] StatInfo[]
    monster_0->hp = 100;
    monster_0->attack = 10;
    monster_0->defense = 1;
    // monster_0[(100, 10, 1)] StatInfo[] StatInfo[] StatInfo[] StatInfo[]

    // �������� ������ ��¥ �� ���� ���ϴ� ���� �ƴ϶� StatInfo Ÿ�� ��ŭ �̵��ϴ� �ǹ�
    // monster_0[(100, 10, 1)] monster_1[] StatInfo[] StatInfo[] StatInfo[]
    StatInfo* monster_1 = monsters + 1;
    monster_1->hp = 200;
    monster_1->attack = 20;
    monster_1->defense = 2;
    // monster_0[(100, 10, 1)] monster_1[(200, 20, 2)] StatInfo[] StatInfo[] StatInfo[]

    // �ּ� ���ް� ���� ������ ��ȯ �����ϴ�.
    // monster_0[(100, 10, 1)] monster_1[(200, 20, 2)] StatInfo[] StatInfo[] StatInfo[]
    StatInfo& monster_2 = *(monsters + 2);
    // monster_0[(100, 10, 1)] monster_1[(200, 20, 2)] monster_2[] StatInfo[] StatInfo[]
    monster_2.hp = 300;
    monster_2.attack = 30;
    monster_2.defense = 3;
    // monster_0[(100, 10, 1)] monster_1[(200, 20, 2)] monster_2[(300, 30, 3)] StatInfo[] StatInfo[]

    // [����] &���̷� ���� �ٸ� �ǹ̰� �� �� �ִ�.
    // monster_0[(100, 10, 1)] monster_1[(200, 20, 2)] monster_2[(300, 30, 3)] StatInfo[] StatInfo[]
    StatInfo temp = *(monsters + 2);
    // temp [(300, 30, 3)]
    temp.hp = 400;
    temp.attack = 40;
    temp.defense = 4;
    // monster_0[(100, 10, 1)] monster_1[(200, 20, 2)] monster_2[(300, 30, 3)] StatInfo[] StatInfo[]
    // temp [(400, 40, 4)]
    // �迭�� ���빰�� ������� ������ StatInfo ����ü�� ���� �����͸� �������� ����.
    
    // �ڵ�ȭ�� �迭�� ������ ä���
    for (int i = 0; i < monsterCount; i++)
    {
        StatInfo& monster = *(monsters + i);
        monster.hp = 100 * (i + 1);
        monster.attack = 10 * (i + 1);
        monster.defense = (i + 1);
    }
    // *(monsters + i) �ʹ� �����ϰ� �������� ������.
    // �ε����� ����Ѵ�. �迭�� 0������ �����Ѵ�. N��° �ε����� �ش��ϴ� �����Ϳ� �����Ϸ��� �迭�̸�[N]
    // *(monsters + i) = monsters[i]

    for (int i = 0; i < monsterCount; i++)
    {
        monsters[i].hp = 100 * (i + 1);
        monsters[i].attack = 10 * (i + 1);
        monsters[i].defense = (i + 1);
    }

    int hp = monsters[3].hp; // hp = 400

    // �迭�� �ʱ�ȭ ����
    // ���� �������� �迭�� �ʱ�ȭ ���� ������ �����Ⱚ�� ����.
    // 1) 0���� �ʱ�ȭ �ϱ�
    int numbers[5] = {}; // {0, 0, 0, 0, 0}
    // 2) �迭�� �Ϻθ� �ʱ�ȭ �ϱ�
    int numbers_1[10] = { 1, 2, 3, 4, 5}; // {1, 2, 3, 4, 5, 0, 0, 0, 0, 0}
    // 3) �ʱ�ȭ�� ũ��� �迭 �����
    int numbers_2[] = { 1, 2, 3, 4}; // numbers_2[4] 
    // 3) 3���� ����
    char helloStr[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
    cout << helloStr << endl;

    return 0;
}