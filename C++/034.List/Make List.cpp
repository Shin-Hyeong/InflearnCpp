#include <iostream>
#include <list>
using namespace std;

// list 구현
template<typename T>
class Node
{
public:
    // _data(T()) -> T()가 int로 들어가면 0으로 밀림, float로 들어가면 0.0f
    Node() : _next(nullptr), _prev(nullptr), _data(T())
    {

    }

    // 직접적으로 값을 넣어줄 때
    // T : 값을 복사해서 입력
    // T& : 값을 참조하여 원본 그대로 입력
    Node(const T& value) : _next(nullptr), _prev(nullptr), _data(value)
    {

    }

public:
    Node*   _next;
    Node*   _prev;
    T       _data;
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
    // T&를 해서 참조값으로 하는 것은 (*it)한 이후 값을 수정할 수 있기 때문
    T& operator*()
    {
        return _node->_data;
    }

    // it == it
    bool operator==(const Iterator& right)
    {
        return _node == right._node;
    }

    // it != it
    bool operator!=(const Iterator &right)
    {
        return _node != right._node;
    }

public:
    // TODO 어떤 Container에 속해져 있는지에 대한 정보
    Node<T>* _node;
};


// [1] <-> [2] <-> [3] <-> [4] <-> [_header] <-> [1]
template<typename T>
class List
{
public:
    // 처음 생성되었을때 앞과 뒤 노드가 없을 떄 _next와 _prev가 자신을 가르키도록 함.
    //  <-> [_header] <-> 
    List() : _size(0)
    {
        _header = new Node<T>();
        _header->_next = _header;
        _header->_prev = _header;
    }
    ~List()
    {
        // TODO 모든 노드를 해제해야함.
        while(_size > 0)
            pop_back();


        delete _header;
    }

    void push_back(const T& value)
    {   
        // _header : list의 맨 뒤 노드
        AddNode(_header, value);
    }

    // before : 어디 노드 앞에 삽입할지, value : 삽입할 값
    //  <-> [_header] <->
    // [1] <-> [2] <-> [before] <-> [4] <-> [_header] <-> [1]
    // [1] <-> [2] - [value] - [before] <-> [4] <-> [_header] <-> [1]
    // insert와 erase는 list<int>::iterator를 반환하기 때문에 반환값을 Node<T>*으로 한다.
    Node<T>* AddNode(Node<T>* before, const int& value)
    {
        // [1] <-> [2] - [value] - [before] <-> [4] <-> [_header] <-> [1]
        Node<T>* node = new Node<T>(value);

        // 기존 before의 앞 노드 주소를 가져옴 -> [2]주소
        // [1] <-> [prevNode] - [value] - [before] <-> [4] <-> [_header] <-> [1]
        Node<T>* prevNode = before->_prev;

        // prevNode가 다음 노드를 가리키는 걸 추가된 노드로 변경함.
        // [1] <-> [prevNode] -> [value] - [before] <-> [4] <-> [_header] <-> [1]
        prevNode->_next = node;

        // 추가된 Node가 이전 노드를 가르키는 노드는 prevNode로 설정.
        // [1] <-> [prevNode] <-> [value] - [before] <-> [4] <-> [_header] <-> [1]
        node->_prev = prevNode;

        // 추가된 Node의 다음 노드를 before로 설정
        // [1] <-> [prevNode] <-> [value] -> [before] <-> [4] <-> [_header] <-> [1]
        node->_next = before;

        // before의 이전 노드를 추가된 노드로 변경
        // [1] <-> [prevNode] <-> [value] <-> [before] <-> [4] <-> [_header] <-> [1]
        before->_prev = node;

        // 노드가 추가되어서 _size 증가
        _size++;

        // 새로 만든 node의 주소를 반환
        return node;
    }

    // [1] <-> [2] <-> [before] <-> [4] <-> [_header] <-> [1]
    void pop_back()
    {   
        // _header의 전 노드를 삭제
        RemoveNode(_header->_prev);
    }

    // 삭제할 노드의 위치(주소)
    // [1] <-> [2] <-> [node] <-> [4] <-> [_header] <-> [1]
    Node<T>* RemoveNode(Node<T> *node)
    {
        // [1] <-> [prevNode] <-> [node] <-> [4] <-> [_header] <-> [1]
        Node<T>* prevNode = node->_prev;

        // [1] <-> [prevNode] <-> [node] <-> [nextNode] <-> [_header] <-> [1]
        Node<T>* nextNode = node->_next;

        // [1] <-> [prevNode] <-> [nextNode] <-> [_header] <-> [1]
        prevNode->_next = nextNode;
        nextNode->_prev = prevNode;

        // list에서 연결이 해제된 node 삭제
        delete node;

        // list의 삭제로 감소
        _size--;

        // 원래 node가 있던 위치
        return nextNode;
    }

    // list의 원소 갯수 출력
    int size() { return _size; }

    // Iterator<T>를 iterator라고 부른다.
    typedef Iterator<T> iterator;
    
    iterator begin() { return iterator(_header->_next); }
    iterator end() { return iterator(_header); }

    iterator insert(iterator it, const T& value)
    {
        Node<T>* node = AddNode(it._node, value);
        return iterator(node);
    }

    iterator erase(iterator it)
    {
        Node<T>* node = RemoveNode(it._node);
        return iterator(node);
    } 

public:
    // list.end()가 가르키는 더미 노드
    Node<T>* _header;
    // 원소의 개수
    int _size;
};

int main ()
{
    list<int> li;

    list<int>::iterator eraseIt;

    // list에 0 ~ 9 까지 삽입
    for (int i = 0; i < 10; i++)
    {   
        // 입력값이 5일때
        if (i == 5)
        {
            // insert : list<int>iterator를 반환함
            // insert(li.end(), 5) 즉 맨 뒤에 5을 넣음 = push_back(5)
            // 입력값 5를 넣은 노드 주소를 기억함.
            eraseIt = li.insert(li.end(), i);
        }
        else
        {
            li.push_back(i);
        }
    }
    // 정상 작동하는지 확인
    // 9 삭제
    li.pop_back();
    
    // 값이 5인 주소를 삭제
    li.erase(eraseIt);

    // list 내용 확인
    for (list<int>::iterator it = li.begin(); it != li.end(); ++it)
    {
        cout << (*it) << " ";
    }

    // ! ----------------------------------------------------
    cout << endl << "----------------------------------------" << endl;

    List<int> Li;

    List<int>::iterator eraseIt1;

    for (int i = 0; i < 10; i++)
    {
        if (i == 5)
        {
            eraseIt1 = Li.insert(Li.end(), i);
        }
        else
        {
            Li.push_back(i);
        }
    }

    Li.pop_back();

    Li.erase(eraseIt1);

    for (List<int>::iterator it = Li.begin(); it != Li.end(); ++it)
    {
        cout << (*it) << " ";
    }

    return 0;
}