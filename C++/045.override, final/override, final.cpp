#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// override(virtual과 함께 사용), final
// Modern C++ (C++11 이후 문법)

class Player
{
public:
    // 객체의 본체에 맞게 Attack함수를 호출할 수 있도록 virtual를 붙임
    // 부모에서 virtual를 붙이면 상속받는 자식들은 자동으로 virtual이 적용됨.
    virtual void Attack()
    {
        cout << "Player!" << endl;
    }

    virtual void Defense()
    {
        cout << "Player!" << endl;
    }
};

class Knight : public Player
{
public:
    // 재정의(override)
    // 부모에서 virtual를 적용해서 안써도 되지만 가상함수라는것을 가시성있게 확인할 수 있게 적는다.
    // virtual를 붙이면 해당 함수가 가상함수가 시작하는 함수인지 아닌지 확인이 어려움
    // ! override : 부모로부터 받은 함수를 재정의 했다는것을 명시적으로 표시
    virtual void Attack() override
    {
        cout << "Knight!" << endl;
    }

    // ! final : 자식 class에서 재정의(override) 하는 것을 막음.
    virtual void Defense() final
    {
        cout << "Knight!" << endl;
    }
};

int main ()
{
    Player* player = new Knight();
    player->Attack();

    return 0;
}