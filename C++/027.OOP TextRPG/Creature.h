#pragma once

enum CreatureType
{
    CT_PLAYER = 0,
    CT_MONSTER = 1
};

class Creature
{
public:
    Creature(int creatureType) 
        : _creatureType(creatureType), _hp(0), _attack(0), _defense(0)
    {

    }

    virtual ~Creature()
    {

    }

    // = 0 -> 추상함수로 만듦 -> 상속받는 모든 class는 PrintInfo를 재정의 해줘야함.
    virtual void PrintInfo() = 0;

    // 자신이 공격 받는 함수, 매개변수는 나를 공격하는 대상
    void OnAttacked(Creature* attacker);

    // 죽었는지 확인
    bool IsDead() { return _hp <= 0; }

protected:
    int _creatureType;
    int _hp;
    int _attack;
    int _defense;
};