#include <iostream>
using namespace std;

// 콜백(Callback)
// 함수 포인터 + 함수 객체 + 템플릿
// 다시 호출하다. 역으로 호출하다. 나중에 호출하다
// 어떤 상황이 일어나면 -> 이 기능을 호출해달라.
// ex) 특정 스킬버튼을 누르면 -> 스킬을 쓰는 함수를 호출

class Item
{
public:

public:
    int _itemId = 0;
    int _rarity = 0;
    int _ownerId = 0;
};

// OwnerID를 받아서 검색하는 class
class FindByOwnerID
{
public:
    bool operator()(const Item* item)
    {
        return (item->_ownerId == _ownerId);
    }

public:
    int _ownerId;
};

// Rarity를 받아서 검색하는 class
class FindByRarity
{
public:
    bool operator()(const Item *item)
    {
        return (item->_rarity == _rarity);
    }

public:
    int _rarity;
};

// 특정 조건을 받아서 Item을 검색하는 class
// 검색 조건이 특정된 것(함수 포인터)만이 아닌 함수객체를 템플릿으로 받아서 여러 조건을 받을 수 있도록 함.
template<typename T>
Item* FindItem(Item items[], int itemCount, T selector)
{
    for (int i = 0; i < itemCount; i++)
    {
        Item* item = &item[i];
        if (selector(item))
            return item;

        return item;
    }
    return nullptr;
}

int main ()
{
    Item items[10];
    items[3]._ownerId = 100;
    items[6]._rarity = 1;

    FindByOwnerID functor1;
    functor1._ownerId = 100;

    FindByRarity functor2;
    functor2._rarity = 1;

    // OwnerID를 통해서 검색
    cout << FindItem(items, 10, functor1) << endl;

    // Rarity를 통해서 검색
    cout << FindItem(items, 10, functor2) << endl;

    return 0;
}