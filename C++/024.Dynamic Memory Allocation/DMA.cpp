#include <iostream>
using namespace std;

// 동적 할당

// ! 메모리 구조  
// -- 낮은 주소
// - 실행할 코드가 저장되는 영역 -> 코드

// - 전역(global) / 정적(static) 변수 -> 데이터 영역
// -- 프로그램이 실행되는 도중에는 무조건 사용

// - 동적 할당 -> 힙 영역
// -- 필요할때만 사용하고, 필요없으면 반납할 수 있다.
// -- 생성/소멸 시점을 관리할 수 있다.
// -- 동적할당과 연관된 함수/연산자 : C언어(malloc / free), C++(new / delete, new[] / delete[])

// - 지역 변수/ 매개변수 -> 스택 영역
// -- 함수가 끝나면 같이 정리되는 불안정한 메모리 -> 잠시 함수에 매개변수를 넘긴다거나, 하는 용도로 사용
// -- 높은 주소

// 실제 상황에서 동적할당 사용
// - 사용자 캐릭터 1명 ~ 5만명, 몬스턴 1마리 ~ 500만 마리

class Monster
{
public:
    Monster()
    {
        cout << "Monster" << endl;
    }
    ~Monster()
    {
        cout << "~Monster" << endl;
    }
public:
    int _hp;
    int _x;
    int _y;
};

// 2) 전역 변수(배열)로 생성하기
// 1마리만 필요할 수도 있는데 무조건 500만마리를 준비함.
// 프로그램이 실행되는 도중에는 무조건 사용함.
// Monster monster[500 * 10000];

int main()
{
    // 1) 지역 변수(배열)로 생성하기 -> 방대한 배열량은 스택오버플로우를 일으켜서 시스템이 꺼짐.
    // Monster monster[500 * 10000];

    // ! 프로그램의 영역
    // 유저 영역 [메모장] [카카오톡]
    // 서로 독립적인 형태
    // 프로그램이 추가적인 메모리가 부족하면 커널영역에서 허락을 얻어서 메모리를 확장함.
    // --------------------------------------------
    // 커널 영역 (Windows(운영체제) 등 의 핵심 코드)

    // ! 동적할당 작동원리
    // 유저 영역) 프로그램이 운영체제에서 제공하는 API(함수) 호출
    // 커널 영역) 프로그램이 요청한 메모리를 할당해서 건내줌
    // 실질적으로 프로그램이 원할때마다 메모리를 제공하는 형태가 아님.

    // ! 실질적 힙 메모리 형태
    // 한번에 대용량으로 힙 메모리를 사용할 수 있도록 할당해줌.
    // C++에서는 기본적으로 CRT(C 런타임 라이브러리)의 [힙 관리자]를 통해 힙 영역을 나누어서 사용한다.
    // 고급 영역으로 직접 API를 통해 힙을 생성하고 관리할 수도 있음(MMORPG 서버 메모리 풀링)

    // ! malloc()
    // - 할당받고 싶은 메모리 크기를 건내준다.
    // - 메모리 할당 후 시작 주소를 가리키는 포인터를 반환해준다 (메모리 부족시 NULL를 반환함.)
    // ! malloc(); // void *__cdecl malloc(size_t _Size);

    // size_t -> unsigned int
    /*
    #ifdef _WIN64 -> 운영체제가 64비트이면  unsigned __int64로 typedef
        typedef a b -> a 자료형을 b라고 써서 사용하고 싶다.

        unsigned __int 64 자료형을 size_t라고 써서 사용하고 싶다.
        typedef unsigned __int64 size_t;
    #else   운영체제가 32비트이면 unsigned int로 typedef
        typedef unsigned int size_t;
    #endif
    */
    
    // void *__cdecl malloc(unsigned int64 _Size);

    // void* pointer = malloc(1000);
    // 할당받은 대용량 힙 메모리에서 1000byte만큼의 메모리를 할당하고 시작주소를 pointer 변수에 준다.
    // 1000byte 할당해주는거 말고도 헤더에 할당될때 얼마만큼 할당해줬는지 기록한다.
    // ? void형 포인터
    // ? *가 있으니까 포인터변수이다 -> OK
    // ? 타고 가면 void니까 아무것도 없다? -> NO
    // ? 타고 가면 뭐가 있는지 모르겠으니까 적당히 변환해서 사용해라 -> OK
    // class Monster의 크기만큼만 할당
    void* pointer = malloc(sizeof(Monster));

    // 할당받은 메모리를 Monster형태로 변환해서 사용
    Monster* m1 = (Monster*)pointer;
    m1->_hp = 100;
    m1->_x = 1;
    m1->_y = 2;

    // ! free
    // - malloc (혹은 기타 calloc, realloc 등 사촌)을 통해 할당된 영역을 해제
    // - 힙 관리자가 할당 / 미할당 여부를 구분해서 관리

    // 메모리가 필요없어지면 할당된 메모를 해제
    // 헤더에 기록된 할당해준 메모리량 만큼 해제한다.
    free(pointer);
    pointer = nullptr;

    // ! new / delete
    // - C++에 추가됨.
    // - malloc/free는 함수이고 new/delete는 연산자(operator)

    // Monster 타입인 m2에 class Monster의 크기만큼 할당
    // void* pointer = malloc(sizeof(Monster))
    // Monster m2 = (Monster*)pointer; 와 같다.
    // 자료형 변수명 = new 할당할 크기
    Monster *m2 = new Monster;
    m2->_hp = 200;
    m2->_x = 3;
    m2->_y = 2;

    // 메모리 해제
    delete m2;
    m2 = nullptr;

    // ! new[] / delete[]
    // Monster를 배열형태로 5개 할당하고 시작주소를 m3에 저장한다.
    // 배열과 같이 N개 데이터를 같이 할당할때 사용함
    // m3 = Monster[0]
    Monster* m3 = new Monster[5];
    m3->_hp = 200;
    m3->_x = 3;
    m3->_y = 2;

    // m4 = Monster[1]
    Monster* m4 = (m3 + 1);
    m4->_hp = 400;
    m4->_x = 3;
    m4->_y = 2;

    // Monster형태로 5개 할당된 메모리를 해제
    // new[]형태로 할당하고 delete로 해제하면 에러 혹은 맨앞에 있는 메모리만 해제된다.
    delete[] m3;

    // ! Heap Overflow
    // - 할당 받은 힙 범위를 초과해서 사용하는 문제

    // ! 메모리 누수
    // 할당 받은 메모리를 해제하지 않으면 메모리가 반납되지 않아서 
    // 사용하지도 않는데 메모리를 계속 차지하고 있는 현상이 일어남

    // ! Double free
    // 해제해준 메모리를 한번 더 해제할려고 하면 에러가 발생함.

    // ! Use-After-Free
    // 메모리를 해제해도 pointer 변수에는 할당해줬던 메모리의 주소를 가지고 있음.
    // 메모리 주소를 가지고 있기 떄문에 의도치 않는 주소에 값을 저장시킬 수 있음.
    // 메모리가 오염됬다고 한다.
    // free()/delete() 이후 pointer 변수도 nullptr해주는 것이 좋다.

    // ! malloc/free vs new/delete
    // - 사용 편의성 -> new/delete 
    // - 타입에 상관없이 특정한 크기의 메모리 영역을 할당 받는다 -> malloc/free
    // - new/delete는 (생성타입이 클래스일 경우) 생성자/소멸자를 호출한다.
    // -- malloc/free는 생성자와 소멸자는 호출하지 않음.

    return 0;
}