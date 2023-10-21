#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// 람다(lambda)
// Modern C++ (C++11 이후 문법)

// 함수 객체를 빠르게 만드는 문법

enum class ItemType
{
    None,
    Armor,
    Weapon,
    Jewelry,    // 보석
    Consumable  // 소모품
};

enum class Rarity
{
    Common,
    Rare,
    Unique
};

class Item
{
public:
    Item() { }
    Item(int itemId, Rarity rarity, ItemType type)  
        : _itemId(itemId), _rarity(rarity), _type(type)
    {

    }

public:
    int _itemId = 0;
    Rarity _rarity = Rarity::Common;
    ItemType _type = ItemType::None;
};

int main ()
{
    vector<Item> v;
    v.push_back(Item(1, Rarity::Common, ItemType::Weapon));
    v.push_back(Item(2, Rarity::Common, ItemType::Armor));
    v.push_back(Item(3, Rarity::Rare, ItemType::Jewelry));
    v.push_back(Item(4, Rarity::Unique, ItemType::Weapon));

    // 람다 = 함수 객체를 손 쉽게 만드는 문법 -> 람다 자체로 C++11에 새로운 기능을 추가한 것은 아님.
    {   
        // 일반적인 함수 객체 선언 & 사용
        struct IsUniqueItem
        {
            bool operator()(Item& item)
            {
                return item._rarity == Rarity::Unique;
            }
        };
        auto findIt = std::find_if(v.begin(), v.end(), IsUniqueItem());

        if (findIt != v.end())
        {
            cout << "아이템 ID 함수 객체 : " << findIt->_itemId << endl;
        }

        // ! 람다 표현식(lambda expression)
        // [](매개변수(인자)) {함수 구현부} -> 익명 함수를 생성
        // 구현부를 추론하여서 반환값을 줌.
        // bool 형태를 받음.
        // Lambda에 의해 만들어진 실행시점 객체를 클로저(closure)라고 불림.
        auto isUniqueLambda = [](Item& item) { return item._rarity == Rarity::Unique;};

        // 만약 다른 type으로 받고 싶으면 () {} 사이에 -> type를 넣으면 된다.
        // int타입으로 받아옴.
        auto isUniqueLambdaInt = [](Item &item) -> int { return item._rarity == Rarity::Unique; };

        auto findIt2 = std::find_if(v.begin(), v.end(), isUniqueLambda);

        if (findIt2 != v.end())
        {
            cout << "아이템 ID 다회성 람다 : " << findIt->_itemId << endl;
        }

        // 람다 함수를 완전히 1회성으로 사용하겠다
        auto findIt3 = std::find_if(v.begin(), v.end(), 
            [](Item &item){ return item._rarity == Rarity::Unique; });

        if (findIt3 != v.end())
        {
            cout << "아이템 ID 일회성 람다 : " << findIt->_itemId << endl;
        }
    }

    cout << "----------------------------------------------" << endl;

    {
        // 일반적인 함수 객체 선언 & 사용
        struct FindItemByItemId
        {
            FindItemByItemId(int itemId) : _itemId(itemId)
            {

            }

            bool operator()(Item &item)
            {
                return item._itemId == _itemId;
            }
            
            int _itemId;
        };
        int itemId = 4;
        auto findIt = std::find_if(v.begin(), v.end(), FindItemByItemId(itemId));

        if (findIt != v.end())
        {
            cout << "아이템 ID 함수 객체 : " << findIt->_itemId << endl;
        }

        // ! 람다 표현식(lambda expression)
        // [캡쳐](매개변수(인자)) {함수 구현부} -> 익명 함수를 생성

        // 함수 객체는 외부의 변수를 사용할 수 없지만 람다는 외부 변수를 사용할 수 있다.
        // 사용 할때 어떤식으로 값을 가져올지는 캡쳐([])에서 정한다.

        // [] 캡쳐(capture) : 함수 객체 내부에 변수를 저장하는 개념과 유사함.
        // 기본 캡쳐 모드 : 값(복사) 방식(=) 참조 방식(&)
        // - 값(복사) 방식 : 변수의 값을 가져와서 사용 -> 람다식 생성 이후 변수 값이 변해도 람다가 가져온 값은 안변함.
        // - 참조 방식 : 변수의 주소를 가져와서 사용 -> 람다식 생성 이후 변수 값이 변하면 람다가 가지고 있는 값도 변함.
        // 변수마다 캡처모드를 지정해서 사용 가능
        // 값 방식 : [name]
        // 참조 방식 : [&name]
        auto findByItemLambda = [=](Item &item)
            { return item._itemId == itemId; };

        // [&] 일때 클로저가 실행될때 비교될 값.
        itemId = 1;

        auto findIt2 = std::find_if(v.begin(), v.end(), findByItemLambda);
        if (findIt2 != v.end())
        {
            cout << "아이템 ID 다회성 람다 : " << findIt2->_itemId << endl;
        }
    }

    cout << "----------------------------------------------" << endl;

    {
        // 일반적인 함수 객체 선언 & 사용
        struct FindItem
        {
            FindItem(int itemId, Rarity rarity, ItemType type) 
                : _itemId(itemId), _rarity(rarity), _type(type)
            {

            }

            bool operator()(Item &item)
            {
                return item._itemId == _itemId && item._rarity == _rarity && item._type == _type;
            }

            int _itemId;
            Rarity _rarity;
            ItemType _type;
        };

        int itemId = 4;
        Rarity rarity = Rarity::Unique;
        ItemType type = ItemType::Weapon;

        auto findIt = std::find_if(v.begin(), v.end(), FindItem(4, Rarity::Unique, ItemType::Weapon));

        if (findIt != v.end())
        {
            cout << "아이템 종합 검색 함수 객체 : " << findIt->_itemId << endl;
        }

        // ! 람다 표현식(lambda expression)
        // [캡쳐](매개변수(인자)) {함수 구현부} -> 익명 함수를 생성
        // 변수마다 다르게 캡처모드를 설정한다.
        // itemId, type : 값(복사) 방식
        // rarity : 참조 방식
        // [=, &rarity] 대체 가능

        // []안에 캡처모드 방식을 써주는 것이 가독성과 &를 사용하여 주의해야함을 각인시킬 수 있다.
        auto findByItem = [itemId, &rarity, type](Item &item)
        {
            return item._itemId == itemId && item._rarity == rarity && item._type == type;
        };

        auto findIt2 = std::find_if(v.begin(), v.end(), findByItem);

        if (findIt2 != v.end())
        {
            cout << "아이템 ID 다회성 람다 : " << findIt2->_itemId << endl;
        }
    }

    // 람다의 캡처 모드가 = 여도 안전하지 않을 수 있음.
    {   
        class Knight
        {
        public:
            auto ResetHpJob()
            {   
                // 값(복사) 방식
                // this라고 써서 위함감을 줄 수 있음
                // = 만하면 안전하구나 라고 생각 들수 있음.
                auto f = [=/*this*/]() 
                {   
                    // 자신의 멤버 변수를 사용할때는 this-> 가 생략됨.
                    // 이해를 위해 명시적으로 적음.
                    this->_hp = 200;
                };

                return f;
            }

        public:
            int _hp = 100;
        };

        Knight* k = new Knight;
        // k 주소에 _hp를 수정하는 함수 객체 생성
        auto job = k->ResetHpJob();
        // k 메모리 해제
        delete k;
        // ! 메모리가 해제되었지만 k의 _hp 주소위치에 200이라고 값을 넣음.
        job();
    }

    return 0;
}