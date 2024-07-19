#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;


void CreateGraph();
void Dijkstra(int here);

// 다익스트라 알고리즘
// 간선의 가중치(Cost)가 있을 떄.
// 출발점을 지정하면 연결된 모든 정점을 순회하면서 각 정점의 최대 경로를 구함.

struct Vertex 
{
    // int data;
};

vector<Vertex> vertieces;
vector<vector<int>> adjacent;

int main()
{
    CreateGraph();

    Dijkstra(0);

    return 0;
}

void CreateGraph()
{
    vertieces.resize(6);
    adjacent = vector<vector<int>>(6, vector<int>(6, -1));

    adjacent[0][1] = 15;
    adjacent[0][3] = 35;

    adjacent[1][0] = 15;
    adjacent[1][2] = 5;
    adjacent[1][3] = 10;

    adjacent[3][4] = 5;

    adjacent[5][4] = 5;
}

void Dijkstra(int here)
{
    struct VertexCost
    {
        int vertex;
        int cost;
    };

    // 발견 목록 (방문 X)
    list<VertexCost> discovered;
    // 각 정점별로 지금까지 발견한 최소 거리
    vector<int> best(vertieces.size(), INT32_MAX);
    // Parent
    vector<int> parent(vertieces.size(), -1);

    // 0번 정점 발견 및 방문
    discovered.push_back(VertexCost{ here, 0 });
    best[here] = 0;
    parent[here] = here;

    
    while (discovered.empty() == false)
    {
        list<VertexCost>::iterator bestIt;
        int BestCost = INT32_MAX;

        // 발견된 정점 중에서 가장 적은 가중치를 가진 경로를 구함.
        for (auto it = discovered.begin(); it != discovered.end(); it++)
        {
            // discovered(발견된 정점) 중 cost가 가장 낮은 정점 찾기
            if (it->cost < BestCost)
            {
                bestIt = it;
                BestCost = it->cost;
            }
        }

        // Cost가 가장 낮은 정점을 방문 준비
        int cost = bestIt->cost;
        here = bestIt->vertex;
        discovered.erase(bestIt);

        // 기존에 Best로 찾아둔 경로가 더 짧으면 스킵
        if (best[here] < cost)
            continue;

        // Cost가 가장 낮은 정점 방문, 인접 정점 탐색
        for (int there = 0; there < vertieces.size(); there++)
        {
            // 연결되지 않으면 스킵
            if (adjacent[here][there] == -1)
                continue;

            // 해당 정점까지 온 최저 cost + 다음 정점으로 넘어가는 cost
            int nextCost = best[here] + adjacent[here][there];

            // 더 좋은 경로가 과거에 찾았으면 스킵
            if (nextCost >= best[there])
                continue;

            // Best 갱신
            best[there] = nextCost;
            parent[there] = here;

            // (3, 35)이 있는 상태에서 (3, 25)가 들어온 후 95번 줄에서 (3,35)가 걸러짐.
            discovered.push_back(VertexCost{ there, nextCost });
        }
    }
}
