#pragma once

// 이진 탐색 트리
// - 이진 트리 구조를 가짐.
//	   [10]
//	 [5]  [20]
// [2][7][12][24]
// 부모 노드 기준으로 왼쪽 자식 노드는 부모 노드보다 작아야함
// 부모 노드 기준으로 오른쪽 자식 노드는 부모 노드보다 커야함.

struct Node
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	// 노드가 가지고 있는 값
	int key = {};
};

class BinarySearchTree
{
public:	
	/**
		 트리 출력
	*/
	// 트리 구조로 출력되도록 함
	void Print(Node* node, int x, int y);
	void Print() { Print(_root, 10, 0); }
	// 순차적으로 출력됨
	void Print_Inorder(Node* node);
	void Print_Inorder() { Print_Inorder(_root); }

	/**
		트리 기능
	*/
	// 새로운 노드(값) 추가
	void Insert(int key);

	// 노드 삭제
	void Delete(int key);
	void Delete(Node* node);

	// 노드 교환
	void Replace(Node* u, Node* v);

	// 해당 노드기준으로 최소값
	Node* Min(Node* node);
	Node* Min() { return Min(_root); }
	// 해당 노드기준으로 최대값
	Node* Max(Node* node);
	Node* Max() { return Max(_root); }
	// 현재 노드의 값에서 다음으로 큰 값 출력
	Node* Next(Node* node);

	// 재귀 함수 사용한 노드 탐색
	Node* Search(Node* node, int key);
	// 반복문을 사용한 노드 탐색
	Node* SearchLoop(Node* node, int key);

	Node* GetRoot() { return _root; }

private:
	Node* _root = nullptr;
};

