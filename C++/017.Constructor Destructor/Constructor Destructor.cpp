#include <iostream>
using namespace std;

// ! 생성자(Constructor)와 소멸자(Destructor)
// 클래스에 소속된 함수들을 멤버 함수라고 한다.
// 이 중에서 굉장히 특별한 함수 2종이 있는데, 바로 [시작]과 [끝]을 알리는 함수들
// - 시작(탄생) -> 생성자, 여러개 존재 가능
// - 끝(소멸) -> 소멸자, 오직 1개만

// 암시적(Implicit) 생성자
// 생성자를 명시적으로 만들지 않으면, 아무 인자도 받지 않는 [기본 생성자]가 컴파일러에 의해 자동으로 만들어짐.
// 그러나 우리가 명시적(Explicit)으로 아무 생성자 하나 만들면,
// 자동으로 만들어지던 [기본 생성자]는 더 이상 만들어지지 않음.
// 다른 유형의 생성자가 있다면 기본 생성자를 명시적으로 생성해줘야함.

class Knight
{
public:
    int _hp;
    int _attack;
    int _posY;
    int _posX;
public:
    // [1] 기본 생성자 (인자가 없음) -> Knight가 호출될 떄 무조건 한번 실행됨.
    // Knight가 메모리에 올라가는 순간 호출됨.
    Knight()
    {
        cout << "Knight() 기본 생성자 호출" << endl;
        _hp = 100;
        _attack = 10;
        _posY = 0;
        _posX = 0;
    }

    // [2] 매개변수를 받는 일반[기타] 생성자
    // 이 중에서 인자를 1개만 받는 일반[기타] 생성자를 [타입 변환 생성자]라고 부르기도 함
    // 암시적 형변환 -> 컴파일러가 알아서 바꿔치기
    // int num = 1;
    // float f = (float)num; (명시적 버전 : 코드로 num을 float형태로 넣으라고 명령함)
    // float ff = num; (암시적 버전 : 별도로 명령하지 않았지만 컴파일러가 알아서 처리함.)
    // Knight K9;
    // Knight = 1;
    // 암시적으로 형변환이 되어 Knight(int hp)를 불러오고 1은 매개변수 hp에 넣어짐.
    // 암시적으로 형변환이 이루어지지 않도록하기 위해서 생성자 앞에 explicit를 넣어준다

    // 명시적인 용도로만 사용
    explicit Knight(int hp)
    {
        cout << "Knight(int) 생성자 호출" << endl;
        _hp = hp;
        _attack = 10;
        _posY = 0;
        _posX = 0;
    }

    Knight(int hp, int attack, int posY, int posX)
    {
        cout << "Knight(int, int, int, int) 생성자 호출" << endl;
        _hp = hp;
        _attack = attack;
        _posY = posX;
        _posX = posX;
    }

    // [3] 복사생성자 -> 자기 자신의 클래스 참조 타입을 인자로 받음
    // 일반적으로 똑같은 데이터를 가진 객체가 생성할려고 사용함.
    Knight(const Knight& knight)
    {   
        cout << "Knight(const Knight& knight) 복사 생성자 호출" << endl;
        _hp = knight._hp;
        _attack = knight._attack;
        _posY = knight._posY;
        _posX = knight._posX;
    }
    
    // 소멸자 -> Knight가 사라질 때(소멸될 때) 호출된다.
    // return 0 다음 Knight가 메모리에서 삭제되는 순간 호출됨.
    ~Knight()
    {
        cout << "~Knight 소멸자 호출" << endl;
    }

    void Move(int y, int x);
    void Attack();
    void Die()
    {
        _hp = 0;
        cout << "Die" << endl;
    }
};

void Knight::Move(int y, int x)
{
    _posY = y;
    _posX = x;
}

void Knight::Attack()
{
    cout << "Attack : " << _attack << endl;
}

int main()
{
    // 기본 생성자 호출
    Knight K0;

    // 매개변수를 받는 생성자 호출
    Knight K1(90);
    Knight K2(80, 5, 1, 1);

    // 복사생성자 호출
    Knight K3(K1);
    Knight K4 = K1;

    // 기본 생성자로 K5를 생성한 이후에 K5의 멤버 변수에 K1 멤버 변수를 넣는다.
    Knight K5;
    K5 = K1;

    K1.Move(2,2);
    K1.Attack();
    K1.Die();

    return 0;
}