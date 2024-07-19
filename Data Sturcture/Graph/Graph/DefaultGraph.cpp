#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

void CreateGraph_1();
void CreateGraph_2();
void CreateGraph_3();
void CreateGraph_4();

int main()
{
    CreateGraph_1();
    CreateGraph_2();
    CreateGraph_3();
    CreateGraph_4();

    return 0;
}

// 정점끼리 서로 포인터로 물고 있음
// 실제 데이터(정점)과 연결(간선)의 여부가 한곳에 있음
void CreateGraph_1()
{
    struct Vertex
    {
        vector<Vertex*> edges;
        // int data;
    };

    vector<Vertex> v;
    v.resize(6);

    v[0].edges.push_back(&v[1]);
    v[0].edges.push_back(&v[3]);

    v[1].edges.push_back(&v[0]);
    v[1].edges.push_back(&v[2]);
    v[1].edges.push_back(&v[3]);

    v[3].edges.push_back(&v[4]);
    v[5].edges.push_back(&v[4]);

    // Q.1) 0 -> 3 정점 연결되어 있나?
    bool connected = false;
    for (Vertex* edge : v[0].edges)
    {
        if (edge == &v[3])
        {
            connected = true;
            break;
        }
    }

    cout << connected << endl;
}

// 정점과 간선의 여부를 따로 관리함
// 단점 - 정점이 많고 각 정점끼리 간선이 많으면 관리가 어려움.
void CreateGraph_2()
{
    struct Vertex
    {
        // int data;
    };

    vector<Vertex> v;
    v.resize(6);

    // 연결된 목록을 따로 관리
    vector<vector<int>> adjacent(6);

    adjacent[0] = { 1, 3 };
    adjacent[1] = { 0, 2, 3 };
    adjacent[3] = { 4 };
    adjacent[5] = { 4 };

    // Q.1) 0 -> 3 정점 연결되어 있나?
    // - roof
    bool connected1 = false;
    for (int vertex : adjacent[0])
    {
        if (vertex == 3)
        {
            connected1 = true;
            break;
        }
    }
    cout << connected1 << endl; 

    // - STL
    vector<int>& adj = adjacent[0];
    // find -> end()값 반환하면 찾는 값이 없음.
    bool connected2 = find(adj.begin(), adj.end(), 3) != adj.end();

    cout << connected2 << endl;
}

// 행렬(2차원 배열)를 사용하여 간선이 많은것을 처리함.
// 메모리를 소모를 많이 함. 대신 빠른 접근이 가능
void CreateGraph_3()
{
    struct Vertex
    {
        // int data;
    };

    vector<Vertex> v;
    v.resize(6);

    // 간선을 행렬로 관리
    // 6개의 vector를 만들고 각 vector에 6개의 bool이 다 false로 초기화 시킴.
    // [X][X][X][X][X][X]
    // [X][X][X][X][X][X]
    // [X][X][X][X][X][X]
    // [X][X][X][X][X][X]
    // [X][X][X][X][X][X]
    // [X][X][X][X][X][X]
    vector<vector<bool>> adjacent(6, vector<bool>(6, false)); 
    // [X][O][X][O][X][X]
    // [O][X][O][O][X][X]
    // [X][X][X][X][X][X]
    // [X][X][X][X][O][X]
    // [X][X][X][X][X][X]
    // [X][X][X][X][O][X]
    
    // adjectent[from][to]
    adjacent[0][1] = true;
    adjacent[0][3] = true;
    adjacent[1][0] = true;
    adjacent[1][2] = true;
    adjacent[1][3] = true;
    adjacent[3][4] = true;
    adjacent[5][4] = true;

    // Q.1) 0 -> 3 정점 연결되어 있나?
    bool conneted3 = adjacent[0][3];

    cout << conneted3 << endl;
}

// 간선의 가중치를 추가함.
void CreateGraph_4()
{
    struct Vertex
    {
        // int data;
    };

    vector<Vertex> v;
    v.resize(6);

    vector<vector<int>> adjacent =
    {
        // -1 = 연결 안됨.
        vector<int> { -1, 15, -1, 35, -1, -1},
        vector<int> { 15, -1, +5, 10, -1, -1},
        vector<int> { -1, -1, -1, -1, -1, -1},
        vector<int> { -1, -1, -1, -1, +5, -1},
        vector<int> { -1, -1, -1, -1, -1, -1},
        vector<int> { -1, -1, -1, -1, +5, -1},
    };

    bool connected4 = adjacent[0][3] > -1;
    cout << connected4 << endl;
}
