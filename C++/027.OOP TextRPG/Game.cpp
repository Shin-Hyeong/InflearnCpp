#include <iostream>
#include "Game.h"
#include "Player.h"
using namespace std;

Game::Game() : _player(nullptr)
{

}

Game::~Game()
{

}

void Game::Init()
{
    
}

void Game::Update()
{
    if (_player == nullptr)
        CreatePlayer();
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
