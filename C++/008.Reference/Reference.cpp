#include <iostream>
using namespace std;

// Point* : ����Ʈ ����
// *point : point�� ������ �ִ� �ּҷ� �̵��Ѵ�.

// Reference& : ���� ����
// &reference : reference������ �ּҸ� �����´�.

struct StatInfo
{
    int hp;
    int attack;
    int defense;
};

void CreateMonster(StatInfo *Info)
{
    Info->hp = 40;
    Info->attack = 8;
    Info->defense = 1;
}

// 1) �� ���� ���
// ���� �������� �ʴ´ٸ�, ���� �� �ϴ� ���� ����.
// �޸𸮻󿡼��� �Ű����� info�� ������ �������� info�� �����ؼ� �����ؼ� ����Ѵ�.
void PrintInfoByCopy(StatInfo info)
{   
    cout << "Copy-----------------------" << endl;
    cout << "HP  : " << info.hp << endl;
    cout << "ATK : " << info.attack << endl;
    cout << "DEF : " << info.defense << endl;
    cout << "---------------------------" << endl;
}

// 2) �ּ� ���� ���
// �޸𸮻󿡼��� �Ű������� �ּҰ��� ���������� �޾Ƽ� �ּҿ��� ���� �����´�.
void PrintInfoByPtr(StatInfo* info)
{
    cout << "Ptr------------------------" << endl;
    cout << "HP  : " << info->hp << endl;
    cout << "ATK : " << info->attack << endl;
    cout << "DEF : " << info->defense << endl;
    cout << "---------------------------" << endl;
}

// 3) ���� ���� ���
// �޸𸮻󿡼��� �Ű������� �ּҰ��� ���������� �޾Ƽ� �ּҿ��� ���� �����´�.
void PrintInfoByRef(StatInfo& info)
{
    cout << "Ref------------------------" << endl;
    cout << "HP  : " << info.hp << endl;
    cout << "ATK : " << info.attack << endl;
    cout << "DEF : " << info.defense << endl;
    cout << "---------------------------" << endl;
}

// StatInfo ����ü�� 1000Byte¥�� ���� ����ü���?
// - �� ���� : StatInfo�� �ѱ�� 1000Byte�� ����Ǵ� ��Ȳ �߻�
// - �ּ� ���� : StatInfo*�� �ü���� ����ؼ� ����(�ּ� ����Ʈ ũ��, x86 : 4Byte, x64 : 8Byte)
// - ���� ���� : StatInfo&�� �ü���� ����ؼ� ����(�ּ� ����Ʈ ũ��, x86 : 4Byte, x64 : 8Byte)

// ���� ���� ����ϴ� ����
// 1) info->hp ���� info.hp�� �� ��뼺�� ����.
// 2) �� ���޺��� �ּ� ������ �޸𸮸� ������ �� �ִ�.
// �� ����ó�� ��뼺 �ְ� �ڵ��ϰ�, �ּ� ����ó�� �ּҰ��� �̿��� �޸𸮸� �����ϴ� ���

// ���� ���� vs �ּ� ����
// 1) ���Ǽ� ����
// ���� ������ ���Ǽ��� ���ٴ� ���� �� ������ �ִ°� �ƴϴ�.
// �����ʹ� �ּҸ� �ѱ�� Ȯ���ϰ� ������ �ѱ�ٴ� ��Ʈ�� �� �� �ִ�.
// ������ �� ���ް� ����ϰ� ����� ������ �𸣰� ����ĥ �� ����.
// �� ����   : PrintInfo(info)
// ���� ���� : PrintInfo(info)

// ���� ������ ����ؼ� �ǵ�ġ �ʰ� ������ ���� �����ϴ� ���� �߻��� �� ����.
// �Ű������� const�� �ٿ��� �Լ������� ���� ���ϴ°� ������ �� ����.
// void PrintInfo(const StatInfo& info)

// �ּ� ���������� const�� ��� ����.
// *�� �������� �տ� ���̴���, �ڿ� ���̴��Ŀ� ���� �ǹ̰� �޶�����.

// info [ �ּҰ� ]          �ּҰ� [ ������ ]
// (const StatInfo* info) or (StatInfo const* info)
// �ּ� ���� ������ �ִ� �����͸� �����ϴ� ���� ������.
// �ּ� ���� ����Ǵ� ���� ���� ����.

// (StatInfo* const info)
// �Ű������� ������ �ִ� �ּҰ��� ����Ǵ°��� ������.
// �ּ� ���� ������ �ִ� �����͸� �����ϴ� ���� ���� ����.

// (const StatInfo* const info)
// �Ѵ� ����Ͽ� �ּҰ��� ������ �� �� ���� ���� ���ϵ��� �����.

// 2) �ʱ�ȭ ����
// ���� ������ �����ϴ� ����� �����ؾ� �Ѵ�.
// �ּ� ������ � �ּҸ� �ǹ��ϱ� ������ �ּҿ� ����� �������� ���� ���� ����.

// �ּ� ����
// StatInfo* testPtr;
// PrintInfoByPtr(testPtr);
// testPtr�� ����ü ���� ��� ���� ���� ����.
// �����ͺ����� �ƹ��͵� ����Ű�� ������ nullptr�� �־��ش�.
// StatInfo* testPtr = nullptr;
// ���� : nullptr�� �̿��Ͽ� ���ϴ� ã�� ������Ʈ�� �ּҰ� ���� �� nullptr�� ��ȯ�Ͽ� ��� ����.
// ���� : nullptr���� �ּҸ� �������� �ϸ� �����Ϸ��� ������ �������� �� ��ȿ���� �ʾ� ���� ó����.
// �����͸� ����ϸ� nullptr�� ���� ������ 80%�̻��� ������ ����.
// if(info == nullptr) return;�� ����Ͽ� null crash error�� ������� ���� ����.

// ���� ����
// StatInfo& testRef;
// PrintInfoByRef(testRef);
// testRef�� ������ �������� �𸣱� ������ ���� ��.
// StatInfo& testRef = info;
// PrintInfoByRef(testRef);
// testRef�� info�� �����ϵ��� ������. testRef�� info�� 2��° �̸�.
// ���� : ������ ������ ���� �����ϱ� ������ null crash error�� ���� �� ����.
// ���� : ���ϴ� �ּҰ��� ���� �� nullptr(��ȿ�� ���� �ƴ�.)�� �� �� ����.

// �ּҷ� ����ϴ��� ������ �Ѱ��ٷ���?
// pointer[ �ּ�(&info) ]     Ref, info[ ������ ]
// PrintInfoByRef(pointer);
// pointer�� �ּҸ� ������ �ֱ� ������ pointer�� ������ �ִ� �ּҷ� �̵����Ѿ� ��.
// PrintInfoByRef(*pointer);

// ������ ����ϴ��� �ּҷ� �Ѱ��ٷ���?
// pointer[ �ּ�(&info) ]      reference, info[ ������ ]
// PrintInfoByPtr(reference);
// reference�� �����͸� ����Ű�� �ֱ� ������ &�� �ٿ� �ּҸ� ����Ű���� �Ѵ�.
// PrintInfoByPtr(&reference);

// ���
// Team by Team -> ��� ����ϴ��Ŀ��� ���� �ٸ�.
// Google Open Source ������ ������ ������ ���
// Unreal Engine������ reference�� �����.

// - ���� ��ȿ���� ���� ��쵵 ����ؾ� �Ѵٸ� pointer (null üũ �ʼ�)
// - �ٲ��� �ʰ� �д� �뵵(ReadOnly)�� ����ϸ� const ref&
// - �� �� �Ϲ������� ref (��������� ���� ����� �� �ִ� �Լ��� ȣ���� �� OUT�� ���δ�.)
// #define OUT
// StatInfo ChangeInfo(OUT StatInfo& info);
// ChangeInfo(OUT info);
// OUT�� �ƹ� �͵� �������� �ʾұ� ������ �ƹ��� �ǹ� ���� ������� �ǹ̸� ����.
// -- ��, �ٸ� ����� pointer�� �������� �� �̾ ����ٸ�, ��� pointer�� �̿��Ѵ�.
// StatInfo ChangeInfo(StatInfo* info1, StatInfo* info2) ( O )
// StatInfo ChangeInfo(StatInfo* info1, StatInfo& info2) ( X )

int main()
{
    StatInfo info;
    CreateMonster(&info);
    
    // �� ����
    PrintInfoByCopy(info);

    // �ּ� ����
    PrintInfoByPtr(&info);

    // ���� ����
    PrintInfoByRef(info);

    // ���� ���� ����
    // 4Byte ���������� ������ number��� �̸��� �����ش�.
    // number���� �� �����ų�, �� �ִ´ٸ� �ش� �ּ�(data or stack or heap)�� ���� ������ �ȴ�.
    int number = 1;

    // * �ּҸ� ��� ����
    // �ش� �ּҸ� ���󰡸� int �����Ͱ� ����.
    int* pointer = &number;
    // pointer ������ �ִ� �ּҸ� Ÿ�� �̵��ؼ� �� ������ 2�� �ִ´�.
    *pointer = 2;

    int& reference = number;
    // ����� �������� ���� �۵��� �����Ϳ� �Ȱ���.
    // ������ �����ϸ� �����Ϸ��� �����Ϳ� ���� �����Ѵ�.

    // C++ ���������� number��� �ٱ��Ͽ� �� �ٸ� �̸��� �ο��� ��.
    // number��� �ٱ��Ͽ� reference��� �ٸ� �̸��� �����ش�.
    // reference�� �� �����ų� ������ ���� number�� �� ���� �����ų� �ִ°Ͱ� ����.
    reference = 3;

    return 0;
}