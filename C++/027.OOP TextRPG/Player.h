#pragma once
#include "Creature.h"

enum PlayerType
{
    PT_Knight = 1,
    PT_Archer = 2,
    PT_Mage = 3
};

class Player : public Creature
{
public:
    // 헤더파일에선 선언만 하고 구현은 .cpp 파일에서 하는 것이 좋다
    // 단, 내용이 적으면 헤더에서 해도 상관없다.
    // Player를 생성하면 _CreatureType에 CT_PlAYER를 넣음
    Player(int playerType) : Creature(CT_PLAYER), _playerType(playerType)
    {

    }

    // 소멸자를 virtual로 생성하여 원본에 맞는 소멸자를 호출시킴.
    virtual ~Player()
    {

    }
    virtual void PrintInfo();

protected:
    int _playerType;

};

class Knight : public Player
{   
public:
    // Knight를 생성하면 _playerType에 PT_Knight를 넣음
    Knight() : Player(PT_Knight)
    {
        _hp = 150;
        _attack = 10;
        _defense = 5;
    }
};

class Archer : public Player
{
public:
    // Archer를 생성하면 _playerType에 Archer를 넣음
    Archer() : Player(PT_Archer)
    {
        _hp = 80;
        _attack = 15;
        _defense = 3;
    }
};

class Mage : public Player
{
public:
    // Mage를 생성하면 _playerType에 Mage를 넣음
    Mage() : Player(PT_Mage)
    {
        _hp = 50;
        _attack = 25;
        _defense = 1;
    }
};