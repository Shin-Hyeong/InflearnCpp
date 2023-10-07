#include "Creature.h"

void Creature::OnAttacked(Creature* attacker)
{   
    // 공격자의 공격력 - 나의 방어력
    int damage = attacker->_attack - _defense;
    if (damage < 0)
        damage = 0;

    _hp -= damage;
    if (_hp < 0)
        _hp = 0;
}