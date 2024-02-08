#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

void CreateGraph_1(); // 정점과 간선의 정보를 하나의 vector에서 관리
void CreateGraph_2(); // 정점과 간선의 정보를 분리하여 관리
void CreateGraph_3(); // 정점과 간선의 정보를 분리하여 관리, 간선의 정보가 많을 경우
void CreateGraph_4(); // 정점과 간선의 정보를 분라하여 관리, 간선의 가중치가 있을 경우

int main()
{
	CreateGraph_1();
	CreateGraph_2();
	CreateGraph_3();
	CreateGraph_4();

	return 0;
}

void CreateGraph_1()
{
	// 정점과 간선의 정보가 한번에 있음.
	struct Vertex
	{
		vector<Vertex*> _edges;
		int _data;
	};

	vector<Vertex> v;
	v.resize(6);

	v[0]._edges.push_back(&v[1]);
	v[0]._edges.push_back(&v[3]);
	v[1]._edges.push_back(&v[0]);
	v[1]._edges.push_back(&v[2]);
	v[1]._edges.push_back(&v[3]);
	v[3]._edges.push_back(&v[4]);
	v[5]._edges.push_back(&v[4]);


	// Q) 0번 -> 3번 정점이 연결되어 있나?
	bool connected = false;
	for (Vertex* edge : v[0]._edges)
	{
		if (edge == &v[3])
		{
			connected = true;
			break;
		}
	}

	cout << connected << endl;
}

void CreateGraph_2()
{
	// 정점과 간선의 정보를 따로 관리함
	struct Vertex
	{
		int _data;
	};

	vector<Vertex> v;
	v.resize(6);

	// 6개의 정점이 가지고 있는 간선의 정보
	
	// adjacent[n] -> n번째 정점과 연결된 정점의 목록들
	vector<vector<int>> adjacent(6);

	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0,2,3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	// Q) 0번 -> 3번 정점이 연결되어 있나?

	// for문
	bool connected = false;
	for (int vertex : adjacent[0])
	{
		if (vertex == 3)
		{
			connected = true;
			break;
		}
	}
	cout << connected << endl;

	// STL
	// vector<int>타입을 참조하는 변수 adj
	vector<int>& adj = adjacent[0];

	// std::find -> 값이 없으면 end()값을 반환함.
	bool connected2 = (find(adj.begin(), adj.end(), 3) != adj.end());
	cout << connected2 << endl;
}

void CreateGraph_3()
{
	// 정점과 간선의 정보를 따로 관리함
	struct Vertex
	{
		int _data;
	};

	vector<Vertex> v;
	v.resize(6);

	// 6개의 정점이 가지고 있는 간선의 정보가 매우 많을 때
	// 행렬(2차원 배열)을 사용하여 처리한다 -> 메모리 소모는 크지만 빠르게 접근 가능

	// 6 * 6 행렬에 false로 초기화
	vector<vector<bool>> adjacent(6, vector<bool>(6, false));
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	//[X][O][X][O][X][X]	-> 0번 정점에서 갈 수 있는 정점
	//[O][X][O][O][X][X]	-> 1번 정점에서 갈 수 있는 정점
	//[X][X][X][X][X][X]	-> 2번 정점에서 갈 수 있는 정점
	//[X][X][X][X][O][X]	-> 3번 정점에서 갈 수 있는 정점
	//[X][X][X][X][X][X]	-> 4번 정점에서 갈 수 있는 정점
	//[X][X][X][X][O][X]	-> 5번 정점에서 갈 수 있는 정점

	// Q) 0번 -> 3번 정점이 연결되어 있나?

	bool connected3 = false;
	if (adjacent[0][3] == true)
		connected3 = true;

	cout << connected3 << endl;
}

void CreateGraph_4()
{
	// 정점과 간선의 정보를 따로 관리하고 간선에 가중치를 부여함.
	struct Vertex
	{
		int _data;
	};

	vector<Vertex> v;
	v.resize(6);

	// 6개의 정점이 가지고 있는 간선의 정보가 매우 많을 때
	// 행렬(2차원 배열)을 사용하여 처리한다 -> 메모리 소모는 크지만 빠르게 접근 가능

	vector<vector<int>> adjacent =
	{
		vector<int> {-1, 15, -1, 35, -1, -1},
		vector<int> {15, -1, +5, 10, -1, -1},
		vector<int> {-1, -1, -1, -1, -1, -1},
		vector<int> {-1, -1, -1, -1, +5, -1},
		vector<int> {-1, -1, -1, -1, -1, -1},
		vector<int> {-1, -1, -1, -1, +5, -1}
	};

	// Q) 0번 -> 3번 정점이 연결되어 있나?

	bool conneted4 = false;
	if (adjacent[0][3] != -1)
		conneted4 = true;

	cout << conneted4 << endl;
}
