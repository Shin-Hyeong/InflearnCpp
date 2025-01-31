#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

// 상호 배타적 집합 (Disjoint Set) : 유니온-파인드 (Union-Find, 합치기-찾기)라고도 불림

// Lineage + Battleground
// - 혈맹전 + 서바이벌
// - 1인팀 1000명 ( 팀 ID : 0 ~ 999)
// - 서로 합의하에 동맹 (1번팀 + 2번팀 = 1번팀)
void LineageBattleground()
{
    struct User
    {
        int teamID;
        // TODO : 유저 정보
    };

    // TODO : UserManager
    vector<User> users;
    for (int i = 0; i < 1000; i++)
    {
        // 1000명의 userID 설정
        users.push_back(User{ i });
    }

    // 팀 동맹 : 찾기 연산
    // users[1] <-> user[5]
    // 5번 유저도 1번 팀으로 속하게됨
    users[5].teamID = users[1].teamID; // 1

    // 다수인 팀이 동맹 : 합치기 연산
    // [1][1][1][1]...[2][2][2]
    // teamID = 1인 팀과 teamID = 2인 팀이 통합
    for (User& user : users)
    {
        // teamID가 1인 사람을 teamID을 2로 설정
        if (user.teamID == 1)
            user.teamID = 2;
    }

    // 찾기 연산 : O(1)
    // 합치기 연산 : O(N) -> 자료가 커질 수록 효율이 안좋기 때문에 개선이 필요함
}

// 트리 구조를 이용한 상호 배타적 집합의 표현
// [0] [1] [2] [3] [4] [5]

// 대장 : [1]           [3]
// 부하 : [2]         [4],[5]
//                        [0]

// 옆으로 넓은것이 아닌 아래로 깊을수록 비효율적임
// 트리가 한쪽으로 기우는 문제가 발생가능
class NaiveDisjointSet
{
public:
    NaiveDisjointSet(int n) : _parent(n)
    {
        _parent.resize(n);
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

    // u와 v를 합침 (일단 u가 v밑으로 들어감)
    // 조건없이 합치기 때문에 높이의 불균형이 일어날 수 있음
    void Merge(int u, int v)
    {
        u = Find(u);
        v = Find(v);

        // 서로 대장이 같음
        if (u == v)
            return;

        // u가 v 밑으로 들어감
        _parent[u] = v;

        // 대장      [3]
        // 부하   [4][5][1]
        //          [0][2]
    }

private:
    vector<int> _parent;
};

// 트리가 한쪽으로 기우는 문제를 해결해야함
// 트리를 합칠 때, 항상 [높이가 낮은 트리]를 [높이가 높은 트리] 밑으로 들어가면 높이 더 늘어나지 않을 수 있음
// (Union-By-Rank) 랭크에 의한 합치기 최적화
// 시간 복잡도 : O(Ackermann(N)) -> O(1)
class DisjointSet
{
public:
    DisjointSet(int n) : _parent(n), _rank(n, 1) // 모든 rank는 1로 초기화
    {
        _parent.resize(n);
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

int main()
{
    DisjointSet djs(6);

    // 2번이 1번 밑으로 들어감
    djs.Merge(2, 1);
    // 3번이 2번 밑으로 들어감
    djs.Merge(3, 2);
    cout << djs.Find(3) << endl;
}
