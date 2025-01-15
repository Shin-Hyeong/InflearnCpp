#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include "Red_BlackTree.h"
#include <thread>

using namespace std;

// Red_BlackTree
// 이진탐색트리와 비슷하고 트리의 균형을 맞춤
// 새로 추가된 노드는 레드를 가지고 시작함 -> 이후 규칙에 맞게 변경됨
// 1)노드는 무조건 레드 혹은 블랙 중 하나임
// 2) 루트는 블랙임
// 3) 모드 리프(NIL) 노드들은 블랙임
// - NIL : 자식이 없을 때 Nullptr대신 아무런 값을 가지않는 더미 노드로 대체함
// 4) 레드 노드의 자식 노드 양쪽 언제나 모두 블랙이다
// - 블랙노드의 자식이 블랙인 것은 상관없음
// - 레드 노드는 연달아 나타날 수 없고, 블랙 노드만이 레드 노드의 부모노드가 될 수 있다.
// 5) 어떤 노드로부터 시작되어 그에 속한 하위 리프 노드(NIL)에 도달하는 모든 경로에는
//   모든 같은 개수의 블랙 노드가 있다.

// 3, 4번이 레드블랙트리의 특성임
// - 해당 특성이 어긋나면 트리 재구성이 이루어짐



int main()
{
    Red_BlackTree rbt;
    rbt.Insert(20);
    rbt.Print();
    // 1초 동안 잠시 멈춤
    this_thread::sleep_for(1s);

    rbt.Insert(10);
    rbt.Print();
    // 1초 동안 잠시 멈춤
    this_thread::sleep_for(1s);

    rbt.Insert(30);
    rbt.Print();
    // 1초 동안 잠시 멈춤
    this_thread::sleep_for(1s);

    rbt.Insert(5);
    rbt.Print();
    // 1초 동안 잠시 멈춤
    this_thread::sleep_for(1s);

    rbt.Insert(15);
    rbt.Print();
    // 1초 동안 잠시 멈춤
    this_thread::sleep_for(1s);

    rbt.Insert(25);
    rbt.Print();
    // 1초 동안 잠시 멈춤
    this_thread::sleep_for(1s);

    rbt.Insert(35);
    rbt.Print();
    // 1초 동안 잠시 멈춤
    this_thread::sleep_for(1s);

    rbt.Insert(50);
    rbt.Print();
    // 1초 동안 잠시 멈춤
    this_thread::sleep_for(1s);

    rbt.Insert(47);
    rbt.Print();
    // 1초 동안 잠시 멈춤
    this_thread::sleep_for(1s);

    rbt.Insert(60);
    rbt.Print();
    // 1초 동안 잠시 멈춤
    this_thread::sleep_for(1s);

    rbt.Delete(47);
    rbt.Print();
    this_thread::sleep_for(1s);

    rbt.Delete(35);
    rbt.Print();
    this_thread::sleep_for(1s);

    rbt.Delete(25);
    rbt.Print();
    this_thread::sleep_for(1s);
}
