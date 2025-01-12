#include "BinarySearchTree.h"
#include <iostream>
#include <Windows.h>

using namespace std;

// Console창에서 커서 위치를 설정하는 함수
void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

// 트리 구조로 출력되도록 함
// x : 가로, y : 세로
void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == nullptr) return;

	// 입력된 위치에 커서를 설정함
	SetCursorPosition(x, y);

	// 값 출력
	cout << node->key;
	
	// 자식 노드를 출력
	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);
}

// 순차적으로 출력됨
void BinarySearchTree::Print_Inorder(Node* node)
{
	// 전위 순회 (preorder traverse)
	// - Parent를 출력 이후 왼쪽 자식부터 출력함
	// - Root 기준으로 왼쪽 자식, 오른쪽 자식 내려가면서 출력됨
	// 중위 순회 (inorder)
	// - 가장 밑단의 왼쪽 자식부터 출력함
	// - 가장 낮은 값을 가진 노드 부터 출력됨
	// 후위 순회 (postorder)
	// - 가장 밑단의 왼쪽 자식부터 출력함
	// - 가장 하위 노드 들부터 부터 출력됨.

	if (node == nullptr) return;

	//   [중]
	// [좌][우]

	// 전위 순회 순서 (PreOrder Traverse) : [중]이 "앞"에 옴
	//			   [1]
	//		[2]				 [9]
	//	 [3]	[6]		 [10]	   [13]
	// [4] [5] [7] [8] [11] [12] [14] [15]
	// 노드 값을 출력 이후
	// [중]cout << node->key << endl;
	// 왼쪽 자식 노드만 계속 출력
	// [좌]Print_Inorder(node->left);
	// 그후 다시 돌아오면서 오른쪽 자식 노드 출력
	// [우]Print_Inorder(node->right);

	// 중위 순회 순서(InOrder) : [중]이 "중간"에 옴
	//			   [8]
	//		[4]				 [9]
	//	 [2]	[6]		 [11]	   [14]
	// [1] [3] [5] [7] [10] [12] [13] [15]
	// 왼쪽 자식 노드 끝까지 들어감
	// [좌]Print_Inorder(node->left);
	// 왼쪽 자식 노드 끝까지 들어가면 노드의 값을 출력
	// [중]cout << node->key << endl;
	// 왼쪽 자식 노드 끝에서 root로 다시 올라오면서 오른쪽 자식
	// [우]Print_Inorder(node->right);

	// 후위 순회 순서(Post Order) : [중]이 "마지막"에 옴
	//			   [8]
	//		[7]				 [15]
	//	 [3]	[6]		 [11]	 [14]
	// [1] [2] [4] [5] [9] [10] [12] [13]
	// 가장 왼쪽 노드 끝까지 들어감 -> 자식 노드가 없으면 값을 출력 후 Parent로 돌아감
	// [좌]Print_Inorder(node->left);
	// Parent에서 오른쪽 자식으로 들어가서 자식 노드가 없으면 값을 출력하고 Parent롤 돌아감
	// [우]Print_Inorder(node->right);
	// Parent 출력
	// [중]cout << node->key << endl;

	// 전위
	cout << node->key << endl;
	Print_Inorder(node->left);
	Print_Inorder(node->right);
}

// 새로운 노드(값) 추가
void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	// 트리가 처음 생성되었을 때 Root에 값을 넣음
	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}

	// 어느 위치에 데이터를 추가해야하는 검색함
	Node* node = _root;
	Node* parent = nullptr;
	while (node)
	{
		// 노드가 존재하기 때문에 해당 노드의 자식으로 추가 가능함
		// Parent 기준으로 왼쪽 or 오른쪽으로 가야하는지 정함
		parent = node;
		// 입력값이 Parent보다 작으면 왼쪽
		if (key < parent->key)
			node = parent->left;
		// 입력값이 Parent보다 크면 오른쪽
		else
			node = parent->right;

		// 이동한 node가 nullptr이면 노드가 존재하기 않기 때문에 더 이상 검색하지가 않고
		// 새로운 노드를 추가함
	}
	// 새로 추가될 노드의 Parent를 지정함
	newNode->parent = parent;

	// 새로운 노드가 Parent 노드보다 작으면 왼쪽 자식에 추가함
	if (key < parent->key)
		parent->left = newNode;
	// 새로운 노드가 Parent 노드보다 크면 오른쪽 자식에 추가함
	else
		parent->right = newNode;
}

void BinarySearchTree::Delete(int key)
{
	// Root에서 시작해서 삭제해야하는 Node를 찾기
	Node* deleteNode = Search(_root, key);
	// Node를 삭제
	Delete(deleteNode);
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr) return;
	
	// 삭제할 노드가 하나의 자식이나 자식이 없을때
	// 왼쪽 자식이 없을 때 오른쪽 자식을 부모노드로 올려서 대체함
	if (node->left == nullptr)
		Replace(node, node->right);

	// 오른쪽 자식이 없을 때 왼쪽 자식을 부모 노드로 올려서 대체함
	else if (node->right == nullptr)
		Replace(node, node->left);

	// 삭제할 노드가 두개의 자식을 가지고 있을 때
	// 삭제하는 노드의 다음 크기의 노드로 대체함
	else
	{
		// 삭제할려는 노드의 다음 크기를 가진 노드를 찾음
		Node* next = Next(node);
		// 다음 크기의 노드의 값으로 변경함
		node->key = next->key;
		// 다음 크기의 노드를 삭제함
		Delete(next);
	}
}

// u 서브트리를 v서브트리로 교체
// u 위치에 v를 대체함
void BinarySearchTree::Replace(Node* u, Node* v)
{
	// v가 u로 대체하기 위해
	// v와 u->parent 연결

	// u->parent의 자식을 v로 대체
	// - v에 nullptr(자식이 없을때)를 넣으면 u->parent엔 nullptr와 연결됨
	//  u가 root이면
	if (u->parent == nullptr)
		_root = v;
	// u가 왼쪽 자식이면
	else if (u == u->parent->left)
		// u를 v로 대체하기 위해서 u부모랑 v연결
		u->parent->left = v;
	// u가 오른쪽 자식이면
	else
		// u를 v로 대체하기 위해서 u부모랑 v연결
		u->parent->right = v;

	// v의 parent를 u의 parent로 변경
	// - v에 nullptr를 넣었을때(노드 제거) 연결되지 않도록 함
	if (v)
		v->parent = u->parent;

	// 필요없기 때문에 메모리 해제
	delete u;
}

// 해당 노드기준으로 최소값
Node* BinarySearchTree::Min(Node* node)
{
	// 가장 왼쪽 자식을 반환하면 됨
	while (node->left)
		node = node->left;

	return node;
}

// 해당 노드기준으로 최대값
Node* BinarySearchTree::Max(Node* node)
{
	// 가장 오른쪽 자식을 반환하면 됨
	while (node->right)
		node = node->right;

	return node;
}

// 현재 노드의 값에서 다음으로 큰 값 출력
Node* BinarySearchTree::Next(Node* node)
{
	// 자신이 가장 큰값이면 자신을 반환
	if (Max(_root) == node)
		return node;

	// 현재 노드가 오른쪽 자식을 가지고 있다면
	// 현재 노드에서 한번 오른쪽 자식으로 이동후 가장 왼쪽 노드를 반환하면 됨
	if (node->right)
		return Min(node->right);
	
	// 현재 노드가 오른쪽 자식을 가지고 있지 않다면
	// 자식이 왼 / 오른쪽 자식인지 확인한 뒤
	// 왼쪽 자식이면 부모를 반환
	// 오른쪽 자식이면 부모의 부모 노드를 반환

	Node* parent = node->parent;
	// 자신이 오른쪽 노드라면 부모의 부모 노드를 찾음
	// - 자신이 오른쪽 노드이면 부모 < 자식인 상태임
	// - 자신이 왼쪽 자식인 상태를 찾아야함
	
	// 자신이 왼쪽 자식일때
	if (parent && node == parent->left)
	{
		// 다음으로 큰 값을 가진 부모 노드를 반환
		return parent;
	}

	// 자신이 오른쪽 자식일때
	while (parent && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

// 재귀 함수 사용 -> 가독성이 좋으나 성능이 비교적 떨어짐
Node* BinarySearchTree::Search(Node* node, int key)
{
	// 루트가 없거나 검색된 결과이면 반환
	if (node == nullptr || key == node->key)
		return node;

	// 찾을려는 key가 node의 key값보다 작으면 왼쪽 자식에서 다시 Search함
	if (key < node->key)
		return Search(node->left, key);
	// 찾을려는 key가 node의 key값보다 크면 오른쪽 자식에서 다시 Search함
	else
		return Search(node->right, key);
}

// 루프를 사용 -> 가독성은 떨어지나 성능이 비교적 좋음
Node* BinarySearchTree::SearchLoop(Node* node, int key)
{
	// node가 값이 존재하고 찾는 key값을 찾을 때까지 반복
	while (node && key != node->key)
	{
		// 찾을려는 key가 node의 key값보다 작으면 왼쪽 자식으로 들어감
		if (key < node->key)
			node = node->left;
		// 찾을려는 key가 node의 key값보다 작으면 오른쪽 자식으로 들어감
		else
			node = node->right;
	}
	return node;
}
