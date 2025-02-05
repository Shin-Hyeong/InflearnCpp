#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <Windows.h>


using namespace std;

// 동적 계획법 : Dynamic Programming(DP)
// 게임 같은 콘텐츠 제작에서는 잘 사용하진 않지만
// 기계적으로 다가갈수록 많이 사용함(AI, 등 Low한 작업)

// 이항 계수 : Combination
// DP를 사용하는 대표적이 예
// 상자 안에 번호가 적힌 공 5개가 있다. 공 2개를 뽑는 경우의 수
// Conbination(n, k) : nCk   (n : 공 개수, k : 뽑아야하는 개수)
// 
// 방법 1) n! / k!(n - k)!
// = (5 * 4 * 3 * 2 * 1) / (2 * 1)(3 * 2 * 1) = 10
// 
// 방법 2) (n - 1, k - 1) + (n - 1, k - 1)
// = (5, 2) = (4, 2) + (4, 1) = ((4 * 3) / 2) + 4 = 6 + 4 = 10
// 
// (4, 2) -> 특정 공을 제외하고 뽑아야함 -> 나머지 4개중 2개를 뽑음
// 4부터 1까지 1씩 내려가는 수를 곱하는데 2번함 = 4 * 3
// 
// (4, 1) -> 특정 공을 포함하고 뽑아야함 -> 나머지 4개중 1개를 뽑음
// 4부터 1까지 1씩 내려가는 수를 곱하는데 1번함 = 4 

int g_count;

// 방법2 구현
// 재귀함수를 통해 구현함
// combination(2,1), combnation(1,0), combination(0,0)등 중복으로 구하는 상황이 있음
// combation(45, 6)의 경우 : 실행 속도 46ms, n == 2 && k == 1인 상황이 962,598번 일어남
// - 반복적으로 계산하는 구간을 따로 저장하여 한번만 계산하도록 한다

// 메모이제이션 (Memoization) : 계산한 결과값을 임시 저장해둠 (n이 50을 안넘는 가정하에 32비트 int으로 생성)
// - 메모이제이션을 사용하여 combination(45, 6)을 사용한 경우 : 실행속도 0ms, n == 2 && k == 1인 상황이 1번 일어남
// - combination에 입력되는 숫자가 커지거나, 매개변수 수가 들어날 수록 메모이제이션을 할당하기 위한 메모리가 부담스러울수 있음.
int cached[50/*n*/][50/*k*/];

int combination(int n, int k)
{
    // 시도할려는 횟수가 0이거나 전체의 값과 같으면 1
    if (k == 0 || n == k)
        return 1;

    // 이미 답을 구한 적 있으면 바로 반환
    int& ref = cached[n][k];
    // -1이 아니면 이미 구한 값이 있음
    if (ref != -1)
        return ref;

    // combination(2, 1) 계산한 횟수 카운트
    if (n == 2 && k == 1)
        g_count++;

    // 새로 답을 구해서 캐시에 저장
    // -1인 ref에 새로운 값을 저장하여 계산한 값을 넣음
    ref = combination(n - 1, k - 1) + combination(n - 1, k);
    return ref;
}

int main()
{
    // cached를 -1로 전체 초기화
    memset(cached, -1, sizeof(cached));

    __int64 start = ::GetTickCount64();
    int lotto = combination(45, 6);

    __int64 end = ::GetTickCount64();

    
    cout << end - start << "ms" <<  endl; // 경과 시간
    cout << g_count << endl;              // combination(2,1) 실행 횟수

    return 0;
}