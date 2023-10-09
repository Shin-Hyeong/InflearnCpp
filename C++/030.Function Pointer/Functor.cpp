#include <iostream>
using namespace std;

// 함수 객체(Functor)
// 함수처럼 동작하는 객체
// 함수 포인터의 단점
// 1) 완전히 같은 반환값과 인자값을 가지고 있어야함.
// 2) 상태를 가질 수 없다. = 함수에 값을 저장할 수 없음.

void HelloWorld()
{
    cout << "Hello World" << endl;
}


class Functor
{
public:
    // ()을 오버로딩
    void operator()()
    {
        cout << "Functor Test" << endl;
        cout << _value << endl;
    }

    bool operator()(int num)
    {
        cout << "Functor Test" << endl;
        return _value = num;
    }

private:
    int _value = 0;
};

class MoveTask
{
public:
    void operator()()
    {
        // TODO 플레이어 이동
        cout << "해당 좌표로 플레이어 이동" << endl;
    }

public:
    int _playerId;
    int _posX;
    int _posY;
};

int main ()
{   
    void(*pfunc)(void);
    // 함수 포인터
    pfunc = &HelloWorld;
    (*pfunc)();

    // 함수처럼 동작하는 객체
    Functor functor;

    functor();
    bool ret = functor(3);
    cout << ret << endl;

    // MMO에서 함수 객체를 사용하는 예시
    // 클라 <-> 서버
    // 서버 : 클라가 보내준 네트워크 패킷을 받아서 처리
    // ex) 클라 : 나를 (5, 0) 좌표로 이동시켜줘! -> 동시에 수천명이 요구함.
    // 한번에 처리하는 것이 아니라 여유가 되는 만큼 순차적으로 처리
    // 함수 객체는 생성한 시점과 실행하는 시점을 분리할 수 있다.
    MoveTask task;
    // 클라에서 요청이 들어옴
    task._playerId = 100;
    task._posX = 5;
    task._posY = 0;

    /*
    먼저 처리해야하는 요청들
    */
   
    // 나중에 여유가 될때 실행
    task();
    return 0;
}