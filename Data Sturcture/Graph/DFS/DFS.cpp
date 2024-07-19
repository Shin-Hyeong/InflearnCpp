#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

void CreateGraph();
void DFS(int here);
void DFSAll();

struct Vertex
{
    // int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent(6);

vector<bool>visited(6, false);

int main()
{
    CreateGraph();

    DFSAll();

    return 0;
}

void CreateGraph()
{
    vertices.resize(6);
    adjacent = vector<vector<int>>(6);

    // 인접 리스트
    // adjacent[0] = { 1, 3 };
    // adjacent[1] = { 0, 2, 3 };
    // adjacent[3] = { 4 };
    // adjacent[5] = { 4 };

    // 인접 행렬
    adjacent = vector<vector<int>>
    {
        {0, 1, 0, 1, 0, 0},
        {1, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0},
    };

    return;
}

void DFS(int here)
{
    visited[here] = true;
    cout << "Visited : " << here << endl;

    // 인접 리스트
    // for (int i = 0; i < adjacent[here].size(); i++)
    // {
    //     int there = adjacent[here][i];
    //     if (visited[there] == false)
    //         DFS(there);
    // }

    // 인접 행렬
    for (int there = 0; there < 6; there++)
    {
        // 간선이 없다.
        if (adjacent[here][there] == 0)
            continue;

        // 방문한적이 없다
        if (visited[there] == false)
            DFS(there);
    }
}

void DFSAll()
{
    for (int i = 0; i < 6; i++)
        if (visited[i] == false)
            DFS(i);
}
