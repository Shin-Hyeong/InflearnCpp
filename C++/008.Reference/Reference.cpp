#include <iostream>
using namespace std;

// ! Point* : 포인트 변수
// ! *point : point가 가지고 있는 주소로 이동한다.

// ! Reference& : 참조 변수
// ! &reference : reference변수의 주소를 가져온다.

struct StatInfo
{
    int hp;
    int attack;
    int defense;
};

void CreateMonster(StatInfo *Info)
{
    Info->hp = 40;
    Info->attack = 8;
    Info->defense = 1;
}

// 1) 값 전달 방식
// 값을 수정하지 않는다면, 양쪽 다 일단 문제 없음.
// 메모리상에서는 매개변수 info의 정보를 지역변수 info로 복사해서 저장해서 사용한다.
void PrintInfoByCopy(StatInfo info)
{   
    cout << "Copy-----------------------" << endl;
    cout << "HP  : " << info.hp << endl;
    cout << "ATK : " << info.attack << endl;
    cout << "DEF : " << info.defense << endl;
    cout << "---------------------------" << endl;
}

// 2) 주소 전달 방식
// 메모리상에서는 매개변수의 주소값을 지역변수로 받아서 주소에서 값을 가져온다.
void PrintInfoByPtr(StatInfo* info)
{
    cout << "Ptr------------------------" << endl;
    cout << "HP  : " << info->hp << endl;
    cout << "ATK : " << info->attack << endl;
    cout << "DEF : " << info->defense << endl;
    cout << "---------------------------" << endl;
}

// 3) 참조 전달 방식
// 메모리상에서는 매개변수의 주소값을 지역변수로 받아서 주소에서 값을 가져온다.
void PrintInfoByRef(StatInfo& info)
{
    cout << "Ref------------------------" << endl;
    cout << "HP  : " << info.hp << endl;
    cout << "ATK : " << info.attack << endl;
    cout << "DEF : " << info.defense << endl;
    cout << "---------------------------" << endl;
}

// StatInfo 구조체가 1000Byte짜리 대형 구조체라면?
// - 값 전달 : StatInfo로 넘기면 1000Byte가 복사되는 상황 발생
// - 주소 전달 : StatInfo*는 운영체제에 비례해서 변경(주소 바이트 크기, x86 : 4Byte, x64 : 8Byte)
// - 참조 전달 : StatInfo&는 운영체제에 비례해서 변경(주소 바이트 크기, x86 : 4Byte, x64 : 8Byte)

// 참조 전달 사용하는 이유
// 1) info->hp 보다 info.hp가 더 사용성이 높다.
// 2) 값 전달보다 주소 전달이 메모리를 절약할 수 있다.
// 값 전달처럼 사용성 있게 코딩하고, 주소 전달처럼 주소값을 이용해 메모리를 절약하는 방식

// 참조 전달 vs 주소 전달
// 1) 편의성 관련
// 참조 전달이 편의성이 좋다는 것이 꼭 장점만 있는게 아니다.
// 포인터는 주소를 넘기니 확실하게 원본을 넘긴다는 힌트를 줄 수 있다.
// 참조는 값 전달과 비슷하게 생겼기 때문에 모르고 지나칠 수 있음.
// 값 전달   : PrintInfo(info)
// 참조 전달 : PrintInfo(info)

// 참조 전달을 사용해서 의도치 않고 원본의 값을 수정하는 문제 발생할 수 있음.
// 매개변수에 const를 붙여서 함수내에서 값이 변하는걸 방지할 수 있음.
// void PrintInfo(const StatInfo& info)

// 주소 참조에서도 const를 사용 가능.
// *를 기준으로 앞에 붙이느냐, 뒤에 붙이느냐에 따라 의미가 달라진다.

// info [ 주소값 ]          주소값 [ 데이터 ]
// (const StatInfo* info) or (StatInfo const* info)
// 주소 값이 가지고 있는 데이터를 변경하는 것을 방지함.
// 주소 값이 변경되는 것은 방지 못함.

// (StatInfo* const info)
// 매개변수가 가지고 있는 주소값이 변경되는것을 방지함.
// 주소 값이 가지고 있는 데이터를 변경하는 것은 방지 못함.

// (const StatInfo* const info)
// 둘다 사용하여 주소값과 데이터 둘 다 변경 되지 못하도록 만든다.

// 2) 초기화 여부
// 참조 전달은 참조하는 대상이 존재해야 한다.
// 주소 전달은 어떤 주소를 의미하기 때문에 주소에 대상이 실존하지 않을 수도 있음.

// 주소 전달
// StatInfo* testPtr;
// PrintInfoByPtr(testPtr);
// testPtr에 구조체 값이 없어도 오류 나지 않음.
// 포인터변수가 아무것도 가르키지 않으면 nullptr를 넣어준다.
// StatInfo* testPtr = nullptr;
// 장점 : nullptr를 이용하여 원하는 찾는 오브젝트의 주소가 없을 때 nullptr로 반환하여 사용 가능.
// 단점 : nullptr에서 주소를 읽을려고 하면 컴파일러는 되지만 실행했을 때 유효하지 않아 에러 처리남.
// 포인터를 사용하면 nullptr로 인한 오류가 80%이상을 차지할 정도.
// if(info == nullptr) return;를 사용하여 null crash error를 어느정도 방지 가능.

// 참조 전달
// StatInfo& testRef;
// PrintInfoByRef(testRef);
// testRef가 무엇을 참조한지 모르기 때문에 오류 남.
// StatInfo& testRef = info;
// PrintInfoByRef(testRef);
// testRef가 info를 참조하도록 선언함. testRef는 info의 2번째 이름.
// 장점 : 무조건 유요한 값을 참조하기 때문에 null crash error를 막을 수 있음.
// 단점 : 원하는 주소값이 없을 때 nullptr(유효한 값이 아님.)를 줄 수 없음.

// 주소로 사용하던걸 참조로 넘겨줄려면?
// pointer[ 주소(&info) ]     Ref, info[ 데이터 ]
// PrintInfoByRef(pointer);
// pointer는 주소를 가지고 있기 때문에 pointer가 가지고 있는 주소로 이동시켜야 함.
// PrintInfoByRef(*pointer);

// 참조로 사용하던걸 주소로 넘겨줄려면?
// pointer[ 주소(&info) ]      reference, info[ 데이터 ]
// PrintInfoByPtr(reference);
// reference는 데이터를 가지키고 있기 때문에 &를 붙여 주소를 가르키도록 한다.
// PrintInfoByPtr(&reference);

// 결론
// Team by Team -> 어디서 사용하느냐에서 따라 다름.
// Google Open Source 에서는 무조건 포인터 사용
// Unreal Engine에서는 reference도 사용함.

// - 값이 유효하지 않을 경우도 고려해야 한다면 pointer (null 체크 필수)
// - 바뀌지 않고 읽는 용도(ReadOnly)만 사용하면 const ref&
// - 그 외 일반적으로 ref (명시적으로 값이 변경될 수 있는 함수를 호출할 때 OUT을 붙인다.)
// #define OUT
// StatInfo ChangeInfo(OUT StatInfo& info);
// ChangeInfo(OUT info);
// OUT는 아무 것도 정의하지 않았기 때문에 아무런 의미 없이 명시적인 의미만 가짐.
// -- 단, 다른 사람이 pointer를 만들어놓을 걸 이어서 만든다면, 계속 pointer을 이용한다.
// StatInfo ChangeInfo(StatInfo* info1, StatInfo* info2) ( O )
// StatInfo ChangeInfo(StatInfo* info1, StatInfo& info2) ( X )

int main()
{
    StatInfo info;
    CreateMonster(&info);
    
    // 값 전달
    PrintInfoByCopy(info);

    // 주소 전달
    PrintInfoByPtr(&info);

    // 참조 전달
    PrintInfoByRef(info);

    // 참조 전달 예시
    // 4Byte 정수형으로 변수에 number라는 이름을 짓어준다.
    // number에서 뭘 꺼내거나, 뭘 넣는다면 해당 주소(data or stack or heap)에 값을 넣으면 된다.
    int number = 1;

    // * 주소를 담는 변수
    // 해당 주소를 따라가면 int 데이터가 있음.
    int* pointer = &number;
    // pointer 변수에 있는 주소를 타고 이동해서 그 변수에 2를 넣는다.
    *pointer = 2;

    int& reference = number;
    // 어셈블리 관점에서 실제 작동은 포인터와 똑같음.
    // 실제로 실행하면 컴파일러는 포인터와 같이 실행한다.

    // C++ 관점에서는 number라는 바구니에 또 다른 이름을 부여한 것.
    // number라는 바구니에 reference라는 다른 이름을 지어준다.
    // reference에 뭘 꺼내거나 넣으면 실제 number에 그 값을 꺼내거나 넣는것과 같음.
    reference = 3;

    return 0;
}