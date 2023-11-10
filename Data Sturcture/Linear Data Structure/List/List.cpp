#include <iostream>
#include <vector>
#include <list>

using namespace std;

template<typename T>
class Node
{
public:
	Node() : _prev(nullptr), _next(nullptr), _data(T())
	{

	}

	Node(const T& value) : _prev(nullptr), _next(nullptr), _data(value)
	{

	}

public:
	T		_data;
	Node*	_prev;
	Node*	_next;

};

template<typename T>
class Iterator
{
public:
	Iterator() : _node(nullptr)
	{

	}

	Iterator(Node<T>* node) : _node(node)
	{

	}

	// ++it
	Iterator& operator++()
	{
		_node = _node->_next;
		return *this;
	}

	// it++
	Iterator operator++(int)
	{
		Iterator<T> temp = *this;
		_node = _node->_next;
		return temp;
	}

	// --it
	Iterator& operator--()
	{
		_node = _node->_prev;
		return *this;
	}

	// it--
	Iterator operator--(int)
	{
		Iterator<T> temp = *this;
		_node = _node->_prev;
		return temp;
	}

	// *it
	T& operator*() 
	{
		return _node->_data;
	}

	// ==
	bool operator==(const Iterator& other)
	{
		return _node = other._node;
	}

	// !=
	bool operator!=(const Iterator& other)
	{
		return _node != other._node;
	}

public:
	Node<T>* _node;
};

template<typename T>
class List
{
public:
	List() : _size(0)
	{
		// [_head] <-> [_tail]
		// _head와 _tail에 더미 노드를 만들어 nullptr를 확인하는 상황을 피할 수 있음.
		_head = new Node<T>();
		_tail = new Node<T>();

		_head->_next = _tail;
		_tail->_prev = _head;
	}

	~List()
	{
		while (_size > 0)
			pop_back();

		delete _head;
		delete _tail;
	}

	void push_back(const T& value)
	{
		AddNode(_tail, value);
	}

	void pop_back()
	{
		RemoveNode(_tail->_prev);
	}

private:
	// [head] <-> [1] <-> [2] <-> [before] <-> [tail]
	// [head] <-> [1] <-> [2] <-> [newNode] <-> [before] <-> [tail]
	Node<T>* AddNode(Node<T>* before, const T& value)
	{
		// 새로운 노드 생성, _data = value
		Node<T>* newNode = new Node<T>(value);
		// 2번 노드의 주소를 가지게 함.
		Node<T>* prevNode = before->_prev;

		// [2] <-> [newNode]
		prevNode->_next = newNode;
		newNode->_prev = prevNode;

		// [newNode] <-> [before]
		newNode->_next = before;
		before->_prev = newNode;

		_size++;

		return newNode;
	}

	// [head] <-> [prevNode] <-> [node] <-> [nextNode] <-> [tail]
	// [head] <-> [prevNode] <-> [nextNode] <-> [tail]
	Node<T>* RemoveNode(Node<T>* node)
	{	
		// node의 이전노드를 가져옴.
		Node<T>* prevNode = node->_prev;
		// node의 다음 노드를 가져옴.
		Node<T>* nextNode = node->_next;

		// [prevNode] <-> [nextNode]
		prevNode->_next = nextNode;
		nextNode->_prev = prevNode;

		delete node;

		_size--;

		return nextNode;
	}

	int size() { return _size; }

public:
	using iterator = Iterator<T>;

	// 첫번째 node
	iterator begin() { return iterator(_head->_next); }
	// 마지막 node 다음 -> 노드가 끝남을 확인용
	iterator end() { return iterator(_tail); }

	// it "이전"에 추가
	iterator insert(iterator it, const T& value)
	{	
		// it_node 앞에 value를 가진 node를 추가함.
		Node<T>* node = AddNode(it._node, value);
		return iterator(node);
	}

	iterator erase(iterator it)
	{	
		// it가 가지고 있는 노드를 삭제
		Node<T>* node = RemoveNode(it._node);
		return iterator(node);
	}

private:
	Node<T>*	_head;
	Node<T>*	_tail;
	int			_size;
};

int main()
{
	// list<int> li;
	List<int> li;

	// vector
	// - push_back O(1)
	// - push_front O(N) -> 기능 제공 안함
	// - v[3] -> 임의 접근 가능

	// list
	// - push_back
	// - psuh_front -> 기능 제공함.
	// - li[3] -> 임의 접근할 수 없음. ++를 통해 하나씩 넘어가야함.
	// list가 중간 삽입/삭제가 빠르다 -> 삽입/삭제하는 작업 자체는 빠르지만 삽입/삭제할 노드를 찾아가는 과정은 느림.

	List<int>::iterator eraseIt;
	// list<int>::iterator eraseIt;

	for (int i = 0; i < 10; i++)
	{
		if (i == 5)
		{	
			// 중간 삽입할 위치, 값
			// iterator를 반환
			eraseIt = li.insert(li.end(), i);
		}
		else 
		{
			// void 반환
			li.push_back(i);
		}
	}
	
	// 맨 뒤 노드 제거 -> 9 제거
	li.pop_back();

	// 중간 값 삭제 -> 5 제거
	li.erase(eraseIt);
	
	// 	for (list<int>::iterator it = li.begin(); it != li.end(); it++)	// list는 임의 접근이 안되기 떄문에 for (i = 0; i < N; i++)를 할 수 없다.

	for (List<int>::iterator it = li.begin(); it != li.end(); it++)
	{
		cout << (*it) << endl;
	}

	return 0;
}