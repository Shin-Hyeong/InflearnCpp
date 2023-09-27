#include <iostream>
using namespace std;

// 다형성 : 겉은 똑같은데, 기능이 다르게 작동한다.
// - 오버로딩(OverLoading) = 함수를 중복 정의 = 함수 이름 재사용
// - 오버라이딩(Overriding) = 재정의 = 부모 클래스의 함수를 자식 클래스에서 재정의

// 부모(Player)는 자식(Knight & Mage)의 인자에 들어갈 수 없다.
// 자식(Knight & Mage)은 부모(Player)의 인자에 들어갈 수 있다.

// 바인딩(Binding) : 묶는다.
// - 정적 바인딩(Static Binding) : 컴파일 시점에 결정
// ! -  동적 바인딩(Dynamic Binding) : 실행 시점에 결정, 면접 단골 질문

// 일반 함수는 정적 바인딩을 사용함.
// ! 동적 바인딩을 원한다면 -> 가상 함수 (virtual function)을 사용한다.

// 순수 가상 함수 : 구현은 없고 '인터페이스'만 전달하는 용도로 사용하고 싶은 경우
// 순수 가상 함수를 1개 이상 만드는 순간 그 class는 추상 클래스가 된다.
// - 직접적으로 객체를 만들 수 없게 됨.

class Player
{
public:

    Player()
    {   
        // ! 가상함수 테이블에 Player 가상함수 주소를 채워 넣음.
        _hp = 100;
    }

    void Move() {cout << "Move Player !" << endl;}

    // ! 가상함수를 사용하기 위해서 함수 앞에 virtual를 붙여줘야한다.
    virtual void VMove() { cout << "VMove Player !" << endl; }

    virtual void VDie() { cout << "VDie Player !" << endl; }

    // 순수 가상 함수 -> 선언은 Player에서 하지만 실질적 구현 내용은 상속받는 자식이 구현해야함.
    // (virtual) + (= 0)가 해당 가상함수는 순수 가상 함수이다.를 명시
    // 모던 C++ 에서는 = 0 대신 abstract;를 붙임
    virtual void VAttack() = 0;

    // Move의 오버로딩
    void Move(int a) { cout << "Move Player(int " << a << ")!" << endl;}

public:
    int _hp ;
};

class Knight : public Player
{
public:
    Knight()
    {
        // ! 가상함수 테이블에 Knight 가상함수 주소를 채워 넣음.
        _stamina = 100;
    }

    // Move의 오버라이딩
    void Move() { cout << "Move Knight !" << endl; }

    virtual void VDie() { cout << "VDie Knight !" << endl; }

    // ! 가상 함수는 재정의를 하더라도 가상 함수이다. 
    // ! 자식이 가상함수를 제거하기 위해서 virtual를 없애도 실질적으로 virtual이 붙어있다.
    virtual void VMove() { cout << "VMove Knight !" << endl; }

    virtual void VAttack() { cout << "VAttack Knight" << endl; }

public:
    int _stamina;

};

class Mage : public Player
{
public:


public:
    int _mp;

};

// 일반 함수는 정적 바인딩을 호출함
// 컴파일을 하여 해당 Move는 Player에게 있는 Move를 호출하는 것으로 바인딩함.
// 나중에 실행 시켰을 때 Knight가 들어와도 Player의 Move를 호출하게 되는 것.

// ! 가상함수를 호출하면 이제 동적 바인딩으로 적용되어 들어오는 인자값에 맞는 함수를 호출함.
// ! 메모리상에서 player인자가 호출되면 인자가 가지고 있는 가상함수 주소를 타고 가서 그에 맞는 함수를 호출한다.
void MovePlayer(Player* player)
{
    player->VMove();
}

void MoveKnight(Knight* knight)
{
    knight->Move();
}

int main()
{   
    // 추상 클래스가 되었기 때문에 별도로 사용할 수없음.
    // Player p;
    // MovePlayer(&p); // Move Player !
    // 부모(Player)는 자식(Knight & Mage)의 인자에 들어갈 수 없다.
    // 부모(Player)는 자식중에 Knight가 될수도 있고 Mage가 될수도 있기 때문이다.
    // MoveKnight(&p); // Error

    //p.Move();   // Move Player !
    //p.VMove(10); // Move Player(int 10) !

    // ! 가상함수를 생성하면 Knight를 생성하는 과정에서 메모리에 가상 함수 테이블 (가상함수를 찾는 값)이 생김.
    // ! 가상 함수 테이블에는 자신이 가지고 있는 가상함수(VMove)의 주소를 가지고 잇다.
    // ! [VMove][VDie][V...][_hp(100)][_stamina(100)]
    // ! 가상함수 주소를 채우는 역할은 class의 생성자가 함.
    Knight K;
    MoveKnight(&K); // Move Knight !

    // Knight에서 Move를 오버라이딩 했지만 Player의 Move가 호출됨.
    // 이는 바인딩과 관련된 내용이다.
    // 자식(Knight & Mage)은 부모(Player)의 인자에 들어갈 수 있다.
    MovePlayer(&K); // Move Player !

    //K.Move();   // Move Knight !

    return 0;
}