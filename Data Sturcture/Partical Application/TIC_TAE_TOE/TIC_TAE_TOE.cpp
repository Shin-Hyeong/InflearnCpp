#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <Windows.h>

using namespace std;

// 동적 계획법
// TIC_TAE_TOE

// [o][x][.]
// [.][o][x]
// [.][.][o]
// 1차 배열로 변환
// [o][x][.][.][o][x][.][.][o] -> [./o/x] 3(0,1,2)가지가 들어감
// 3가지 케이스만 가질수 있는 칸이 총 9칸 있음 -> 3^9 = 19683

// 현재 board 상태(2차원 배열 + 한칸에 3가지 종류가 들어갈 수 있음)를 1차원 배열로 만듦
// HashKey -> 0 ~ 3^9(19683)의 사이값이 도출됨
int HashKey(const vector<vector<char>>& board)
{
    int ref = 0;

    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            // 3을 곱하는 이유 = 유니크한 값을 추출하기 위함
            // 다음 좌표의 값을 저장할때 공간을 나누기 위함 -> 한칸에 ,/o/x의 3종류가 들어갈수 있기 때문에 3을 곱함
            // 다음 칸을 저장할 때 기존에 있던 값을 앞으로 밀어냄
            // [012][012][012][012]
            //   27   9    3    0  
            // 'o' = {[][ref][]} = 1
            // -> ref * 3 = {[][][ref]}{[][이전 ref][]}                   = 1 * 3         = 3
            // -> 'x'     = {[ref][][]}{[][이전 ref][]}                   = 1 * 3 + 2     = 5
            // -> ref * 3 = {[][][ref]} ... {[이전 ref][][]}{[][][]}      = 5 * 3         = 15
            // -> 'x'     = {[ref][][]} ... {[이전 ref][][]}{[][][]}      = 5 * 3 + 2     = 17
            ref = ref * 3;

            // if (board[y][x] == '.')        ref에 아무런 값이 없으면 ref 증가 없음
            if (board[y][x] == 'o')         // o 이면 ref을 1증가 
                ref += 1;
            else if (board[y][x] == 'x')    // x이면 ref을 2증가
                ref += 2;                          
        }
    }

    return ref;
}

// 게임 판
vector<vector<char>> board;
// Cached
int cached[19683];

// 게임이 끝났는지 확인
// turn = 누구 소유의 돌인지
bool IsFinished(const vector<vector<char>>& board, char turn)
{
    // 좌우로 성공했는지 확인
    for (int i = 0; i < 3; i++)
        if (board[i][0] == turn && board[i][1] == turn && board[i][2] == turn)
            return true;

    // 상하로 성공했는지 확인
    for (int i = 0; i < 3; i++)
        if (board[0][i] == turn && board[1][i] == turn && board[2][i] == turn)
            return true;

    // 대각선으로 성공했는지 확인
    if (board[0][0] == turn && board[1][1] == turn && board[2][2] == turn)
        return true;
    if (board[0][2] == turn && board[1][1] == turn && board[2][0] == turn)
        return true;

    return false;
}

enum
{
    DEFAULT = 2,
    WIN = 1,
    DRAW = 0,
    LOSE = -1
};

int CanWin(vector<vector<char>>& board, char turn)
{
    // 예외 사항
    // 상대방이 이겼는지 확인
    // 'o' + 'x' - turn
    // turn : 나 자신
    // 내가 'o'일 떄 'o' + 'x' - turn = 'o' + 'x' - 'o' = 'x' = 상대방
    // 내가 'x'일 때 'o' + 'x' - turn = 'o' + 'x' - 'x' = 'o' = 상대방
    if (IsFinished(board, 'o' + 'x' - turn)) 
        return LOSE;

    // 캐시 확인
    int key = HashKey(board);
    int& ref = cached[key];
    if (ref != DEFAULT)
        return ref;

    // 구하기
    // [.][x][.]
    // [.][o][.]
    // [.][.][.]

    int minValue = DEFAULT;
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            // 이미 착수가 되어있는 곳은 패스
            if (board[y][x] != '.')
                continue;

            // 착수
            board[y][x] = turn;

            // 확인
            // 착수를 해보고 상대방이 착수를 하고 반복 시뮬레이션을 돌림
            // 내가 'o'일 때 'x'로 전달됨
            // 내가 'x'일 때 'o'로 전달됨
            minValue = min(minValue, CanWin(board, 'o' + 'x' - turn)); // 상대방이 패배하는게 제일 좋은 케이스

            // 취소
            board[y][x] = '.';
        }
    }

    if (minValue == DRAW || minValue == DEFAULT)
        return ref = DRAW;

    // 상대방이 이겼으면 나는 지고, 상대방이 졌으면 나는 이김
    // DRAW(-1) = -1 * Win(1)
    return ref = -minValue;
}

int main()
{
    board = vector<vector<char>>
    {
        {'o','x','x'},
        {'.','o','.'},
        {'.','.','o'},
    };

    // memset -> 1byte 단위로 입력한 값으로 저장시킴 -> 정수형으로 보내면 4 or 8byte로 강제로 늘려서 보냄
    // memset(cached, (char) N, sizeof(cached)); 
    // - N이 -1, 0일때 4byte형태인듯 1byte형태이든 값이 같음
    // --  0 : 1byte(0000 0000) -> 4byte(0000 0000  ...  0000 0000)
    // -- -1 : 1byte(1111 1111) -> 4byte(1111 1111  ...  1111 1111)
    // -- -2 : 1byte(1111 1110) -> 4byte(1111 1110  ...  1111 1110) -> 다른 값이 됨.
    // - N이 그 외 숫자이면 4byte인 정수형이 1byte 단위로 나누어져서 저장됨 -> 값이 어긋남

    fill(cached, cached + 19683, DEFAULT);

    // board에 'o'을 처음으로 착수함
    int win = CanWin(board, 'x');

    switch (win)
    {
    case WIN:
        cout << "Win" << endl;
        break;

    case DRAW:
        cout << "Draw" << endl;
        break;
        
    case LOSE:
        cout << "Lose" << endl;
        break;
    }
}

