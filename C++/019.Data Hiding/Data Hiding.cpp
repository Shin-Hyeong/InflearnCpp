#include <iostream>
using namespace std;

// 은닉성(Data Hiding) = 캡슐화(Encapsulation)
// 무슨 내용인진 몰라도 숨기겠다.
// 숨기는 이유
// - 1) 정말 위험하고 건드리면 안되는 경우
// - 2) 다른 경로로 접근하길 원하는 경우

// 자동차
// - 핸들
// - 페달
// - 엔진
// - 문
// - 각종 전기선

// 일반 구매자 입장에서 사용하는 것
// - 핸들 / 페달 / 문
// 몰라도 됨(오히려 건들면 큰일남)
// - 엔진, 각종 전기선

// 접근 지정자
// - public : 공개적, 누구나(내부, 외부) 사용가능할 수 있음.
// - protected : 보호적, 나의 자손들(해당 class를 상속 받는 class)에게만 허락함
// - private : 개인적, 자신(class 내부에서)만 사용할 수 있음

// 1) 건드리면 안되는 경우
class Car
{
public: // (맴버) 접근 지정자
    // 일반 사용자가 자동차를 사용할 때 사용하는 함수들.
    void MoveHandle() { }   // 사용자가 핸들을 조작함
    void PushPedal() { }    // 페달을 밟음
    void OpenDoor() { }     // 문을 열음

    // public 함수인 TurnKey를 사용하여 외부에서 private 함수인 RunEngine를 호출할 수 있음.
    void TurnKey()          // 키을 넣고 돌림.
    {
        RunEngine();
    }
protected:
    void RunEngine() { }         // 엔진을 시동을 킴.
// 일반 사용자가 자동차를 사용할 때 함부로 사용하면 안되는 함수들.
// private를 통해 아래 함수들을 외부(상속 받는 class)에서 접근할 수 없도록 만든다.
// 단, 경로를 바꾸어 class 내 다른 함수가 호출하는 식으로는 외부에서 사용할 수 있다.
private:
    void DisassembleCar() { }   // 카를 분해함
    void ConnectCircuit() { }   // 전기선을 연결함.
public:
    // 핸들
    // 페달
    // 엔진
    // 문
    // 각종 전기선
};

// 여기서 public은 상속 접근 지정자라고 한다.
// 부모님하테 물려받은 유산을 꼭 나의 자손들에게 똑같이 물려줘야 하진 않음
// 실전에서는 90% 이상 public를 사용함.
// 아무런 지정자 없이 class SuperCar : Car를 사용하면 private가 적용된다.
// - public : 공개적 상속, 부모님 유산 설계 그대로 물려줌 (public -> public, protected -> protected)
// - protected : 보호받은 상속, 내 자손들에게 넘기면서 protected 형태로 변경됨.(public -> protected, protected -> protected)
// - private : 개인적인 상속, 나까지만 사용하고 자손들에겐 물려주지 않음 (public -> private, protected -> private)
class SuperCar : public Car 
{
public : 
    void PushRemoteController()
    {   
        // class Car에서 protected 접근 지정자로 되어 있어서 SuperCar에선 접근되지만 외부 함수에서는 접근을 할 수 없음.
        RunEngine();
    }
};

// 2) 다른 경로로 접근하길 원하는 경우
// 캡슐화 : 연관된 데이터와 함수를 논리적으로 묶어놓은 것
class Berserker
{
public:
    int GetHP() { return _hp; }
    
    // _hp를 캡슐화 한것
    void SetHp(int hp)
    {
        _hp = hp;
        if (_hp <= 50)
            SetBerserkerMode();
    }

private:
    // 외부에서 SetBerserkerMode() 함수만 호출하여 조건없이 호출되는 것을 막음.
    // 사양 : 체력이 50이하로 떨어지면 버서커 모드 발동
    void SetBerserkerMode()
    {
        cout << "매우 강해짐" << endl;
    }
    
private:
    // 외부에서 무심하게 _hp = 20 식으로 조작하게 되면 버커서모드 호출 없이 피만 깍일 수 있음.
    int _hp = 100;
};

int main()
{
    Berserker B;
    cout << B.GetHP() << endl;
    // BerserkerMode() 호출함.  
    B.SetHp(30);

    return 0;
}