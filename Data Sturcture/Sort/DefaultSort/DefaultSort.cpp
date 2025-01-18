#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

// 우선 순위 큐 : O(logN)
// Red-Black Tree : O(logN)
// Sort : ?

// 1) 버블 정렬 (Bubble Sort) : O(N^2)
// 바로 옆에 있는 값 끼리 비교하여 낮은 값을 가진 값이 왼쪽으로 이동함
// 한번 순회하면 가장 오른쪽 값이 가장 큰 값이 됨
// 가장 오른쪽 값을 제외하고 다시 버블 정렬을 진행함
// 
// 트럼프 카드 정렬
// [3][J][5][K][9] -> "[3][J]"[5][K][9] -> [3]"[5][J]"[K][9] -> [3][5]"[J][K]"[9]
// -> [3][5][J]"[9][K]" -> [3][5][J][9] / [K] K가 가장 큰값이라고 확정시킴
// "[3][5]"[J][9] / [K] 다시 처음부터 버블 정렬을 시작함

void BuubleSort(vector<int>& v)
{
    const int size = static_cast<int>(v.size()); // 벡터의 사이즈

    // i = 몇번쨰 순회인지
    for (int i = 0; i < size - 1; i++)
    {
        // 비교하고 있는 인덱스
        // 순회할 때마다 맨 끝에서 i만큼 안가도록 - i 해줌
        for (int j = 0; j < size - i - 1; j++)
        {
            if (v[j] > v[j + 1]) // 다음 값보다 크면 뒤로 보내야함
            {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }

}
// 2) 선택 정렬 (Selection Sort) : O(N^2), Bubble Sort보단 살짝 성능 좋음(교환하는 기능이 한번씩만 일어남)
// 전체 값을 스캔한 후 가장 작은값 or 큰 값 중 하나를 찾는다
// 작은 값을 찾았을 때) 찾은 값을 가장 왼쪽에 배치한다
// 큰 값을 찾았을 때) 찾은 값을 가장 오른쪽에 배치한다
// 이를 반복함
// 
// 트럼프 카드 정렬
// [3][J][5][K][9] -> 전체 스캔 -> "[3]"[J][5][K][9] -> 전체 스캔 -> [3]"[5]"[J][K][9]
// -> 전체 스캔 -> [3][5]"[9]"[K][J] -> 반복
void SelectionSort(vector<int>& v)
{
    const int size = static_cast<int>(v.size()); // 벡터의 사이즈

    // 몇번째 스캔인지
    for (int i = 0; i < size; i++)
    {
        // 가장 작은 값을 가진 인덱스
        int bestIdx = i;
        for (int j = i + 1; j < size; j++)
        {
            // bestIdx의 값보다 작은 값을 찾을 때마다 갱신함
            if (v[j] < v[bestIdx])
                bestIdx = j;
        }

        // 맨 앞부터 작은 값으로 교환함
        int temp = v[i];
        v[i] = v[bestIdx];
        v[bestIdx] = temp;
    }
}

// 3) 삽입 정렬 (Insertion Sort) : O(N^2)
// 정렬하고자 하는 배열을 임시로 구역을 나눔
// 정렬하고자 하는 배열에 값을 하나 뽑아서 임시로 저장해둠
// 정렬하는 구역에서 뒤에서부터 비교하면서 맞는 순서에 삽입함
//
// 트럼프 카드 정렬
// [3][J][5][K][9]
// [J]                        [5]                       [5]             [5]
// "[3][J]" / [5][K][9] ->    [3]"[J][5]" / [K][9]  ->  "[3][J]"[J] ->  [3][5][J] / [K][9]
void InsertionSort(vector<int>& v)
{
    const int size = static_cast<int>(v.size()); // 벡터의 사이즈

    // 0번째는 정렬할 것이 없기때문에 1번부터 시작
    for (int i = 1; i < size; i++)
    {
        int insertData = v[i];

        // 뒤부터 시작
        int j;
        for (j = i - 1; j >= 0; j--)
        {
            // 정렬시킬 값이 정렬된 값보다 작으면
            // 정렬된 값을 뒤로 보냄
            if (v[j] > insertData)
                v[j + 1] = v[j];
            // 정렬시킬 값이 정렬된 값보다 크면 더 이상 비교할 필요없음
            else
                break;
        }
        // 정렬된 위치에 저장
        v[j + 1] = insertData;
    }
}


int main()
{
    vector<int> vec{1, 5, 3, 4, 2, 6};

    // sort(vec.begin(), vec.end());
    
    // BuubleSort(vec); 
    // SelectionSort(vec);
    InsertionSort(vec);

    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }

    return 0;
}
