#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

void MergeResult(vector<int>& v, int left, int mid, int right);

// 힙 정렬 (Heap Sort) : O(NlogN)
// 힙 : 최대, 최소값을 구하는데 최적화
// 우선순위 큐를 사용하여 정렬하는 것
void HeapSort(vector<int>& v)
{
    // 작은 수부터 출력됨
    priority_queue<int, vector<int>, greater<int>> pq;

    // vector의 요소들을 pq에 저장함
    // O(log N) * O(N) = O(NlogN)
    for (int num : v)
    {
        pq.push(num);
    }

    // vector 정리
    v.clear();

    // 최소값부터 다시 vector에 저장함
    // O(log N) * O(N) = O(NlogN)
    while (pq.empty() == false)
    {
        v.push_back(pq.top());
        pq.pop();
    }

}

// 병합 정렬 (Merge Sort)  : O(NlogN)
// 분할 정복 (Divide and Conquer)
// 1) 분할(Divide)    : 문제를 더 단순하게 분할한다
// 2) 정복(Conquer)   : 분할된 문제를 해결, 한번만 분할하는 것이 아닌 해결하기 쉬울때까지 분할해도 괜찮음
// 3) 결합(Combine)   : 결과를 취합하여 마무리
//
// 트럼프 정리
// [3][K][7][2][J][4][8][9]  -> 8 * 1
// [3][K][7][2] / [J][4][8][9] -> 분할 : 두 2구간으로 나누어서 정렬함 4 * 2
// [2][3][7][K] / [4][8][9][J] -> 정복 : 각 구간끼리 정렬함
// 결합 : 각 구간에 앞에 있는 값끼리 비교하여 차례대로 결합한다
// [3][7][K] / [4][8][9][J]           [7][K] / [4][8][9][J]             [7][K] / [8][9][J]
// [2]                          ->    [2][3]                    ->      [2][3][4]        
// 
// [3][K][7][2] / [J][4][8][9] -> 4 * 2 분할 
// [3][K] / [7][2] / [J][4] / [8][9] -> 2 * 4 분할
// [3][K] / [2][7] / [4][J] / [8][9] -> 정렬
// [2][3][7][K] / [4][8][9][J] -> 4 * 2결합
void MergeSort(vector<int>& v, int left, int right)
{
    // 데이터가 없거나 1개인 상황
    if (left >= right)
        return;

    // O(N)
    int mid = (left + right) / 2; // 분할 위치
    MergeSort(v, left, mid);
    MergeSort(v, mid + 1, right);

    // 결과 결합
    // O(logN)
    MergeResult(v, left, mid, right);
}

// 결합
void MergeResult(vector<int>& v, int left, int mid, int right)  
{
    // [2][3][7][K] / [4][8][9][J]
    // [left]       / [right]

    int leftIdx = left;
    int rightIdx = mid + 1;
    vector<int> temp; // 결합된 결과를 저장할 vector
    
    // 왼쪽 구간과 오른쪽 구간이 값이 둘다 있을 때
    while (leftIdx <= mid && rightIdx <= right)
    {
        // 왼쪽 구간의 맨 앞에 있는 값이 오른쪽 구간의 맨 앞에 있는 값보다 작을때
        if (v[leftIdx] <= v[rightIdx])
        {
            // 작은 값을 temp에 저장
            temp.push_back(v[leftIdx]);
            leftIdx++;
        }
        else
        {
            temp.push_back(v[rightIdx]);
            rightIdx++;
        }
    }

    // 왼쪽 구간이 먼저 끝났으면 오른쪽 구간의 남은 값을 전달
    if (leftIdx > mid)
    {
        while (rightIdx <= right)
        {
            temp.push_back(v[rightIdx]);
            rightIdx++;
        }
    }
    // 오른쪽 구간이 먼저 끝났으면 왼쪽 구간의 남은 값을 전달
    else
    {
        while (leftIdx <= mid)
        {
            temp.push_back(v[leftIdx]);
            leftIdx++;
        }
    }
    
    // temp의 값을 v에 전달하여 반환함
    for (int i = 0; i < temp.size(); i++)
        v[left + i] = temp[i];
}

vector<int> Merge(vector<int> a, vector<int> b)
{
    vector<int> temp;

    int aIdx = 0;
    int bIdx = 0;
    // a와 b를 비교해서 값 저장
    while (aIdx <= a.size() - 1 && bIdx <= b.size() - 1)
    {
        if (a[aIdx] <= b[bIdx])
        {
            temp.push_back(a[aIdx]);
            aIdx++;
        }
        else
        {
            temp.push_back(b[bIdx]);
            bIdx++;
        }
    }

    // a혹은 b 중 하나가 먼저 완료되면 남은 하나를 그대로 저장함
    if (aIdx >= a.size())
    {
        while (bIdx <= b.size() - 1)
        {
            temp.push_back(b[bIdx]);
            bIdx++;
        }
    }
    else
    {
        while (aIdx <= a.size() - 1)
        {
            temp.push_back(a[aIdx]);
            aIdx++;
        }
    }


    return temp;
}

int main()
{
    vector<int> vec;//{5, 6, 4, 1, 3, 2};
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        int randValue = rand() % 100;
        vec.push_back(randValue);
    }

    // sort(vec.begin(), vec.end());

    // BuubleSort(vec);     O(N^2)
    // SelectionSort(vec);  O(N^2)
    // InsertionSort(vec);  O(N^2)
    // HeapSort(vec);       O(NlogN)
    MergeSort(vec, 0, vec.size() - 1);

    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }

    return 0;
}
