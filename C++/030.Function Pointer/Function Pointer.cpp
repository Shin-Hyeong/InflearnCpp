#include <iostream>
using namespace std;

// 함수 포인터

int Add(int a, int b)
{
    return a + b;
}

class Item
{
public:

public:
    int _itemId;
    int _rarity;
    int _ownerId;
};

// bool(Item*, int) 타입형태를 ITEM_SELECTOR라고 별칭함.
typedef bool(ITEM_SELECTOR)(Item*, int);

// Item 타입을 반환하고 Item 배열, int, bool(Item*, int)형태의 함수를 매개변수를 가지는 함수
// ITEM_SELECTOR가 가르키고 있는 함수는 Item를 선별하는 함수를 불러오면 된다.
Item* FindItem(Item items[], int itemCount, ITEM_SELECTOR* selector, int value)
{
    for (int i = 0; i < itemCount; i++)
    {
        Item* item = &items[i];
        // item의 _rarity가 2이상인지 확인
        if (selector(item, value))
            return item;
    }
    return nullptr;
}

// bool (Item*)의 형태를 가진 함수
bool IsRareItem(Item* item, int value)
{
    return item->_rarity >= value;
}

bool IsOwnerItem(Item* item, int ownerId)
{
    return item->_ownerId == ownerId;
}

int main ()
{
    int a = 10;
    // DATA는 int형 자료형을 갖게 된다. DATA = int
    typedef int DATA;

    // pointer[ 주소 ]  ->  주소 [ a ]
    // 1) 포인터        *
    // 2) 변수 이름     pointer
    // 3) 변수 타입     int
    int* pointer = &a;
    DATA* pointerD = &a;

    // 함수
    // 함수는 매개변수의 타입, 반환 타입이 뭔지 중요하다.
    // int Add(int a, int b); -> Add는 함수 이름이므로 중요하지 않음
    // int (int a, int b) -> 2개의 int 매개변수를 가지고 반환갑이 int임.
    typedef int(FUNC_TYPE)(int, int); // 2개의 int 매개변수를 가지고 반환갑이 int인 함수를 FUNC_TYPE이라고 한다.
    // typedef int(int a, int b) = FUNC_TYPE같은 느낌
    // 모던 C++
    using FUNC_TYPE2 = int(int, int);

    // 1) 포인터        *
    // 2) 변수 이름     fn
    // 3) 변수 타입     함수(매개변수는 int, int  / 반환값은 int)
    FUNC_TYPE* fn;

    // 어셈블리상 Add함수를 불러오는 것은 Add가 가르키고 있는 주소를 호출하고 있음.
    // Add(함수의 이름) -> 함수의 시작 주소를 가지고 있음.
    int result = Add(1, 2);
    cout << result << endl;

    // int(int, int)의 주소를 가질수 잇는 포인터 변수에 int(int, int)형태인 함수의 주소를 넣음.
    fn = &Add;

    // 기본 함수포인터 문법
    result = fn(3, 5);
    cout << result << endl;

    // 함수포인터는 *(접근 연산자) 붙어도 함수 주소를 나타냄.
    result = (*fn)(4, 1);
    cout << result << endl;

    // 1) 함수 포인터 사용 이유
    // A라는 함수를 100개 사용중인데 함수를 B로 변경해야하는 상황
    // 그냥 함수 사용 : 일일히 찾아서 변경시켜줘야함
    // 함수 포인터 사용 : 함수 포인터가 가르키는 주소만 변경하면 모두 변경됨.

    Item items[10] = {};
    items[3]._rarity = 3;
    Item* rareItem = FindItem(items, 10, IsRareItem, 2);
    Item* ownerItem = FindItem(items, 10, IsOwnerItem, 5);

    // 2) 함수 포인터 사용 이유
    // 다양한 동작(함수)을 함수에 넘겨주고 싶을때.
    // 동작(함수) 자체를 함수의 인자(매개변수)로 넘겨 주고 싶을때
    // 정확하게 일치하고 있는 인자값들을 가지고 있는 함수만 넘겨 줄수 있음.

    return 0;
}