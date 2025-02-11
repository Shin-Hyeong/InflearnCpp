#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <Windows.h>

using namespace std;

// 동적 계획법(DP)
// LIS (Longest Increasing Sequence)

// Seq(수열) : 1 9 2 5 7
// 부분 수열 : 일분(0개 이상) 숫자를 지우고 남은 수열, 수열의 순서를 지켜야함(1 2 9 (X), 1 9 2(O))
// ex) 1 2 5
// ex) 1 9 5 7
//
// 순 증가 부분 수열 : 수가 점점 커지는 순서대로 나열된 부분 수열
// ex) 1 2 5 (O)
// ex) 1 9 7 7 (X)

// LIS : 가장 긴 순 증가 부분 수열의 길이 구하기
// 1 2 5 7 = 길이 4

vector<int> seq;
int cached[100];

// pos : seq의 몇번 인덱스부터 시작하는지 
// ex) pos = 0 -> 0번 인덱스인 1을 포함한 부분 수열
int LIS(int pos)
{
    // 예외 사항
    if (pos == seq.size() - 1)
        return 1;

    // 캐시 확인
    int& ref = cached[pos];
    if (ref != -1)
        return ref;

    // 구하기
    // Seq(수열) : 1 9 2 5 7
    // 1을 포함한 순 증가 부분 수열
    // 1 9 = LIS(1)를 호출
    // 1 9 를 포함한 순 증가 부분 수열 = 없음 = 2
    // 
    // 1 2 = LIS(2)를 호출
    // 1 2 를 포함한 순 증가 부분 수열
    // - 1 2 5 = LIS(3)를 호출
    // - 1 2 5를 포함한 순 증가 부분 수열
    // -- 1 2 5 7 = 4 
    // - 1 2 7
    // - 1 2 7를 포함한 순 증가 부분 수열
    // -- 1 2 7 = 3
    // 
    // 1 5 = LIS(3)를 호출
    // 1 5를 포함한 순 증가 부분 수열
    // - 1 5 7 = 3
    // 
    // 1 7 = LIS(4)를 호출
    // 1 7를 포함한 순 증가 부분 수열 = 없음 = 2

    // 정리
    // LIS(0)
    // 1 9 : LIS(0) -> LIS(1) = 2
    // 
    // 1 2 : LIS(0) -> LIS(2)
    // 1 2 5 : LIS(0) -> LIS(2) -> LIS(3)
    // 1 2 5 7 : LIS(0) -> LIS(2) -> LIS(3) -> LIS(4) = 4
    // - 이 시점에서 모든 LIS값을 cached에 저장함 -> 다시 계산한 필요없이 값을 가져와서 사용하면 됨.
    // 
    // 1 2 7 : LIS(0) -> LIS(2) -> LIS(4) = 3
    // 
    // 1 5 : LIS(0) -> LIS(3)
    // 1 5 7 : LIS(0) -> LIS(3) -> LIS(4) = 3
    // 
    // 1 7 : LIS(0) -> LIS(4) = 2


    // 최수 부분 수열인 자기 자신인 seq[pos]값을 가짐
    ref = 1; // 기본 값
    
    // pos 다음 인덱스부터 seq사이즈 만큼 반복
    for (int next = pos + 1; next < seq.size(); next++)
    {
        // 다음 인덱스가 pos의 값보다 작으면 안됨 -> 순 증가 부분 수열 조건
        if (seq[pos] < seq[next])
        {
            // 현재 순 증가 부분 순열 길이와  1 + LIS(다음 인덱스) 중 더 큰 값을 저장함
            ref = max(ref, 1 + LIS(next));
        }
    }

    return ref;
}

int main()
{
    // cached 배열을 -1로 초기화
    ::memset(cached, -1, sizeof(cached));

    seq = vector<int>{ 1, 9, 2, 5, 7 };

    int ref = 0;
    // 0번 인덱스부터 순환하여 seq의 LIS값을 얻음
    // - 0번 인덱스가 가장 큰 값일 시 무조건 1이 나오기 때문
    for (int pos = 0; pos < seq.size(); pos++)
    {
        ref = max(ref, LIS(pos));
    }
    
    cout << ref <<endl;

}
