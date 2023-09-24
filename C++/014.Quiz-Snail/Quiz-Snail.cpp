#include <iostream>
// setfill, setw를 사용하기 위함.
#include <iomanip>
using namespace std;

void PrintBoard();
void SetBoard();
void SetBoard_2();
bool CanGo(int y, int x);

const int MAX = 100;
int board[MAX][MAX] = {};
int num;

enum DIR
{
    RIGHT = 0,
    DOWN = 1,
    LEFT = 2,
    UP = 3
};

int main()
{
    cin >> num;

    SetBoard_2();
    PrintBoard();

    return 0;
}

bool CanGo(int y, int x)
{   
    // y의 범위 측정
    if (y < 0 || y >= num)
        return false;

    // x의 범위 측정
    if (x < 0 || x >= num)
        return false;

    // 입력값이 있는지 확인.
    if (board[y][x] != 0)
        return false;

    // 해당 사항없으면 true
    return true;
}

void SetBoard_2()
{
    int dir = RIGHT;
    int count = 1;
    int y = 0, x = 0;

    // RIGHT = 0 / DOWN = 1 / LEFT = 2 / UP = 3
    int dy[] = {0 , 1, 0 , -1};
    int dx[] = {1, 0, -1, 0};

    while (true)
    {
        board[y][x] = count;

        /* 다음 좌표 이동 */

        // 방향에 맞게 더함
        // RIGHT : y + 0 / x + 1;
        // DOWN : y + 1 / x + 0;
        // LEFT : y + 0 / x - 1;
        // UP : y - 1 / x + 0;
        int nextY = y + dy[dir];
        int nextX = x + dx[dir];
        
        // switch (dir)
        // {
        // case RIGHT :
        //     nextY = y;
        //     nextX = x + 1;
        //     break;
        // case DOWN :
        //     nextY = y + 1;
        //     nextX = x;
        //     break;
        // case LEFT :
        //     nextY = y;
        //     nextX = x - 1;
        //     break;
        // case UP :
        //     nextY = y - 1;
        //     nextX = x;
        //     break;
        // }

        /* 다음 좌표가 이동이 가능한 곳인지 확인 */

        if (CanGo(nextY, nextX))
        {
            y = nextY;
            x = nextX;
            count++;
        }
        /* 이동할 수 없으면 이동 방향 변경 */
        else
        {   
            // dir + 1 : 다음 dir로 넘어감. RIGHT -> DOWN
            // (dir + 1) % 4 : dir의 값이 0 ~ 3의 값만 가지도록 함.
            dir = (dir + 1) % 4;
            // switch (dir)
            // {
            // case RIGHT :
            //     dir = DOWN;
            //     break;
            // case DOWN:
            //     dir = LEFT;
            //     break;
            // case LEFT:
            //     dir = UP;
            //     break;
            // case UP:
            //     dir = RIGHT;
            //     break;
            // }
        }

        /* 입력 마무리 */
        if (count == num * num)
        {
            board[y][x] = count;
            break;
        }
    }
}

void SetBoard()
{
    int count = 1;
    int x = 0, y = 0;
    int endNum = num * num;
    while (true && count != endNum + 1)
    {
        for (int i = 0; i < num; i++)
        {
            board[y][x] = count;
            x++;
            count++;
        }

        num--;
        x--;
        y++;
        cout << "현재 위치 : [" << x << "] [" << y << "]\n";

        for (int i = 0; i < num; i++)
        {
            board[y][x] = count;
            y++;
            count++;
        }

        x--;
        y--;
        cout << "현재 위치 : [" << x << "] [" << y << "]\n";

        for (int i = 0; i < num; i++)
        {
            board[y][x] = count;
            x--;
            count++;
        }

        num--;
        x++;
        y--;
        cout << "현재 위치 : [" << x << "] [" << y << "]\n";

        for (int i = 0; i < num; i++)
        {
            board[y][x] = count;
            y--;
            count++;
        }

        x++;
        y++;
        cout << "현재 위치 : [" << x << "] [" << y << "]\n";
    }
}

void PrintBoard()
{ 
    for (int y = 0; y < num; y++)
    {
        for (int x = 0; x < num; x++)
        {
            // setw(N) :  N자리수로 나타낸다.
            // setfill('M') : N자리 수로 나타낼때 빈칸을 M으로 채운다.
            cout << setfill('0') << setw(2) << board[y][x] << " ";
        }
        cout << endl;
    }
}