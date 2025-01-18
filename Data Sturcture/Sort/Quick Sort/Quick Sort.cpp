#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

int Partition(vector<int>& v, int left, int right);

// 퀵 정렬 (Quick Sort) : O(NlogN)
// 배열의 시작점(왼쪽)을 left, 끝 점(오른쪽)을 right라고 함
// 배열의 맨 왼쪽 요소를 Pivot으로 지정한다
// 배열에서 Pivot을 제외한 가장 왼쪽 요소를 low라고 한다
// 배열에서 가장 오른쪽 요소를 high라고 한다
// 1) Pivot과 low를 비교하고 Pivot >= arr[low]이면 low를 오른쪽으로 이동
//    Pivot과 high를 비교하고 Pivot <= arr[high]이면 high를 왼쪽으로 이동
// 2) low와 high가 모두 멈춘 상태에서 low < high 이면 arr[low]와 arr[high]의 데이터 교체
// 3) higt <= low이면 반복문을 빠져나오고 Pivot과 arr[high]의 데이터를 교체
// - Pivot이였던 값은 크기 맞는 위치에 찾게 되고 
// - 그값의 왼쪽은 Pivot이였던 값보다 작은값이 있고 오른쪽은 Pivot이였던 값보다 큰값이 있다.
// - 각 구간을 퀵정렬 하면 된다.

// 퀵정렬 : O(NlogN), 힙 정렬 : O(NlogN), 병합정렬 : O(NlogN)
// 셋다 O(NlogN)이지만 실질적 성능은 퀵정렬이 좋음
// - 힙 정렬은 입력한 배열의 크기만큼 priorityQueue를 생성해야함
// - 병합 정렬은 결합되는 과정에서 임시 배열을 생성함
// - 둘다 추가적인 메모리를 사용해야함
// -- 퀵 정렬은 받은 배열의 데이터를 교환하는 식이기 떄문에 추가적인 메모리를 사용하지 않음


// [5][1][3][7][9][2][4][6][8]
// [p]
//    [L]->              <-[H]

// 정렬했더니 Pivot이 가장 왼쪽 값(최소값)이 되던가 가장 오른쪽 값(최대 값)이였을 경우 최악의 상황이 됨 -> O(N^2)
// 평균적으로 정렬했더니 Pivot이 중앙에 정렬되면 O(NlogN)
void QuickSort(vector<int>& v, int left, int right)
{
    // 재귀함수를 종료시키기 위함
    if (left > right)
        return;

    // 기준 점을 반환 받음
    int pivot = Partition(v, left, right);
    // pivot보다 낮은 값이 있는 구간
    QuickSort(v, left, pivot - 1);
    // pivot보다 큰 값이 있는 구간
    QuickSort(v, pivot + 1, right);
}

int Partition(vector<int>& v, int left, int right)
{
    int pivot = v[left];
    int low = left + 1;
    int high = right;

    // O(N) : 이중 반복문이지만 실질적으로 while을 돌때 계속 처음부터 실행되는게 아니라
    //        지나간 구간은 제외하고 실행하기 때문에 O(N^2)이 아닌 O(N)이다
    // low가 high보다 크지 않으면
    while (low <= high)
    {
        // 1 단계
        // v[low]값이 pivot값보다 작으면 
        while (low <= right && pivot >= v[low])
            // low을 오른쪽으로 넘김
            low++;
        // v[high]값이 pivot값보다 크면
        while (high >= left + 1 && pivot <= v[high])
            // high을 왼쪽으로 넘김
            high--;

        // 2 단계
        // v[low]값은 pivot보다 크고, v[high]값은 pivot보다 작은 상태임
        // v[low]와 v[high]값을 서로 교환함 -> v[low]에는 pivot보다 작은 값이, v[high]에는 pivot보다 큰값이 들어감
        if (low < high)
            swap(v[low], v[high]);
    }
    // low와 high가 교차되는 순간 while에서 빠져나옴
    // 3단계
    // pivot과 v[higt]의 데이터를 교환함
    swap(v[left], v[high]);

    // 위치가 고정된 값이 기준이 되어 분할되기 때문에 기준을 반환해줌
    return high;
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

    QuickSort(vec, 0, static_cast<int>(vec.size()) - 1);

    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }

    return 0;
}

