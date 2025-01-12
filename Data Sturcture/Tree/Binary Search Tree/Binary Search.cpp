#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

#include "BinarySearchTree.h"
using namespace std;

// 이진 탐색 트리

// 이진 탐색
// 업다운 방식으로 값을 찾기 O(log n)
// - 정렬되어 있는 배열에 특정 값을 찾는다.
// [1][8][15][23][32]/[44][56][63][81][91]
// - 배열에서 중간값을 기준으로 찾고자하는 값이 작은지 큰지 확인함
// - 값이 작으면(크면) 중간값보다 작은 구간(큰 구간)에서 중간값과 찾고자하는 값을 비교한다.
// -- 이를 반복하여 값을 찾는다
// 트리가 한쪽으로 몰리면 굳이 이진 탐색 트리를 사용할 이유가 없음

// - 정렬되지 않은 배열은 탐색 불가능
// - 정렬된 연결 리스트로는 불가 (임의 접근이 불가능함)
// -- 배열은 중간 삽입/삭제가 느림 -> 탐색해서 추가, 삭제, 변경이 어려움 -> 트리 방식(노드 방식)으로 만들어 유동성을 챙김.

vector<int> numbers;

// 이진 탐색
void BinarySearch(int N)
{
    // 검색할 범위
    int left = 0;
    int right = numbers.size() - 1;

    // left가 right보다 작거나 같으면 
    while (left <= right)
    {
        cout << "탐색 범위 : " << left << " ~ " << right << endl;

        // 배열의 중간 위치의 배열 (소수점 내림)
        // (0 + 9) / 2 = 4 -> 32
        int mid = (left + right) / 2;

        // N이 32보다 작음
        if (N < numbers[mid])
        {
            cout << N << " < " << numbers[mid] << endl;
            right = mid - 1;
        }
        // N이 32보다 큼
        else if (N > numbers[mid])
        {
            cout << N << " > " << numbers[mid] << endl;
            left = mid + 1;
        }
        // N = 32임
        else
        {
            cout << "찾음" << endl;
            break;
        }
    }
}

int main()
{
    // numbers = vector<int>{ 1, 8, 15, 23, 32, 44, 56, 63, 81, 91 };
    // BinarySearch(81);

    //    [20]
    //  [10] [30]
    //[5][15][25][35]
    BinarySearchTree bst;
    bst.Insert(20);
    bst.Insert(10);
    bst.Insert(30);
    bst.Insert(5);
    bst.Insert(15);
    bst.Insert(25);
    bst.Insert(35);


    // bst.Print_Inorder();
    // bst.Delete(20);
    bst.Print();
    // cout << endl <<  bst.Next(bst.Search(bst.GetRoot(), 15))->key << endl;


}
