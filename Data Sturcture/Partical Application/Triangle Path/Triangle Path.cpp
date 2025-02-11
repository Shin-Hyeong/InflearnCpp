#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <Windows.h>

using namespace std;

// 동적 계획법(DP)
// Triangle Path
// - (0, 0)부터 시작해서 아래 or 아래 우측(5시 방향 대각선)으로 이동 가능
// - 이동하면서 만나는 숫자를 모두 더함
// - 더한 숫자가 최대가 되는 경로의 합

// 6                |
// 1 2              |  
// 3 7 4            |   y
// 9 4 1 7          |
// 2 7 5 9 4        |
// ㅡㅡㅡㅡㅡㅡㅡㅡㅡ
//        x

// ex) 6 + 1 + 3 + 9 + 2 = 21
// ex) 6 + 1 + 7 + 1 + 9 = 24

int N; // board의 크기 = N * N
vector<vector<int>> board;      // 경로의 값을 가진 vector
vector<vector<int>> cached;     // 지나가는 경로의 triangle path를 저장한 vector
vector<vector<int>> nextX;      // 지나간 경로 X값을 저장한 vector

// cache 문제에선 구해야하는 문제를 반환하여 재귀하는것이 좋음
int path(int y, int x)
{
    // 예외 사항
    if (y == N) // vector의 범위를 벗어나면 0으로 반환
        return 0;

    // 캐시 확인
    int& ref = cached[y][x];
    if (ref != -1)
        return ref;

    // 구하기
    // path(0, 0) -> path(1, 0), path(1, 1)
    // - path(1, 0) -> path(2, 0), path(2, 1)
    // - path(1, 1) -> path(2, 1), path(2, 2)
    // -- path(2, 0) -> path(3, 0), path(3, 1)
    // -- ...
    // 
    // path(y + 1, x);         // 아래 방향으로 이동
    // path(y + 1, x + 1);     // 아래 우측 방향으로 이동

    // 경로 기록 -> y는 무조건 +1이기 때문에 x좌표만 저장하면 됨
    int nextBottom = path(y + 1, x);
    int nextBottomRight = path(y + 1, x + 1);
    // 아래 방향 경로와 아래 우측 방향경로 비교후 좌표 저장
    // 다음 경로가 어디로 가는지 저장함
    if (nextBottom > nextBottomRight)
        nextX[y][x] = x;
    else
        nextX[y][x] = x + 1;

    // [y][x]좌표 값과 아래 방향 or 아래 우측방향의 path값 중 큰값을 반환함
    return ref = board[y][x] + max(nextBottom, nextBottomRight);
}

int main()
{
    board = vector<vector<int>>
    {
        {6},
        {1, 2},
        {3, 7, 4},
        {9, 4, 1, 7},
        {2, 7, 5, 9, 4}
    };

    N = board.size();
    cached = vector<vector<int>>(N, vector<int>(N, -1));
    nextX = vector<vector<int>>(N, vector<int>(N));

    int ref = path(0, 0);
    cout << ref << endl;
    
    // 어떤 경로를 지나갔는지 확인
    int y = 0;
    int x = 0;
    while (y < N)
    {
        cout << board[y][x] << "->";

        // 다음 경로의 x좌표를 가져옴
        x = nextX[y][x];
        y++;
    }
}
