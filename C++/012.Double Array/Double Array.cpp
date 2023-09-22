#include <iostream>
using namespace std;

int main ()
{
    // [1][1][4][2][2] << 1층
    // [4][2][3][4][1] << 0층

    // 1차원 배열로 만들기
    int first[5] = { 4, 2, 3, 4, 1 };
    int second[5] = { 1, 1, 4, 2, 2 };

    // 2차원 배열로 만들기
    // 배열 안에 배열이 있는 느낌.
    // apartment[0 ~ 1][0 ~ 4] 인덱스를 가짐.
    // 메모리상에서 { 4, 2, 3, 4, 1 }를 순차적으로 저장하고 바로 { 1, 1, 4, 2, 2 }를 순차적으로 저장한다.
    // 메모리상에선 1차 배열이나 2차배열이나 차이가 없다.
    int apartment2D[2][5] = {{ 4, 2, 3, 4, 1 }, { 1, 1, 4, 2, 2 }};

    cout << "2차원 배열" << endl;
    for (int floor = 0; floor < 2; floor++)
    {
        for (int room = 0; room < 5; room++)
        {
            // 4 2 3 4 1
            // 1 1 4 2 2
            cout << apartment2D[floor][room] << " ";
        }
        cout << endl;
    }

    cout << "1차원 배열" << endl;
    // apartment1D
    int apartment1D[10] = { 4, 2, 3, 4, 1, 1, 1, 4, 2, 2 };
    for (int floor = 0; floor < 2; floor++)
    {
        for (int room = 0; room < 5; room++)
        {
            int index = (floor * 5) + room;
            // 4 2 3 4 1
            // 1 1 4 2 2
            cout << apartment1D[index] << " ";
        }
        cout << endl;
    }

    // 2차 배열은 언제 사용할까? 대표적으로 2D 로그라이크 맵
    int map[5][5] =
    {   
        // 1 = 플레이어가 지나갈수 없는 지형
        // 0 = 플레이어가 지나갈수 있는 지형
        {1, 0, 1, 1, 1},
        {1, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1},
        {1, 1, 0, 1, 1},
    };

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            int info = map[y][x];
            cout << info;
        }
        cout << endl;
    }

    return 0;
}