#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

// 최소 신장 트리 (Minimum Spanning Tree) : Graph의 응용
// Spanning Tree : 간선의 수를 최소화해서, 모든 정점을 연결하는 것
// - 간선을 통한 싸이클(순환)이 생기면 안됨
// - N개의 정점을 N-1개의 간선으로 연결

// Minimum Spanning Tree : Spanning Tree중 최소 비용을 사용하는 경로
// Graph에서 가중치에 따라 연결시키는 것과 유사(단, 싸이클이 생기면 안되고, 모든 정점이 연결되어야함)
// 길을 찾는 것이 아닌 길을 뚫어주는 기능
// 
// - 통신 네트워크 구축
// -- 구축비용, 전송 시간등을 최소로해서 구함

// Kruskal Algorithm (크루스칼) : 탐욕적(greedy)인 방법을 이용
// 현재 가장 최적인 답을 선택하여 결과를 도출함
// - 간선 중 가중치가 가장 적은 간선을 확정시킴
// - 그 다음으로 가중치가 가장 적은 간선 중 순환이 생기지 않는 간선을 확정시킴 -> 반복
// 순환 하지 않는 간선을 선택하는 알고리즘
// 
// - 간선으로 연결되는 정점은 하나의 그룹으로 취급함
// - 다음 간선의 연결이 같은 그룹을 연결할려고 하면 스킵함
// - 간선의 연결이 서로 다른 그룹을 연결할려고할 때 가능
// - 서로 다른 그룹이 연결하면 하나의 그룹으로 합침
// -- 서로 다른 그룹을 합칠때 효율적으로 합치기 위해 상호 배타적 집합(Disjoint set, Union-Find)을 사용한다

class DisjointSet
{
public:
    DisjointSet(int n) : _parent(n), _rank(n, 1) // 모든 rank는 1로 초기화
    {
        // 정해진 수만큼 자신을 _parent로 가지도록 함
        for (int i = 0; i < n; i++)
        {
            _parent[i] = i;
        }
    }

    // 팀의 대장 찾기
    int Find(int u)
    {
        // 자신 위에 대장이 있으면 
        while (u != _parent[u])
        {
            // 대장을 불러옴
            u = _parent[u];
        }
        return u;
    }

    // u와 v를 합침 (u가 v밑으로 들어감)
    // _rank(높이)를 확인한 후 _rank가 낮은 트리가 _rank 높은 트리 밑으로 들어감
    void Merge(int u, int v)
    {
        u = Find(u);
        v = Find(v);

        // 서로 대장이 같음
        if (u == v)
            return;

        // u의 _rank가 높으면 u와 v의 값을 교환함
        if (_rank[u] > _rank[v])
            swap(u, v);

        _parent[u] = v;

        // u와 v가 같은 높이를 가지고 있으면 v의 _rank를 +1함
        if (_rank[u] == _rank[v])
            _rank[v]++;

    }

private:
    vector<int> _parent;
    vector<int> _rank;
};

struct Vertex
{
    // int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

void CreateGraph()
{
    vertices.resize(6);
    adjacent = vector<vector<int>>(6, vector<int>(6, -1));

    adjacent[0][1] = adjacent[1][0] = 15;
    adjacent[0][3] = adjacent[3][0] = 35;
    adjacent[1][2] = adjacent[2][1] = 5;
    adjacent[1][3] = adjacent[3][1] = 10;
    adjacent[3][4] = adjacent[4][3] = 5;
    adjacent[3][5] = adjacent[5][3] = 10;
    adjacent[4][5] = adjacent[5][4] = 5;

}

struct CostEdge
{
    int cost;   // 비용
    int u;      // 출발
    int v;      // 도착

    bool operator<(CostEdge& other)
    {
        return cost < other.cost;
    }
};

int Kruskal(vector<CostEdge>& selected) // selected : 연결된 결과물 반환, return : Graph의 모든 간선 Cost 값
{
    int ret = 0;

    // 불 필요한 자료 제거
    selected.clear();

    vector<CostEdge> edges;

    for (int u = 0; u < adjacent.size(); u++)
    {
        for (int v = 0; v < adjacent[u].size(); v++)
        {
            // adjacent[0][1] = 저장
            // adjacent[1][0] = 패스
            // 같은 간선을 두번 검사하는것을 방지
            if (u > v)
                continue;

            // 연결되어 있으면 edges에 저장
            int cost = adjacent[u][v];
            if (cost == -1)
                continue;

            edges.push_back(CostEdge{ cost, u, v });
        }
    }

    // 작은 수로 정렬
    sort(edges.begin(), edges.end());

    // 정점의 갯수 만큼 노드(배열) 생성
    DisjointSet sets(vertices.size());

    // 작은 순서대로 간선을 확정지어 연결하기 시작
    for (CostEdge& edge : edges)
    {
        // 서로 같은 그룹에 있는 정점은 연결할려고하면 스킵 (안 그러면 사이클(순환) 발생)
        if (sets.Find(edge.u) == sets.Find(edge.v))
            continue;

        // 두 그룹을 합친다
        sets.Merge(edge.u, edge.v);

        // 연결된 결과를 저장함
        selected.push_back(edge);

        // 연결된 Cost를 누적시킴 -> 총 cost = Graph의 최소 신장 트리의 합산
        ret += edge.cost;
    }

    return ret;
}

int main()
{
    CreateGraph();

    vector<CostEdge> selected;
    int cost = Kruskal(selected);

    return 0;
}
