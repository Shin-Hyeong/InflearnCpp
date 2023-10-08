#include "Archer.h"
#include "Pet.h"

Archer::Archer(Pet* pet) : _pet(pet)
{
	
}

Archer::Archer(int hp) : Player(hp)
{
}

Archer::~Archer()
{
	if (_pet != nullptr)
		delete _pet;
}

void Archer::AddHp(int value)
{
	Player::AddHp(value);

	if (IsDead())
	{
		delete _pet;
		
		// _pet가 가지고 있는 주소를 없애야함.
		_pet = nullptr;
	}
}
