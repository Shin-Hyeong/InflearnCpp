#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

void CreateGraph();
void BFS(int here);
void BFSAll();

struct Vertex
{
    // int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent(6);

vector<bool>discovered(6, false);

int main()
{
    CreateGraph();

    BFSAll();
    return 0;
}

void CreateGraph()
{
    vertices.resize(6);
    adjacent = vector<vector<int>>(6);

    // 인접 리스트
    adjacent[0] = { 1, 3 };
    adjacent[1] = { 0, 2, 3 };
    adjacent[3] = { 4 };
    adjacent[5] = { 4 };

    // 인접 행렬
    // adjacent = vector<vector<int>>
    // {
    //     {0, 1, 0, 1, 0, 0},
    //     {1, 0, 1, 1, 0, 0},
    //     {0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 1, 0},
    //     {0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 1, 0},
    // };



    return;
}
void BFS(int here)
{
    // 누구에 의해서 발견 되었는가?
    vector<int> parent(6, -1);
    // 시작점에서 얼만큼 떨어져 있는지?
    vector<int> distance(6, -1);

    queue<int> q;
    q.push(here);
    discovered[here] = true;

    parent[here] = here;
    distance[here] = 0;

    while (q.empty() == false)
    {
        // 발견 해두었던 정점을 방문함.
        here = q.front();
        q.pop();
        cout << "Visited : " << here << endl;

        // 방문한 노드와 연결된 정점 탐색
        for (int there : adjacent[here])
        {
            if (discovered[there] == true)
                continue;

            // 다음에 갈 정점을 발견만 해두고 queue에 저장함.
            q.push(there);
            discovered[there] = true;

            // 부모가 누구인지 출발점과의 거리 저장
            parent[there] = here;
            distance[there] = distance[here] + 1;
            cout << here << "의 연결 정점 : " << there << endl;
            cout << there << "의 시작점과의 거리는 : " << distance[there] << endl;
        }
    }
}

void BFSAll()
{
    for (int i = 0; i < 6; i++)
    {
        if (discovered[i] == false)
            BFS(i);
    }
}