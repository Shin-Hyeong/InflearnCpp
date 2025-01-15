#pragma once

enum class Color
{
	Red = 0,
	Black = 1,
};

struct Node
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;

	int key = {};
	Color color = Color::Black;
};


// Red-Black Tree
// 1) 모든 노드는 Red or Black
// 2) Root는 Black
// 3) Leaf(NIL)dms Black
// 4) Red 노드의 자식은 Black
// 5) 각 노드로부터 ~ 리프(NIL)까지 가는 경로들은 모두 같은 수의 Black노드 개수를 가짐
class Red_BlackTree
{
public:
	Red_BlackTree();
	~Red_BlackTree();

	/**
		 트리 출력
	*/
	// 트리 구조로 출력되도록 함
	void Print();
	void Print(Node* node, int x, int y);

	/**
		트리 탐색
	*/
	Node* Search(Node* node, int key);
	Node* Next(Node* node);
	Node* Max(Node* node);
	Node* Min(Node* node);
	Node* Min() { return Min(_root); }
	Node* Max() { return Max(_root); }

	/**
		트리 삽입 / 삭제
	*/
	// 이진 트리 구조에 맞게 새로운 Node를 배치함
	// 이후 Red-Black Tree의 특성에 맞게 재구성함
	void Insert(int key);
	void InsertFixup(Node* node);

	// 이진 탐색 트리와 삭제 과정은 비슷하게 이루어진다.
	// 다만, 삭제 이후 Red-BlackTree의 특성인 
	// 각 노드로부터 그에 속한 NIL까지의 경로의 Black노드의 수가 일정하다는 조건을 맞추어야함
	void Delete(Node* node);
	void Delete(int key);
	void DeleteFixup(Node* node);

	// 노드 교환
	void Replace(Node* u, Node* v);

	/**
		Rotate
	*/
	// 반시계방향 회전
	void LeftRotate(Node* node);
	// 시계방향 회전
	void RightRotate(Node* node);

private:
	Node* _root = nullptr;
	Node* _nil = nullptr;
};
