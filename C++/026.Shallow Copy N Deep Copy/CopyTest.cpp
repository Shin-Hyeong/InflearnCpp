#include <iostream>
using namespace std;

// 실험
// - 암시적 복사 생성자 Steps
// -- 1) 부모 클래스의 복사 생성자 호출 -> ImplicitPlayer(const ImplicitPlayer& ImplicitPlayer)
// -- 2) 멤버 클래스(ImplicitPet _ImplicitPet(); OK / ImplicitPet* _ImplicitPet(); NO)의 복사 생성자 호출 -> ImplicitPet(const ImplicitPet& ImplicitPet)
// -- 3) 멤버가 기본 타입일 경우 메모리 복사(얕은 복사 Shallow Copy)
// - 명시적 복사 생성자 Steps
// -- 1) 부모 클래스의 기본 생성자 호출 -> ExplicitPlayer()
// -- 2) 멤버 클래스의 기본 생성자 호출 -> ExplicitPet()
// -- 3) 복사 생성자에 명시된 코드 실행 -> ExplicitKnight(const ExplicitKnight& explicitKnight)
// ! -- 복사 생성자에서 제대로 복사하지 않으면 누락된 데이터(부모 class의 멤버 변수, 등)가 있을 수 있다.
// ! -- 혹은 초기화 리스트를 통해서 부모 class의 복사 생성자를 호출 하도록 한다.

// - 암시적 복사 대입 연산자 Steps
// -- 1) 부모 클래스의 복사 연산자 호출 -> ImplicitPlayer& operator=(const ImplicitPlayer& implicitPlayer)
// -- 2) 멤버 클래스(ImplicitPet _ImplicitPet(); OK / ImplicitPet* _ImplicitPet(); NO)의 복사 생성자 호출 -> ImplicitPet& operator=(const ImplicitPet& pet)
// -- 3) 멤버가 기본 타입일 경우 메모리 복사(얕은 복사 Shallow Copy)
// - 명시적 복사 대입 연산자 Steps
// -- 1) 알아서 해주는 거 없음 프로그래머가 원하는대로 작성해야함.

// ! 암시적 복사
class ImplicitPet
{
public:
    ImplicitPet()
    {
        cout << "ImplicitPet()" << endl;
    }
    ~ImplicitPet()
    {
        cout << "~ImplicitPet()" << endl;
    }
    // 복사 생성자
    ImplicitPet(const ImplicitPet& implicitPet)
    {
        cout << "ImplicitPet(const ImplicitPet& implicitPet)" << endl;
    }
    ImplicitPet& operator=(const ImplicitPet& pet)
    {
        cout << "operator=(const Pet& pet)" << endl;
        return *this;
    }
};

class ImplicitPlayer
{
public:
    ImplicitPlayer()
    {
        cout << "ImplicitPlayer()" << endl;
    }
    // 복사 생성자
    ImplicitPlayer(const ImplicitPlayer& implicitPlayer)
    {
        cout << "ImplicitPlayer(const ImplicitPlayer& implicitPlayer)" << endl;
        _level = implicitPlayer._level;
    }
    // 복사 연산자
    ImplicitPlayer& operator=(const ImplicitPlayer& implicitPlayer)
    {
        cout << "operator=(const ImplicitPlayer& player)" << endl;
        _level = implicitPlayer._level;
        return *this;
    }
    ~ImplicitPlayer()
    {
        cout << "~ImplicitPlayer()" << endl;
    }

public:
    int _level = 0;
};

class ImplicitKnight : public ImplicitPlayer
{
public:
    ImplicitKnight()
    {
        cout << "ImplicitKnight()" << endl;
    }
    ~ImplicitKnight()
    {
        cout << "~ImplicitKnight()" << endl;
    }

public:
    int _hp = 100;
    ImplicitPet _ImplicitPet;
};

// ! 명시적 복사
class ExplicitPet
{
public:
    ExplicitPet()
    {
        cout << "ExplicitPet()" << endl;
    }
    ~ExplicitPet()
    {
        cout << "~ExplicitPet()" << endl;
    }
    // 복사 생성자
    ExplicitPet(const ExplicitPet& explicitPet)
    {
        cout << "ExplicitPet(const ExplicitPet& explicitPet)" << endl;
    }
};

class ExplicitPlayer
{
public:
    ExplicitPlayer()
    {
        cout << "ExplicitPlayer()" << endl;
    }
    // 복사 생성자
    ExplicitPlayer(const ExplicitPlayer& explicitPlayer)
    {
        cout << "ExplicitPlayer(const ExplicitPlayer& explicitPlayer)" << endl;
        _level = explicitPlayer._level;
    }
    // 복사 연산자
    ExplicitPlayer &operator=(const ExplicitPlayer& explicitPlayer)
    {
        cout << "operator=(const ExplicitPlayer& player)" << endl;
        _level = explicitPlayer._level;
        return *this;
    }
    ~ExplicitPlayer()
    {
        cout << "~ExplicitPlayer()" << endl;
    }

public:
    int _level = 0;
};

class ExplicitKnight : public ExplicitPlayer
{
public:
    ExplicitKnight()
    {
        // _ImplicitPet = new ImplicitPet();
    }
    // 부모 class인 ExplicitPlayer의 복사 생성자 호출
    // 멤버 변수인 _explicitPet에 복사대상의_explicitPet의 값을 복사(복사 생성자 호출)
    ExplicitKnight(const ExplicitKnight &explicitKnight) : ExplicitPlayer(explicitKnight), _explicitPet(explicitKnight._explicitPet)
    {
        cout << "ExplicitKnight(const ExplicitKnight& explicitKnight)" << endl;;
        _hp = explicitKnight._hp;
    }
    ExplicitKnight &operator=(const ExplicitKnight &explicitKnight)
    {
        cout << "operator=(const ExplicitKnight& knight)" << endl;
        // ExplicitPlayer의 복사 연산자 호출
        ExplicitPlayer::operator=(explicitKnight);
        _explicitPet = explicitKnight._explicitPet;
        _hp = explicitKnight._hp;
        return *this;
    }
    ~ExplicitKnight()
    {
        // delete _ImplicitPet;
    }

public:
    int _hp = 100;
    ExplicitPet _explicitPet;
    // ImplicitPet *_ImplicitPet;
};

int main ()
{
    {
    ImplicitKnight knight;
    knight._hp = 200;

    cout << "---------------- 암시적 복사 생성자 ----------------" << endl;
    ImplicitKnight knight2 = knight;

    cout << "---------------- 암시적 복사 연산자 ----------------" << endl;
    ImplicitKnight knight3;
    knight3 = knight;
    cout << "---------------- 암시적 복사 소멸자 ----------------" << endl;
    }

    {
    cout << "---------------------------------------------------" << endl;
    ExplicitKnight knight;
    knight._hp = 300;

    cout << "---------------- 명시적 복사 생성자 ----------------" << endl;
    ExplicitKnight knight2 = knight;

    cout << "---------------- 암시적 복사 연산자 ----------------" << endl;
    ExplicitKnight knight3;
    knight3 = knight;
    cout << "---------------- 명시적 복사 소멸자 ----------------" << endl;
    }

    return 0;
}