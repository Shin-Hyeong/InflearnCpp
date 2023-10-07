#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Field.h"
using namespace std;

Game::Game() : _player(nullptr), _field(nullptr)
{

}

Game::~Game()
{
    // Game이 종료되면 player 삭제
    if (_player != nullptr)
        delete _player;

    // Game이 종료되면 field 삭제
    if (_field != nullptr)
        delete _field;
}

void Game::Init()
{
    _field = new Field;
}

void Game::Update()
{
    if (_player == nullptr)
        CreatePlayer();

    if (_player->IsDead())
    {
        delete _player;
        _player = nullptr;
        CreatePlayer();
    }

    // field에서 Monster와 Player가 싸울 수 있도록 Player의 주소를 넘김.
    _field->Update(_player);
}

void Game::CreatePlayer()
{
    while (_player == nullptr)
    {
        cout << "-------------------------------------" << endl;
        cout << "캐릭터를 생성하세요!" << endl;
        cout << "1) 기사 2) 궁수 3) 법사" << endl;
        cout << "-------------------------------------" << endl << "> ";

        int input = 0;
        cin >> input;

        if (input == PT_Knight)
        {
            _player = new Knight();
        }
        else if (input == PT_Archer)
        {
            _player = new Archer();
        }
        else if (input = PT_Mage)
        {
            _player = new Mage();
        }
    }
}
