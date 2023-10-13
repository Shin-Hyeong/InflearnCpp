#include <iostream>
using namespace std;

// 연산자 오버로딩(Operator Overloading)
// 연산자 함수를 정의해야 함.
// 함수도 멤버함수, 전역함수(일반함수)가 존재하는 것 처럼, 연산자 함수도 두가지 방식으로 만들 수 있다.

// 멤버 연산자 함수
// - A op B 형태에서 왼쪽을 기준으로 실행됨 (A가 class여야 가능. A를 '기준 연산자' 라고 함. B는 class가 아니여도 상관없음)
// 단점) A가 class가 아니면 사용 못함.

// 전역 연산자 함수
// - A ob B 형태라면, A, B 모두를 연산자 함수의 피연산자로 만들어준다.
// - 대입연산자(a = b)는 전역 연산자으로는 못 만든다.
// -- (a = b)는 b가 a에게 값을 주는 형태인데 연산자 오버로딩을 통해서 a가 b에게 값을 넘기는 상황을 방지하기 위해

// 복사 대입 연산자
// - 복사 대입 연산자 = 대입 연산자 중, 자기 자신의 참조 타입을 인자로 받는 것

// 모든 연산자를 오버로딩 할 수 있는 것은 아니다(:: .  .*)
// 모든 연산자가 다 2개 항을 가지고 있는 것이 아니다 (++ --, 단항 연산자)
// 증감 연산자 함수
// - 전위형 ++a -> operator++()
// - 후위형 a++ -> operator++(int)

class Position
{
public:
    // 함수 생성방법 : 반환값 함수명(매개변수)
    // 연산자 함수생성 방법 : 반환값 operator(연산자함수를 만들)연산자 (매개변수)
    Position operator+(const Position& arg)
    {
        Position pos;
        pos._x = _x + arg._x;
        pos._y = _y + arg._y;
        return pos;
    }

    Position operator+(int arg)
    {
        Position pos;
        pos._x = _x + arg;
        pos._y = _y + arg;
        return pos;
    }

    bool operator==(const Position& arg)
    {
        return (_x == arg._x) && (_y == arg._y);
    }

    // 연산자 '=' 는 멤버 연산자 함수에서만 오버로딩 가능함.
    // 멤버 연산자 함수는 void형태보다 자신 class의 주소를 반환해주는 형태가 좋다.
    Position& operator=(int arg)
    {
        _x = arg;
        _y = arg;

        // this은 Position* this = 자신의 주소로 이루어진 포인터 변수
        // *this를 통해 자신의 주소로 이동하여 값을 반환함.
        return *this;
    }

    // 복사 대입 생성자
    // 해당 객체가 복사되길 원함.
    Position& operator=(Position& arg)
    {
        _x = arg._x;
        _y = arg._y;

        return *this;
    }

    // ++a
    // ++a -> OK
    // ++(++a) -> OK
    // ++(++a)이 되는 것은 (++a)의 반환값이 자기자신을 참조를 반환해줌 -> Position&
    Position& operator++()
    {   
        _x++;
        _y++;

        return *this;
    }

    // a++
    // a++ -> OK
    // (a++)++ -> No
    // (a++)++이 안되는 것 (a++)가 복사된 값을 반환해주기 때문 -> Position
    // Position&를 붙이면 ret가 값을 복사해서 전달하는게 아니라 주소를 넘기게 됨.
    // 주소는 지역변수이기 때문에 operator++를 벗어나는 순간 사라짐.
    Position operator++(int)
    {
        // pos2 = pos1++
        // pos2에게 값을 건내주기 전에 값을 건드면 안됨.
        // ret에 건내줄 값을 저장함.
        Position ret = *this;
        // pos1은 값을 변경함
        _x++;
        _y++;
        // 변경하지 않음 값을 반환함.
        return ret;
    }

public:
    int _x;
    int _y;

};

// 전역 연산자 함수
Position operator+(int a, const Position& b)
{
    Position ret;

    ret._x = b._x + a;
    ret._y = b._y + a;
    
    return ret;
}

int main()
{
    Position pos;
    pos._x = 1;
    pos._y = 1;

    Position pos2;
    pos2._x = 2;
    pos2._y = 2;

    // 일반적으로 Position + Position를 할수 없음
    // 멤버 연산자 함수 operator+(const Postion& arg)를 사용
    Position pos3 = pos + pos2;
    // pos3 = pos.operator+(pos2);

    // 멤버 연산자 함수 operator+(int arg)를 사용
    Position pos4 = pos3 + 1;
    // pos4 = pos.operator+(1);
    // Postion pos4 = 1 + pos3; -> 왼쪽 피연산자가 class가 아니여서 실행 안됨.

    // 전역 연산자 함수를 사용하여 연산함.
    // 전역 연산자 함수 operator+(int a, const Position& b)
    Position pos5 = 1 + pos4;

    // Postion == Postion은 안되는 형태이지만 연산자 함수를 정의하여서 사용자가 원하는 형태로 정의할 수 있다.
    // 멤버 연산자 함수 operator==(const Position& arg)를 사용
    bool isSame = (pos3 == pos4);

    Position pos6;
    // 멤버 변수 함수 operator= 를 사용함.
    pos6 = 5;
    // Position pos6 = 5;와 다른 개념 -> 생산자를 호출하는 것. Position(int a)형태의 생성자를 찾아서 호출함

    // pos6 = 5는 반환값이 void여도 실행됨. 반값값을 void형태로 받음
    // pos3 = (pos6 = 5)는 실행 되지 않음. (pos6 = 5)가 void형태이기 때문에 operator=(int arg)에 인자값이 맞지 않음.
    // Position& operator=(int arg) 형태로 반환값을 변경하면 실행된다
    pos3 = (pos6 = 5);

    return 0;
}