#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

// 이진 트리
// - 자식 노드가 2개 이하인 노드
// - 왼쪽 자식과 오른쪽 자식으로 나뉨
// -- 왼쪽 자식은 부모보다 작은 값을 가짐
// -- 오른쪽 자식은 부모보다 큰 값을 가짐

// 완전 이진 트리
// - 마지막 레벨을 제외한 모든 레벨에 노드가 꽉 차 있다
// -- 마지막 레벨에 노드가 있을 때는, 항상 왼쪽부터 순서대로 채워야한다.

// 이진 트리의 문제 : 그냥 무식하게 추가하면, 한쪽으로 기울어져서 균형이 깨짐.
// -> 트리 재배치를 통해 균형을 유지하는것이 관건


// 힙 트리 : 최대값과 최소값을 찾을 때 유용함. 우선순위 큐에 사용함. O(log(n)), 
// - 부모노드가 가진 값은 항상 자식 노드가 가진 값보다 크다. -> Root는 가장 큰 수를 가진다
// -- 이진트리보다 조건이 쉬움
// - 노드 개수를 알면, 트리 구조는 무조건 확정할 수 있다. (완전 이진 트리)
// -- 구조가 고정되어 있기 때문에 배열을 이용해서 힙 구조를 바로 표현 할 수 있다.
// --- i 번째 노드의 왼쪽 자식은 (2 * i) + 1번노드이다.
// --- i 번째 노드의 오른쪽 자식은 (2 * i ) + 2번노드이다.
// --- i 번쨰 노드의 부모는 (i - 1) / 2번노드이다.

// 힙트리에 새로운 값을 추가할때 순서
// - 우선 트리 구조(완전 이진 트리)에 맞게 새로운 값을 배치한다.
// - 새로 배치된 값과 부모노드의 값을 비교하여 더 큰 값을 부모로 배치한다.
// -- 부모노드가 가진 값이 자식 노드가 가진 값보다 커질 때까지 반복한다.

// 힙 트리에서 값을 제거할때 순서
// - 힙 트리에선 어느 특정 노드를 제거할 수 있는 것이 아닌 Root노드만 제거 가능함 -> 최대값 꺼내기
// - 최대값을 제거한다
// - 힙 트리중 가장 마지막에 위치한 데이터를 Root로 옳긴다.
// - Root루트(부모노드)와 자식노드(왼쪽 자식과 오른쪽 자식 중 더 큰 값을 가진 노드)와 비교하여 더 큰 값을 부모노드로 설정한다.
// -- 부모노드가 가진 값이 자식 노드가 가진 값보다 커질 때까지 반복한다.

// ! 데이터 구조상 Root를 제거하면 트리 구조가 깨지기 때문에 이론상의 제거 방식과 실질적 구조는 다름
// - 최대값을 가진 Root노드와 최 하단의 노드와 데이터를 교환한다.
// - 최 하단으로 옮겨진 최대값을 가진 노드를 제거한다.
// - 최 하단 값을 가진 Root 노드와 자식 노드의 값을 비교하면서 더 큰 값을 부모노드로 교체한다.
// -- 부모노드가 가진 값이 자식 노드가 가진 값보다 커질 때까지 반복한다.

template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class PriorityQueue
{
public:
    void push(const T& data)
    {
        // 힙 트리 구조의 맨 마지막 구조에 배치함 -> 힙 트리 구조부터 맞춘다.
        _heap.push_back(data);

        // 부모노드와 자식의 크기를 비교를 반복함

        // 현재 추가된 노드의 번호
        int now = static_cast<int>(_heap.size()) - 1;

        // 루트 노드까지 시도
        while (now > 0)
        {
            // 부모 노드와 비교해서 더 작으면 False
            int parent = (now - 1) / 2;

            // 추가된 노드가 부모노드보다 작음 -> 알맞는 위치임
            // if (_heap[now] < _heap[parent]) -> 하드 코딩됨
            if(_predicate(_heap[now], _heap[parent]))
                break;

            // 추가된 노드가 부모노드보다 큼 -> 데이터 교체 필요
            ::swap(_heap[now], _heap[parent]); // 부모 노드와 값 교체
            now = parent; // 부모 노드와 노드 번호 교체
        }

    }

    void pop()
    {   
        // Root 데이터를 최하단 데이터로 덮어씌움 -> root 데이터 삭제
        _heap[0] = _heap.back();
        // 최하단 데이터를 삭제 -> 힙 트리구조를 맞춘다.
        _heap.pop_back();

        int now = 0;

        // 자식 노드와 크기 비교 시작
        while (true)
        {
            // 왼쪽 자식
            int leftChild = 2 * now + 1;
            // 오른쪽 자식
            int rightChild = 2 * now + 2;

            // 왼쪽 자식이 있는지 확인
            if (leftChild >= _heap.size())
                break;

            // next = 최종적으로 이동해야하는 위치
            int next = now;

            // 왼쪽 자식과 비교함 -> 더 작은 수가 자식이 됨.
            // if (_heap[next] < _heap[leftChild]) -> 하드 코딩됨.
            if(_predicate(_heap[next], _heap[leftChild]))
                next = leftChild;

            // 오른쪽 자식이 있는지 확인
            // 왼쪽 자식과 비교후 더 작은 값과 오른쪽 자식의 값과 비교함
            // if (rightChild < _heap.size() && _heap[next] < _heap[rightChild]) -> 하드코딩됨
            if (rightChild < _heap.size() && _predicate(_heap[next], _heap[rightChild]))
                next = rightChild;

            // 왼쪽 자식, 오른쪽 자식 둘다 부모노드보다 작음
            if (next == now)
                break;

            // 왼쪽 자식, 오른쪽 자식 중 더 큰 값이 자식이 있음
            ::swap(_heap[now], _heap[next]); // 자식 노드와 값 교체
            now = next; // 자식 노드와 노드 번호 교체
        }
    }

    T& top()
    {
        return _heap[0];
    }

    bool empty()
    {
        return _heap.empty();
    }

private:
    Container _heap = {};
    Predicate _predicate = {};
};


int main()
{
    // 우선순위 큐
    // push하면 큰 수대로 정렬됨.
    // priority_queue은 <>안에 여러 인자를 받음
    // - <자료형 타입, 자료구조, 정렬 방법>
    // -- 기본 priority_queue <T, vector<T>, less<T>> -> 큰 수부터 배출
    // -- priority_queue<T, vector<T>, greater<T>> -> 작은 수 부터 배출
    
    // priority_queue<int> pq;
    // priority_queue<int, vector<int>, greater<int>> pq;

    PriorityQueue<int, vector<int>, greater<int>> pq;


    pq.push(100);
    pq.push(300);
    pq.push(200);
    pq.push(500);
    pq.push(400);

    while (pq.empty() == false)
    {
        int value = pq.top();
        pq.pop();

        cout << value << endl;
        // less
        // 500, 400, 300, 200, 100
        // greater
        // 100, 200, 300, 400, 500
    }

    return 0;
}

