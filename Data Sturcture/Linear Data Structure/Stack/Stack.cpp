#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;

// Stack (LIFO Last-In-First-Out

// Container의 기본값을 vector<T>로 해둠.
template<typename T, typename Container = vector<T>>
class Stack
{
public:
	void push(const T& value)
	{
		_container.push_back(value);
	}

	void pop()
	{
		_container.pop_back();
	}

	T& top()
	{
		return _container.back();
	}

	// vector의 empty() 활용.
	bool empty() { return  _container.empty(); }
	// vector의 size() 활용
	int size() { return _container.size(); }

private:
	// list와 vector와 원하는 것을 사용해도 된다.
	// list<int> _container;
	// vector<int> _container;

	// 사용자가 원하는 container를 쓸 수 있도록 함.
	Container _container;

};


int main()
{
	// stack<int> s;
	// Stack<int> s;
	
	// Container를 list로 지정해서 stack를 생성
	Stack<int, list<int>> s;

	// 삽입
	s.push(1);
	s.push(2);
	s.push(3);

	// stack이 비어있는지 확인
	while (s.empty() == false)
	{
		// 최상위 원소 확인
		int data = s.top();

		// 최상위 원소 삭제
		s.pop();

		cout << data << endl;
	}

	// stack 사이즈 확인
	int size = s.size();

	return 0;
}