
#include "Red_BlackTree.h"
#include <iostream>
#include <Windows.h>

using namespace std;

// Console 색상 정보
enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE
};

// Console창에서 커서 위치를 설정하는 함수
void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

// Console창에서 커서 색상을 설정하는 함수
void SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<SHORT>(color));
}

// Console창에서 커서가 깜빡거리는걸 On/Off시킴
void ShowConsoleCursor(bool flag)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = flag;
	::SetConsoleCursorInfo(output, &cursorInfo);
}

Red_BlackTree::Red_BlackTree()
{
	_nil = new Node(); // Black Node

	// 아무런 값을 가지고 있지 않은 상태
	// _root와 Leaf(NIL)이 같은 상태
	_root = _nil;
}

Red_BlackTree::~Red_BlackTree()
{
	delete _nil; // 메모리 해제
}

void Red_BlackTree::Print()
{
	::system("cls"); // Console 창을 깔끔하게 지우는 명령어
	ShowConsoleCursor(false); // Console 창에서 커서를 안보이도록 함
	Print(_root, 10, 0);
}

// 트리 구조로 출력되도록 함
// x : 가로, y : 세로
void Red_BlackTree::Print(Node* node, int x, int y)
{
	if (node == _nil) return;	

	// 입력된 위치에 커서를 설정함
	SetCursorPosition(x, y);

	// Console창에서 텍스트 색상을 설정함
	if (node->color == Color::Black)
		SetCursorColor(ConsoleColor::BLUE);
	else
		SetCursorColor(ConsoleColor::RED);

	// 값 출력
	cout << node->key;

	// 자식 노드를 출력
	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);

	// 다시 Console의 텍스트 색상을 디폴트값으로 변경
	// 큰 의미는 없음, Console 완료 메시지가 흰색으로 띄게 만들기 위함
	SetCursorColor(ConsoleColor::WHITE);
}

Node* Red_BlackTree::Search(Node* node, int key)
{
	// node가 NIL이 아니고 찾는 key값을 찾을 때까지 반복
	while (node != _nil && key != node->key)
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

Node* Red_BlackTree::Next(Node* node)
{
	// 자신이 가장 큰값이면 자신을 반환
	if (Max(_root) == node)
		return node;

	// 현재 노드가 오른쪽 자식을 가지고 있다면(오른쪽 자식이 NIL이 아니면)
	// 현재 노드에서 한번 오른쪽 자식으로 이동후 가장 왼쪽 노드를 반환하면 됨
	if (node->right != _nil)
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
	if (parent != _nil && node == parent->left)
	{
		// 다음으로 큰 값을 가진 부모 노드를 반환
		return parent;
	}

	// 자신이 오른쪽 자식일때
	while (parent != _nil && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

Node* Red_BlackTree::Max(Node* node)
{
	// 가장 오른쪽 자식을 반환하면 됨
	while (node->right != _nil)
		node = node->right;

	return node;
}

// 먼저 BST의 삭제 실행 이후 
// Red-Black Tree에 맞게 수정함
void Red_BlackTree::Delete(Node* node)
{
	// 삭제할려는 노드가 _nil이면 반환
	if (node == _nil)
		return;
	
	// 삭제할 노드가 왼쪽 자식이 없으면 오른쪽 자식과 교환 후 삭제
	if (node->left == _nil)
	{
		Color color = node->color;
		Node* right = node->right;
		Replace(node, right);

		// 삭제한 노드가 검정이면 수정이 필요함 -> 빨강은 검정색 카운트에 영향을 주지 않음
		// - Right노드를 검정(or Double-Black)으로 수정해야함
		if (color == Color::Black)
			DeleteFixup(right);
	}
	// 삭제할 노드가 오른쪽 자식이 없으면 왼쪽 자식과 교환 후 삭제
	else if (node->right == _nil)
	{
		Color color = node->color;
		Node* left = node->left;
		Replace(node, left);

		// 삭제한 노드가 검정이면 수정이 필요함 -> 빨강은 검정색 카운트에 영향을 주지 않음
		// - left노드를 검정(or Double-Black)으로 수정해야함
		if (color == Color::Black)
			DeleteFixup(left);
	}
	// 삭제할 노드가 양쪽 자식이 모두 있으면
	// 다음 크기의 노드이 값을 복사한후 다음 크기의 노드를 삭제함
	else
	{
		Node* next = Next(node);
		node->key = next->key;
		// DeleteFixup을 하지 않아도 재귀함수를 통해 DeleteFixup을 실행 됨.
		Delete(next);
	}

	
}

void Red_BlackTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);
	Delete(deleteNode);
}


// Red-BlackTree의 어떤 노드로부터 그에 속한 NIL까지의 검정 노드 수는 일정하다는 규칙을 지키기 위해
// 삭제 대상이 무슨 색상에 따라, 노드 위치에 따라 방법이 다름
// 
// 공통 특징 : 검정 노드를 삭제하면 NIL까지의 검정 노드의 수가 변하기때문에
// 검정 노드를 삭제한 자리에 임시의 Double-Black(Black이 두개) 색상을 가지는 NIL를 대입하여 계산한다
// (실질적으로 Double-Black이 아닌 생각하기 쉽게 하기 위함)
// Double-Black상태의 NIL은 다른 노드로 Black하나를 옮기면서 Red-BlackTree를 정상화시켜야함
// - Red 노드는 Black으로 Black 노드는 Double-Black상태로 만들면서 조건을 찾음
// - Double-Black 상태의 NIL이 Black 하나를 다른 노드로 옮기면 Black(정상)이됨.
// 
// Case 1 : 삭제할 노드가 Red 노드 일때
// - 최하위 노드이면 그냥 삭제하면 됨.
// - 자식이 있는 노드이면 다음 크기의 노드를 값을 복사해서 가져오고 Red로 유지시킴
// - 다음 크기의 노드를 삭제함
// 
// Case 2 : Root가 삭제되거나 Double-Black 상태일때
// - Root만 삭제하면 됨. -> Root는 모든 경로에 영향을 주기 때문에 제거되도 검정 노드의 수가 일정함
// 
// Case 3 : 삭제 노드가 Black(Double-Black), 형제 노드가 Red일 때
// - 부모노드(Black)과 형제 노드(Red)을 색상 교환을 한다 -> 부모노드(Red), 형제노드 (Black)
// - Double-Black인 상태 노드가 왼쪽 자식이면 부모노드에서 LeftRotate를 한다
// - Double-Black인 상태 노드가 오른쪽 자신이면 부모노드에서 RightRotate를 한다
//					[G(?)]								[G(?)]
//		  [P(B)]							[S(B)]		
//	"[D(B)]"	[S(R)]		->			[P(R)]		[F(B)]	
//			 [N(B)][F(B)]			"[D(B)]"[N(B)]	
// - Rotate를 하면 형제의 자식(1)이였던 노드가 형제로 바뀐다.
// - Case 4로 넘어감
// 
// Case 4 : 삭제노드가 Black(Double-Black)이고 형제 노드가 Black이고
//			형제 노드의 양쪽 자식이 모두 Black일때
// - Double-Black의 Black 하나를 Parent에게 이전함
// -- Parent가 Red이면 Black이됨.
// -- Parent가 Black이면 Double-Black이 됨.
// - 형제 노드는 Red로 변경함(형제 트리가 검정이 더많아지므로 Red로 변경함)
// - Parent가 Double-Black이면 삭제 연산을 되돌아가서 상황에 맞게 다시 계산함
// 
// Case 5 : 삭제 노드가 Black(Double-Black), 형제 노드가 Black이고
//			형제 노드의 자식 중 삭제노드와 가까운 노드(Near)가 Red이고 먼 노드(Far)가 Black일때
// - Near노드(Red)와 형제노드(Black) 색상 교환 -> N(Black), S(Red)
// - 형제노드 기준 Far노드 방향으로 Rotate
//					[G(?)]								[G(?)]
//		  [P(R)]							   [P(R)]		
//	"[D(B)]"	[S(B)]		->		   "[D(B)]"		[N(B)]	
//			 [N(R)][F(B)]								[S(R)]	
//															[F(B)]
// - 삭제 노드 기준으로 Far노드가 Red가 됨
// - Case 6 실행
// 
// Case 6 : 삭제노드가 Black(Double-Black), 형제 노드가 Black이고
//			형제 노드의 자식 중 삭제노드와 먼 노드(Far)가 Red이면
// - P(Red)와 S(Black)의 색상 교환 -> P(Black), S(Red)
// - Far노드를 Black으로 변경
// - Parent 기준으로 삭제노드(Double-Black)방향으로 Rotate함
// - Double-Black을 제거함
// 				[G(?)]										[G(?)]
// 		  [P(R)]									[S(R)]
// "[D(B)]"		[S(B)]				->			[P(B)]	[F(B)]
// 					[F(R)]					"[D(B)]"		[1(B)]
// 						[1(B)]
void Red_BlackTree::DeleteFixup(Node* node)
{
	Node* fixupNode = node;

	// Case 1, Case 2를 제외한 상황
	// - Double-Black을 수정하기 위함
	while (fixupNode != _root && fixupNode->color == Color::Black)
	{
		// fixupNode가 왼쪽 자식인지 확인
		//		[P(?)]
		//	[F(B)]	[S(?)]
		//		  [N(?)]
		if (fixupNode == fixupNode->parent->left)
		{
			Node* sibling = fixupNode->parent->right;
			// Case 3 : 형제노드가 Red인 경우
			//		[P(B)]
			//	[F(B)]	[S(R)]
			//		  [N(B)]
			if (sibling->color == Color::Red)
			{
				sibling->color = Color::Black;
				fixupNode->parent->color = Color::Red;
				// fixupNode가 왼쪽 자식이기 때문에 LeftRotate
				//			[S(B)]
				//		[P(R)]
				//	[F(DB)]	[N(B)] -> 이제 N이 S가 됨
				LeftRotate(fixupNode->parent);
				sibling = fixupNode->parent->right; // Near노드가 Sibling이 됨
			}

			// Case 4 : 형제 노드의 양쪽 자식이 모두 검정인 경우
			//		[P(R)]
			//	[F(B)]	[S(B)]
			//		  [N(B)] [F(B)] 
			if (sibling->left->color == Color::Black && sibling->right->color == Color::Black)
			{
				// 형제노드를 Red로 변경
				sibling->color == Color::Red;
				// while를 통해 fixupNode->parent가 Red이면 Black으로 변경되고
				// Black이면 while을 통해 수정을 함
				fixupNode = fixupNode->parent;
			}
			// fixupNode 형제노드의 양쪽 자식이 둘다 Black이 아님
			else
			{
				// Case 5 : fixupNode 형제 노드의 자식 중 멀리 있는 노드가 Black인 경우
				//			가까이 있는 노드가 Red
				if (sibling->right->color == Color::Black)
				{
					//		[P(R)]
					//	[F(B)]	[S(B)]
					//		  [N(R)] [F(B)]
					sibling->left->color = Color::Black;
					sibling->color = Color::Red;
					RightRotate(sibling);

					//		[P(R)]
					//	[F(B)]	[N(B)]
					//				 [S(R)]
					//					[F(B)]
					sibling = fixupNode->parent->right; // Near을 sibling으로 변경함
				}

				// Case 6 : fixupNode 형제 노드의 자식중 멀리 있는 노드가 Red인경우
				//			가까이 있는 노드가 Black
				//		[P(R)]
				//	[F(B)]	[S(B)]
				//		 [N(B)] [F(R)]
				sibling->color = fixupNode->parent->color;
				fixupNode->parent->color = Color::Black;
				sibling->right->color = Color::Black;
				// fixupNode가 왼쪽 자식이므로 왼쪽 회전
				//				[S(R)]
				//		[P(B)]			[F(B)]
				//	[F(B)][N(B)]	
				LeftRotate(fixupNode->parent);
				// fixupNode를 root로 설정하여 while을 통과하도록 함
				fixupNode = _root;
			}
		}
		// fixupNode가 오른쪽 자식인지
		else
		{
			Node* sibling = fixupNode->parent->left;
			// Case 3 : 형제노드가 Red인 경우
			if (sibling->color == Color::Red)
			{
				sibling->color = Color::Black;
				fixupNode->parent->color = Color::Red;
				// fixupNode가 오른쪽 자식이기 때문에 LeftRotate
				RightRotate(fixupNode->parent);
				sibling = fixupNode->parent->left; // Near노드가 Sibling이 됨
			}

			// Case 4 : 형제 노드의 양쪽 자식이 모두 검정인 경우
			if (sibling->left->color == Color::Black && sibling->right->color == Color::Black)
			{
				sibling->color == Color::Red;
				// while를 통해 fixupNode->parent가 Red이면 Black으로 변경되고
				// Black이면 while을 통해 수정을 함
				fixupNode = fixupNode->parent;
			}
			// fixupNode 형제노드의 양쪽 자식이 둘다 Black이 아님
			else
			{
				// Case 5 : fixupNode 형제 노드의 자식 중 멀리 있는 노드가 Black인 경우
				//			가까이 있는 노드가 Red
				if (sibling->left->color == Color::Black)
				{
					sibling->right->color = Color::Black;
					sibling->color = Color::Red;
					LeftRotate(sibling);

					sibling = fixupNode->parent->left; // Near을 sibling으로 변경함
				}

				// Case 6 : fixupNode 형제 노드의 자식중 멀리 있는 노드가 Red인경우
				//			가까이 있는 노드가 Black
				sibling->color = fixupNode->parent->color;
				fixupNode->parent->color = Color::Black;
				sibling->left->color = Color::Black;
				// fixupNode가 오른쪽 자식이므로 왼쪽 회전
				RightRotate(fixupNode->parent);
				// fixupNode를 root로 설정하여 while을 통과하도록 함
				fixupNode = _root;
			}
		}
	}

	// 궁극적으로 해야할 일
	// - Double-Black인 노드를 Black으로 풀어주거나
	// - Red인 노드를 Black으로 변경하는 일
	fixupNode->color = Color::Black;
}

// u 서브트리를 v서브트리로 교체
// u 위치에 v를 대체함
void Red_BlackTree::Replace(Node* u, Node* v)
{
	// v가 u로 대체하기 위해
	// v와 u->parent 연결

	// u->parent의 자식을 v로 대체
	// - v에 nullptr(자식이 없을때)를 넣으면 u->parent엔 nullptr와 연결됨
	//  u가 root이면
	if (u->parent == _nil)
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
	// v가 NIL일수도 있음 -> 노드 제거를 위해 NIL로 대체함
	v->parent = u->parent;

	// 필요없기 때문에 메모리 해제
	delete u;
}

Node* Red_BlackTree::Min(Node* node)
{
	// 가장 왼쪽 자식을 반환하면 됨
	while (node->left != _nil)
		node = node->left;

	return node;
}

// 이진 트리 규칙에 맞게 맞는 자리에 배치 하도록함
// 이후 Red-Black Tree의 규칙에 맞는지 확인하고 재구성함
void Red_BlackTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	// BinarySearch에선 _root가 없으면 _root로 설정함
	// Red-BlackTree에선 _nil을 _root로 설정되어 있기때문에 다른식으로 _root를 값을 넣음

	Node* node = _root;
	Node* parent = _nil;

	// 노드가 NIL이 아니면 부모 노드와 크기 비교를함
	while(node != _nil)
	{
		parent = node;
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	newNode->parent = parent;

	// parent가 NIL이면 새로운 값을 _root로 설정함
	if (parent == _nil)
		_root = newNode;
	// 새로운 노드가 Parent 노드보다 작으면 왼쪽 자식에 추가함
	else if (key < parent->key)
		parent->left = newNode;
	// 새로운 노드가 Parent 노드보다 크면 오른쪽 자식에 추가함
	else
		parent->right = newNode;

	// Red-Black Tree의 규칙을 지키는지 검사
	newNode->left = _nil;
	newNode->right = _nil;
	newNode->color = Color::Red;
	InsertFixup(newNode);
}

void Red_BlackTree::InsertFixup(Node* node)
{
	// 1) Parent = Red, Uncle(부모노드의 형제노드) = Red
	// - Uncle이 Nil(Black)이 아님
	// 2) Parent = Red, Uncle = Black (Triangle)
	// - G, P, N이 삼각형 모양 일때
	// - 회전을 통해 List 타입으로 변경
	// 3) Parent = Red, Uncle = Black (List)
	// - G, P, N이 일직선 모양 일때
	// - 색상 변경 + 회전

	//							[GG(?)]
	//			[G(B)]
	//	[P(R)]			[U(?)]
	//		[N(R)]
	// 부모의 색상이 빨강이면 수정이 필요함
	// Red-BlackTree의 규칙중 Red의 자식은 무조건 Black이야함
	while (node->parent->color == Color::Red)
	{
		// node의 부모노드가 왼쪽 자식인지
		if (node->parent == node->parent->parent->left)
		{
			Node* uncle = node->parent->parent->right;
			// 1) P, U 모두 Red임
			// - P, U을 Black으로 변경하고, G를 Red로 변경함 
			//							[GG(?)]
			//			[G(B)]
			//	[P(R)]			[U(R)]
			//		[N(R)]
			if (uncle->color == Color::Red)
			{
				// P와 U를 Black으로 변경, G을 Red로 변경
				node->parent->color = Color::Black; // P
				uncle->color = Color::Black; // U
				node->parent->parent->color = Color::Red; // G

				// node를 G로 변경하여 GG가 Red인지 다시 확인함
				// - node의 부모가 Black일때까지 반복됨
				node = node->parent->parent;
			}

			// 2) P = Red, U = Black
			//							[GG(?)]
			//			[G(B)]
			//	[P(R)]			[U(B)]
			//		[N(R)]
			else
			{
				// Triangle 타입
				// Parent : Red, Uncle : Black
				// 왼쪽으로 회전시켜 List 타입으로 변경해야함
				//			[G(B)]						  [G(B)]
				//	[P(R)]		[U[B]]		->		[N(R)]		[U[B]]
				//		[N(R)]					[P(R)]
				if (node == node->parent->right) 
				{	
					// Left Rotate을 통해 List 타입으로 변경
					node = node->parent;
					LeftRotate(node);
				}

				// List 타입
				//			  [G(B)]								[P(B)]
				//		[P(R)]		[U(B)]		->			[N(R)]			[G(R)]
				//	[N(R)]														[U(B)]
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				RightRotate(node->parent->parent);
			}
		}
		// node의 부모노드가 오른쪽 자식인지
		else
		{
			Node* uncle = node->parent->parent->left;
			// 1) P, U 모두 Red임
			// - P, U을 Black으로 변경하고, G를 Red로 변경함 
			//							[GG(?)]
			//			[G(B)]
			//	[U(R)]			[P(R)]
			//				[N(R)]
			if (uncle->color == Color::Red)
			{
				node->parent->color = Color::Black; // P
				uncle->color = Color::Black; // U
				node->parent->parent->color = Color::Red; // G

				// node를 G로 변경하여 GG가 Red인지 다시 확인함
				// - node의 부모가 Black일때까지 반복됨
				node = node->parent->parent;
			}

			// 2) P = Red, U = Black
			//							[GG(?)]
			//			[G(B)]
			//	[U(B)]			[P(R)]
			//				[N(R)]
			else
			{
				// Triangle 타입
				// 왼쪽으로 회전시켜 List 타입으로 변경해야함
				//			[G(B)]						  [G(B)]
				//	[U(B)]		[P(R)]		->		[U(B)]		[N(R)]
				//			[N(R)]									[P(R)]
				if (node == node->parent->left)
				{
					// Left Rotate을 통해 List 타입으로 변경
					node = node->parent;
					RightRotate(node);
				}

				// List 타입
				//			  [G(B)]								[P(B)]
				//		[U(B)]		[P(R)]		->			[G(R)]			[N(R)]
				//						[N(R)]			[U(B)]
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				LeftRotate(node->parent->parent);
			}
		}
	}

	// Root의 색상은 검정 고정
	_root->color = Color::Black;
}

// 반시계 방향
//				[G]							[G]
//		[X]							[Y]		
//	[1]		[Y]		->		  [X]		[3]	
//		   [2][3]			 [1][2]		
// 변경해야하는 것 : 2, X, Y
// 주의 : 2가 NIL일수도 있음
void Red_BlackTree::LeftRotate(Node* X)
{
	Node* Y = X->right;

	// X <-> 2 서로 연결
	X->right = Y->left; // X의 오른쪽 자식을 2로 수정
	if(Y->left != _nil) // 2가 NIL이 아니면
		Y->left->parent = X; // 2의 부모을 X로 수정

	// G의 자식을 X에서 Y로 대체함
	Y->parent = X->parent;
	// X가 root이였다면 root로 설정
	if (X->parent == _nil)
		_root = Y;
	// X가 왼쪽 자식이였다면 G의 왼쪽 자식을 Y로 대체
	else if (X == X->parent->left)
		X->parent->left = Y;
	// X가 오른쪽 자식이였다면 G의 오른쪽 자식을 Y로 대체
	else
		X->parent->right = Y;

	// X <-> Y연결
	Y->left = X;
	X->parent = Y;
}

// 시계 방향
//				[G]							[G]
//		[Y]						[X]
//	[X]		[3]		  ->	[1]		[Y]
// [1][2]						   [2][3]
// 변경해야하는 것 : 2, X, Y
// 주의 : 2가 NIL일수도 있음
void Red_BlackTree::RightRotate(Node* Y)
{
	Node* X = Y->left;

	// X <-> 2을 서로 연결
	Y->left = X->right;
	if (X->right != _nil) // 2가 NIL이 아니면
		X->right->parent = Y; // 2의 부모를 Y로 변경

	// G의 자식을 Y에서 X로 변경
	X->parent = Y->parent;
	// Y가 root였다면 root로 설정
	if (Y->parent == _nil)
		_root = X;
	// Y가 왼쪽 자식이였다면 G의 왼쪽 자식을 X로 대체
	else if (Y == Y->parent->left)
		Y->parent->left = X;
	// Y가 오른쪽 자식이였다면 G의 오른쪽 자식을 X로 대체
	else
		Y->parent->right = X;

	// X <-> Y연결
	X->right = Y;
	Y->parent = X;
}
