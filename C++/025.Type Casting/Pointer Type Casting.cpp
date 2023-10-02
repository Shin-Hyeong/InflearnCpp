#include <iostream>
#include <ctime>

using namespace std;

// 타입 변환 (포인터)
// ![결론]
// - 포인터 vs 일반 타입
// -- 포인터 : 원본의 주소를 가지고 원본을 수정한다.
// -- 일반 타입 : 매개변수(지역변수)를 생성하고 원본의 데이터를 매개변수에 복사해서 수정한다.
// - 포인터 사이의 타입 변환을 할때는 매우 조심해야 한다.
// ! - 부모-자식 관계에서 부모 클래스의 소멸자에는 까먹지 말고 virtual을 붙이자
// ! -- 부모-자식 관계에서 타입 변환에 의해서 변환되고
// ! -- 처음 생성한 타입의 소멸자를 호출시 원본 소멸자가 아닌 처음 생성한 타입의 소멸자만 호출하게 됨.

class Knight
{
public:

public:
    int _hp = 0;
};

class Item
{
public:
    // 기본 생성자
    Item()
    {
        cout << "Item()" << endl;
    }

    // 아이템 타입을 인자값으로 받아서 멤버 변수에 넣어줌.
    Item(int itemType) : _itemType(itemType)
    {
        cout << "Item(int itemType)" << endl;
    }

    // 복사 생성자
    Item(const Item& item)
    {
        cout << "Item(const Item&)" << endl;
    }
    // 소멸자
    virtual ~Item()
    {
        cout << "~Item()" << endl;
    }

public:
    int _itemType = 0;
    int _itemDbId = 0;

    // 실전에서 이런저런 변수를 선언해서 비대해진 class를 나타내기 위함.
    char _dummy[4096] = {};
};

enum ItemType
{
    IT_WEAPON = 1,
    IT_ARMOR = 2
};

class Weapon : public Item
{
public:
    Weapon() : Item(IT_WEAPON)
    {  
        cout << "Weapon()" << endl;
        _damage = rand() % 100; // 0 ~ 100
    }
    virtual ~Weapon()
    {
        cout << "~Weapon()" << endl;
    }
public:
    int _damage = 0;
};

class Armor : public Item
{
public:
    Armor() : Item(IT_ARMOR)
    {
        cout << "Armor()" << endl;
    }
    virtual ~Armor()
    {
        cout << "~Armor()" << endl;
    }
public:
    int _defense = 0;
};

// 포인터를 사용하지 않으면 Item의 멤버 변수가 복사되는 개념.
// 지역 변수로 복사 생성자를 통해item이 생성됨.
// 종료되면 소멸자를 호출함.
void TestItem(Item item)
{

}

// 복사(부하) 없이 item의 원본을 건드릴수 있다.
void TestItemPtr(Item* item)
{

}


int main()
{   
    // ! 복습
    {
        {
            // Stack [ type(4) dbId(4) dummy(4096)] = 4014 byte
            // 자동으로 소멸자를 생성함.
            Item item;

            // Stack [ 주소(4 or 8byte) ] = 8byte -> Heap [ type(4) dbId(4) dummy(4096) ]
            // item2 = Item class 타입을 가르키는 포인터 변수
            // 수동으로 소멸자를 생성해줘야 함.
            Item* item2 = new Item();
            
            // 4014 byte가 복사됨
            TestItem(item);
            TestItem(*item2);

            // 복사 없이 진행됨.
            TestItemPtr(&item);
            TestItemPtr(item2);

            // 메모리 누수(Memory Leak) -> 점점 가용 메모리가 줄어들어서 Crash 발생
            delete item2;
        }

        // 배열
        {
            cout << "---------------------------------------------" << endl;

            // 진짜 class Item이 100개 선언 된것 (스택 메모리에 올라와 있다)
            // 바로 생성자를 100개를 부름
            Item item3[100] = {};

            cout << "---------------------------------------------" << endl;

            // ? class Item이 100개 선언되었을까?
            // 아이템을 가르키는 변수가 100개가 선언된 것. 실제로 class Item이 1개도 선언 되지 않았을 수도 있음.
            Item* item4[100] = {};

            // 동적할당으로 class Item를 선언
            for (int i = 0; i < 100; i++)
                item4[i] = new Item();

            cout << "---------------------------------------------" << endl;
            
            // 동적할당된 class Item를 소멸자 호출.
            for (int i = 0; i < 100; i++)
                delete item4[i];

            cout << "---------------------------------------------" << endl;
        }
    }
    

    srand((unsigned int)time(nullptr));
    
    // 연관성이 없는 클래스 사이의 포인터 변환 테스트
    {   
        // Stack [ 주소 ] -> Heap [ _hp(4byte) ]
        Knight* knight = new Knight();
        
        // item이 Knight의 주소를 참조함.
        // 암시적으로 NO, 명시적으로 OK
        // Stack [ 주소 ] 
        Item* item = (Item*)knight;
        // 메모리상 0번 오프셋인 _hp가 차지하고 있던 위치를 수정하는 것 -> OK
        item->_itemType = 2;
        // ! 메모리상 knight가 할당 받지 못한 위치를 수정하는 것 -> NO
        item->_itemDbId = 1;

    }

    // 부모 -> 자식 변환 테스트
    {
        Item* item = new Item();
        // 암시적으로 NO, 명시적으로 OK
        // [[ item ] _damage ]
        // [ item ] (_damage 위치)
        Weapon* weapon = (Weapon*)item;
        // 할당된 메모리를 벗어난 위치를 건드림
        weapon->_damage = 10;

        delete item;
    }

    // 자식 -> 부모 변환 테스트
    {
        Weapon* weapon = new Weapon();
        // 암시적으로 해도 가능.
        Item* item = weapon;
        // 두 멤버 변수 Weapon이 할당 받은 메모리에서 수정됨.
        item->_itemType = 4;
        item->_itemDbId = 3;

        delete weapon;
    }
    
    // ! 명시적으로 타입 변환할때는 항상 조심해야 한다.
    // ? 암시적으로 될 때는 안전한가? -> 평생 명시적으로 타입 변환은 안하면 되는거 아닌가?
    {   
        // 내용물이 있을수도 있고 없을수도 있음. 있으면 실제 아이템을 들고 있고, 없으면 = nullptr
        Item* inventory[20] = {};
                
        for (int i = 0; i < 20; i++)
        {
            int randValue = rand() % 2; // 0 ~ 1
            switch (randValue)
            {
            case 0 :
                // 자식 -> 부모 변환
                // Item* inventory[i] = new Weapon();
                // _itemType = IT_WEAPON이 이루어짐.
                inventory[i] = new Weapon();
                break;
            case 1 :
                // 자식 -> 부모 변환
                // Item* inventory[i] = new Armor();
                // _itemType = IT_ARMOR가 이루어짐.
                inventory[i] = new Armor();
                break;
            }
        }

        for (int i = 0; i < 20; i++)
        {   
            // inventory[] 주소를 가지는 item 포인터 변수 생성
            Item* item = inventory[i];
            if (item == nullptr)
                continue;
            
            if (item->_itemType == IT_WEAPON)
            {
                // 부모 -> 자식 변환
                // 안전 1) item이 원본은 switch문에서 선언한 Weapon형태를 가지고 있음.
                // 안전 2) _itemType가 Weapon를 가르킴.

                // 문제 1) _itemType이 잘못 된 경우
                Weapon* weapon = (Weapon*)item;
                cout << "Weapon Damage : " << weapon->_damage << endl;
            }
        }

        // ! ********************* 매우 중요 *******************************
        for (int i = 0; i < 20; i++)
        {
            // inventory[] 주소를 가지는 item 포인터 변수 생성
            Item *item = inventory[i];
            if (item == nullptr)
                continue;

            // 맨처음 Item으로 만들어서 Weapon과 Armor로 나누어서 변환하였기 떄문에
            // 원본은 Weapon과 Armor로 되어 있음.
            // ! Item의 소멸자를 불러오면 _damage와 _defense는 소멸을 못 시킴.
            // delete item;

            // 방법 1) 각 Inventory의 원본에 맞는 소멸자를 호출해야함.
            // if (item->_itemType == IT_WEAPON)
            // {
            //     Weapon* weapon = (Weapon*)item;
            //     delete weapon;
            // }
            // else
            // {
            //     Armor* armor = (Armor*)item;
            //     delete armor;
            // }

            // 방법 2) 소멸자에 virtual을 붙여 가상함수로 만들고 
            // 소멸자(함수)를 호출하면 원본에 맞는 소멸자를 호출하게 됨.
            delete item;
        }
    }

    return 0;
}