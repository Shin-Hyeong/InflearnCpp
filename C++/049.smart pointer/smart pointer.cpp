#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
// 스마트 포인터
#include <memory>

// 스마트 포인터 (smart pointer)
// Modern C++ (C++11 이후 문법)

// 포인터를 알맞는 정책에 따라 관리하는 객체 (포인터를 래핑해서 사용)
// shared_ptr, weak_ptr, unique_ptr

// shared_ptr : 해당 ptr를 참조하지 않는 상태여야 delete 가능, ptr의 순환 문제 발생 가능.
// - 순환 문제가 생길 수 있음. 객체 생명주기에 관여함. 사용성은 높음.

// weak_ptr : ptr의 순회 문제에서 벗어날 수 있으나, 함수에서 .expired()를 통해서 검사를 해야함
// - 메모리가 구조가 쉬워짐. 객체 생명주기에 관여 하지않음. 사용성이 떨어짐.

// unique_ptr : 해당 포인터 변수만이 특정 포인터를 가지고 있도록함. 다른 변수가 동일한 주소값을 가지지 못하도록 함.
// - 다른 변수에서 값을 가지게 하기 위해선 std::move를 통해 이동시켜야함.(복사 X)

class Knight
{
public:
    Knight() { cout << "Knight 생성" << endl; }
    ~Knight() { cout << "Knight 소멸" << endl; }

    void Attack()
    {
        if (_target)
        {
            _target->_hp -= _damage;
            cout << "HP : " << _target->_hp << endl;
        }
        // target1이 메모리가 날라갔는지 확인
        // false : 메모리가 안날라감 -> 존재함.
        if (_target1.expired() == false)
        {   
            // lock은 shared_ptr로 반환함.
            // _target1를 shared_ptr롤 변환시킴.
            shared_ptr<Knight> sptr = _target1.lock();
            sptr->_hp -= _damage;
            cout << "HP : " << sptr->_hp << endl;
        }
    }

public:
    int _hp = 100;
    int _damage = 10;
    shared_ptr<Knight> _target = nullptr;
    weak_ptr<Knight> _target1;
};

// 참조 횟수를 관리하는 class
class RefCountBlock
{
public:

public:
    // _refCount = 0 -> 아무도 해당 ptr를 사용하지 않으니 delete해도 괜찮음.
    int _refCount = 1;
};

template<typename T>
class SharedPtr
{
public:
    SharedPtr() {}
    SharedPtr(T* ptr) : _ptr(ptr)
    {
        if (_ptr != nullptr)
        {
            _block = new RefCountBlock();
            cout << "RefCount : " << _block->_refCount << endl;
        }
    }

    SharedPtr(const SharedPtr& sptr) :_ptr(sptr._ptr), _block(sptr._block)
    {
        if (_ptr != nullptr)
        {
            _block->_refCount++;
            cout << "RefCount : " << _block->_refCount << endl;
        }
    }

    void operator=(const SharedPtr& sptr)
    {
        _ptr = sptr._ptr;
        _block = sptr._block;

        if (_ptr != nullptr)
        {
            _block->_refCount++;
            cout << "RefCount : " << _block->_refCount << endl;
        }
    }

    ~SharedPtr()
    {
        if (_ptr != nullptr)
        {
            _block->_refCount--;
            cout << "RefCount : " << _block->_refCount << endl;
            if (_block->_refCount == 0)
            {
                delete _ptr;
                delete _block;
                cout << "Delete Data" << endl;
            }
        }
    }

public:
    // 원본 ptr
    T* _ptr;
    //  참조 횟수
    RefCountBlock* _block = nullptr;
};

int main ()
{
    // ! 일반적인 ptr 문제
    // Knight* k1 = new Knight();
    // Knight* k2 = new Knight();

    // k1->_target = k2;

    // 타겟팅중에 로그아웃하여 사라짐.
    // delete k2;

    // 사라진 대상을 공격함. -> 메모리 오염
    // k1->Attack();    // 쓰레기값 출력

    // ! Shared_ptr 직접 구현 사용
    // SharedPtr<Knight> k2;

    {// k1의 유효 범위
        // SharedPtr<Knight>k1(new Knight());

        // k2가 k1의 주소를 가지게 됨.
        // k2 = k1;
    }// k1 소멸됨
    cout << "표준 shared_ptr 사용------------------------" << endl;
    // ! 표준 shared_ptr 사용
    // shared_ptr<Knight> k1(new Knight()) 보다 make_shared<Knight>();가 성능 더 좋음.
    // 메모리 블록을 만들면서 바로 값을 넣어줌.
    shared_ptr<Knight> k1 = make_shared<Knight>();

    {// k2의 유효 범위
        shared_ptr<Knight> k2 = make_shared<Knight>();
        k1->_target = k2;
    }// k2의 소멸
    
    // shared_ptr로 생성된 k2이기 때문에 k2가 소멸되어도 k1이 참조하고 있기 때문에 소멸하지 않음.
    // k2의 _hp가 90이 됨.
    k1->Attack();

    cout << "shared_ptr의 문제점 -----------------------" << endl;
    // ! shared_ptr의 문제점 : 2 객체가 서로 참조하고 있다면 소멸되지 않음.
    // ! 순환문제 발생함 -> 프로그램이 끝났는데도 메모리가 소멸되지 않는 큰 문제 발생
    // k3[1]
    shared_ptr<Knight> k3 = make_shared<Knight>();
    {   
        // k4[1]
        shared_ptr<Knight> k4 = make_shared<Knight>();
        // k3[1]
        // k4[2]
        k3->_target = k4;
        // k3[2]
        // k4[2]
        k4->_target = k3;
    }
    // k3[2]
    // k4[1]
    
    // 소멸시키기 위해 대상을 없애야함.
    k3->_target = nullptr;
    cout << "weak_ptr 사용-------------------------" << endl;
    // ! weak_ptr 사용
    // 해당 ptr이 메모리 해제됬는지 안됬는지 확인할 수 있음.
    // 참조하는 것은 weak_ptr에 영향을 주지 않음.
    // k5[1]
    shared_ptr<Knight> k5 = make_shared<Knight>();
    {
        // k6[1]
        shared_ptr<Knight> k6 = make_shared<Knight>();
        // k5[1]
        // k6[1]
        k6->_target1 = k5;
        // k5[1]
        // k6[1]
        k6->_target1 = k5;
    }
    // k5[1]
    // k6[0] -> 소멸

    // k6가 존재하지 않음을 확인하고 공격하지 않음.
    k5->Attack();

    cout << "------------------------------------" << endl;
    return 0;
}
// k1소멸
// k2소멸
