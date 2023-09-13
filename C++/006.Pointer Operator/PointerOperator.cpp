#include <iostream>
using namespace std;

struct Player
{
    int hp; //���� �޸�(������)
    int damage; //���� �޸�(������) + 4byte
};

int main()
{
    int number = 1;

    // 1) �ּ� ������
    // - �ش� ������ �ּҸ� �˷��ش�.
    // - �� ��Ȯ�� ���ϸ� �ش� �ڷ����� ���� TYPE* ��ȯ
    // &number�� �ּҴ� 0x0002�̴�
    int* pointer = &number;

    // 2) ��� ������ ( +, - )

    number += 1; // number = 2

    // int*
    // - * : ������ Ÿ���̴�.
    // - int : �ּҸ� ���󰡸� int���� �ִٰ� �����Ѵ�.
    // [!] �����Ϳ��� + �� - �� ��� �������� ���ϰų� ����, ���� ��ŭ ���ϰ� ����� �ǹ̰� �ƴϴ�.
    // �ڷ��� ũ�� ��ŭ �̵��Ѵ�.

    pointer += 1; 
    //pointer = 0x0003 ( X ) -> 0x0002 + 1
    //pointer = 0x0006 ( O ) -> 0x0002 + 4(1 * int, �ڷ��� ũ��) , ���� �޸𸮷� �̵���Ų��.


    // 3) ���� ������ (*)
    // - �ش� �ּҷ� �̵��Ѵ�.
    *pointer = 3; // ��� �����ڷ� �������� �ʾҴٸ�, number = 3

    // 4) ���� ��� ������ (->)
    Player player;
    player.hp = 100;
    player.damage = 10;

    Player* playerPtr = &player;
    (*playerPtr).hp = 200; //player.hp = 200
    (*playerPtr).damage = 20; //player.damage = 20
    
    // - *(���� ������) �� .(����ü�� Ư�� ����� �ٷ� �� ���, ������� ����ϸ� �����¿��� ������ŭ �� ��.)�� ��ģ ����
    playerPtr->hp = 200; //(*playerPtr).hp = 200
    playerPtr->damage = 20; //(*playerPtr).damage = 20

    return 0;
}