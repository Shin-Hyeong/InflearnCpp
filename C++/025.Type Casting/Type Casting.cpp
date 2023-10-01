#include <iostream>
using namespace std;

// ! 정리
// [값 타입 변환] : 진짜 비트열도 바꾸고 논리적으로 말이 되게 바꾸는 변환
// - 논리적으로 말이 된다(ex. BullDog -> Dog) OK
// - 논리적으로 말이 안된다(ex. Dog -> DullDog, Dog -> Knight) NO

// [참조 타입 변환] : 비트열은 냅두고 우리의 '관점'만 바꾸는 변환
// - 명시적으로 요구하면 해주긴 하는데, 암시적으로 해주는지는 안정성 여부를 연관 있음
// - 안전하다(ex. BullDog -> Dog&) 암시적으로도 OK
// - 위험하다(ex. Dog -> BullDog&)
// -- 메모리 침범 위험이 있는 경우는 암시적으로 해주진 않음
// -- 명시적으로 하겠다고 하면 OK


// 타입 변환
// void* pointer = malloc(1000); -> malloc을 void*로 반환하고
// Player p1 = (Player*)pointer; -> void*을 Player*을 타입 변환을 통해 사용했음.

class Knight
{
public:
    int _hp = 10;
};

class Dog
{
public:
    Dog()
    {

    }
    // 클래스끼리 변환을 위한 타입 변환 생성자
    Dog(const Knight& knight)
    {
        _age = knight._hp;
    }

    // 타입 변환 연산자
    operator Knight()
    {   
        // 자신(*this)을 Knight로 변환해서 반환
        return (Knight)(*this);
    }
public:
    int _age = 1;
    int _cuteness = 0;
};

class BullDog : public Dog
{

public:
    bool _french; // 프렌치 불독

};

int main()
{
    //--------------- 타입 변환 유형 (비트열 재구성 여부) --------------

    // [1] 값 타입 변환
    // 특징) 의미를 유지하기 위해서, 원본 객체와 다른 비트열 재구성
    {
        int a = 123456789;      // 2의 보수
        float b = (float)a;     // 부동소수점(지수 + 유효숫자)
        cout << b << endl;      // 1.23457e+008 -> 소수 6번째 자리에서 반올림
                                // 1.23457 : 유효숫자, e+ : 지수 시작점, 008 : 지수 값.
                                // 1.23457 * 10^8 = 123457
        // a의 비트열 : 075bcd15
        // b의 비트열 : 4ceb79a3
        // 같은 값을 넣었지만 값(비트열)이 달라짐
    }

    // [2] 참조 타입 변환
    // 특징) 비트열을 재구성하지 않고, '관점'만 바꾸는 것
    // 거의 쓸일은 없지만, 포인터 타입 변환도 참조 타입 변환과 동일한 룰을 사용함
    {
        int a = 123456789;
        float b =(float&)a;
        cout << b << endl;       // 1.6536e-034
        // a의 비트열 : 075bcd15
        // b의 비트열 : 075bcd15
        // 비트열은 그대로 가지고 있지만 2의 보수로 계산하던것을 부동소수점 계산하도록 바뀜.
    }

    //--------------- 안전도 분류 --------------
    
    // [1] 안전한 변환
    // 특징) 의미가 항상 100% 완전히 일치하는 경우
    // 같은 타입이면서 크기만 더 큰 바구니로 이동
    // 작은 사이즈 -> 큰 사이즈로 이동 OK (업캐스팅)
    // ex) char -> short, short -> int, int -> __int64
    {
        int a = 123456789;
        __int64 b = a;  // 업캐스팅
        cout << b << endl;  // 123456789
    }

    // [2] 불안전한 변화
    // 특징) 의미가 항상 100% 일치한다고 보장하지 못하는 경우
    // 타입이 다르거나
    // 같은 타입이지만 큰 사이즈 -> 작은 사이즈 이동 (다운캐스팅)
    {
        int a = 123456789;
        float b = a;    // 타입이 달라짐.
        short c = a;    // 다운캐스팅
        cout << b << endl;  // 1.23457e+008
        cout << c << endl;  // -13035
    }

    //--------------- 프로그래머 의도에 따라 분류 --------------

    // [1] 암시적 변환
    // 특징) 이미 알려진 타입 변환 규칙에 따라서 컴파일러 '자동'으로 타입 변환 
    {
        int a = 123456789;
        float b = a; // 암시적으로 변환 (float)a 라고 안씀. 경고가 뜰수 있음.
        cout << b << endl; // 1.23457e+008
    }

    // [2] 명시적 변환
    {
        int a = 123456789;
        // (int*)을 붙이지 않으면 컴파일러가 타입이 전혀 맞지 않아 오류를 일으킴
        // 명시적으로 표현함으로써 프로그래머가 위험을 알고 강제적으로 변환을 일으킴
        int* b = (int*)a;
        cout << b << endl; // a의 주소를 가지고 됨.    0x75bcd15
    }

    //--------------- 아무런 연관 관계가 없는 클래스 사이의 변환 --------------

    // [1] 연관없는 클래스 사이의 '값 타입' 변환
    // 특징) 일반적으로 안됨. 객체를 대상으로 변경이 이루어짐
    // 예외적으로 class 내에서  타입변환 생성자, 타입변환 연산자 생성하면 가능해짐.
    {   
        // 타입 변환 생성자를 통해서 변환   (knight -> dog)
        Knight knight;
        Dog dog = (Dog)knight;

        // 타입 변환 연산자를 통해서 변환   (dog -> knight)
        Knight knight2 = dog;
    }

    // [2] 연관없는 클래스 사이의 참조 타입 변환
    // 특징) 명시적으로 하면 OK, 주소를 대상으로 변경이 이루어짐
    {
        Knight knight;
        // C++ 관점 : knight라는 변수에 또다른 별칭(dog)을 준다
        // 어셈블리 관점 : 포인터 = 참조

        // [ 포인터 ] -> [ Dog ]
        // knight를 Dog타입으로 형변환함. dog는 Dog로 형변환된 knight를 참조한다.
        Dog& dog = (Dog&)knight;
        // knight는 1개 멤버 변수(4byte), Dog는 2개의 멤버 변수(8byte)를 가지고 있기 때문에 
        // knight의 범위를 벗어난 메모리를 건들 수 있다.
        dog._cuteness = 12;
    }

    //--------------- 상속 관계에 있는 클래스 사이의 변환 --------------

    // [1] 상속 관계 클래스의 값 타입 변환
    // 특징) 자식->부모 OK  /   부모->자식 NO
    {
        // ! 부모 class -> 자식 class : NO
        //Dog dog;
        // dog가 _french의 값을 가지고 있지 않음. 명시적으로 변환을해도 성립되지 않음.
        // BullDog bulldog = (BullDog)dog;
        // ? 모든 개는 불독이 아니다

        // ! 자식 class -> 부노 class : OK
        BullDog bulldog;
        // bulldog가 가지고 있던 _french만 사라지고 dog에 들어감.
        Dog dog = bulldog;
        // ? 모든 불독은 개이다
    }

    // [2] 상속 관계 클래스의 참조 타입 변환
    // 특징) 자식->부모 OK  /   부모->자식 (암시적NO) (명시적 OK)
    {
        // ! 부모 class -> 자식 class : (암시적)NO, (명시적) OK
        Dog dog;
        // dog을 BullDog 타입으로 형변환함.
        // 암시적으론 오류를 표시하지만 명시적 변환을 하면 오류를 패스함.
        BullDog& bulldog = (BullDog&)dog;
        // 엉뚱한 메모리 위치의 값을 변경함.
        // BullDog 타입이 가지고 있어야 할 _french의 값을 가지고 있지 않음.
        bulldog._french =123;

        // ! 자식 class -> 부노 class : OK
        // Dog 타입이 가지고 있어야할 멤버 변수를 다 가지고 있음.
        BullDog bulldog2;
        Dog& dog2 = bulldog2;
    }

    return 0;
}