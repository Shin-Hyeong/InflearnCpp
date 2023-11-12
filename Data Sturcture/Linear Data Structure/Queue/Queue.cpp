#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

// Queue (FIFO First-In-First-Out 선입선출)

template<typename T>
class ListQueue
{
public:
	void push(const T& value)
	{
		_container.push_back(value);
	}

	void pop()
	{
		// vector의 중간 원소 삭제는 효율이 좋지 않음.
		// _container.erase(_container.begin());
		_container.pop_front();
	}

	T& front()
	{
		return _container.front();
	}

	bool empty() { return _container.empty(); }
	int size() { return _container.size(); }

private:
	// vector<T> _container; -> 중간값 삭제가 좋지 못함.
	// queue 라이브러리에는 deque로 구현되어 있음.
	list<T> _container;
};

// 처음 상태
// [front / back][][][][][][][]
// 값을 하나 추가
// [front][back][][][][][][]
// 필요한 만큼 값 추가
// [front][][][][][back][][]
// 맨 앞 원소 제거
// [][front][][][][back][][]
// back이 할당된 메모리를 초과시 -> 순환구조
// [back][][][][front][][][]

// 할당된 메모리는 유지하면서 원소를 앞으로 당기지 않음.
template<typename T>
class ArrayQueue
{
public:
	ArrayQueue()
	{	
		// 처음 생성될때 충분한 메모리를 할당받도록 함.
		_container.resize(100);
	}

	void push(const T& value)
	{
		// TODO : 다 찼는지 체크
		if (_size == _container.size())
		{
			// 증설 작업
			// max(a, b) : a, b 중 큰 값을 반환
			int newSize = max(1, _size * 2);

			// 새로운 vector 생성
			vector<T> newData;
			newData.resize(newSize);

			// 데이터 복사
			for (int i = 0; i < _size; i++)
			{	
				// front부터 back까지의 원소를 그대로 옮기는 것이 아닌 0번 인덱스부터 넣어줌.
				// [back][][][][front][1][2][3]
				int index = (_front + i) % _container.size();
				// [front][1][2][3][back][][][][][][][][][][][][][][][][][][][
				newData[i] = _container[index];
			}

			// 기존 vector와 newData vector와 교환
			_container.swap(newData);
			// 맨 앞으로 이동했으므로 0
			_front = 0;
			// data의 갯수만큼 뒤로 이동.
			_back = _size;
		}

		_container[_back] = value;
		// 다음 원소가 저장되어야 할 위치 변경, _container.size() : 버퍼의 크기를 의미
		_back = (_back + 1) % _container.size();
		// 실질적 원소의 갯수
		_size++;
	}

	void pop()
	{
		if (!_container.empty())
		{
			_front = (_front + 1) % _container.size();
			_size--;
		}
	}

	T& front()
	{
		if (!_container.empty())
		{
			return _container[_front];
		}
	}

	bool empty() { return _size == 0; }
	int size() { return _container.size(); }

private:
	vector<T> _container;

	// data의 시작 지점
	int _front = 0;
	// data의 끝 지점
	int _back = 0;
	int _size = 0;
};

int main()
{
	// queue<int> q;
	// ListQueue<int> q;
	ArrayQueue<int> q;

	for (int i = 0; i < 100; i++)
	{
		q.push(i);
	}

	// queue에 원소가 있으면 실행
	while (q.empty() == false)
	{
		int value = q.front();
		// queue에서 맨 앞에 있는 원소를 제거
		q.pop();
		cout << value << endl;
	}

	int size = q.size();

	return 0;
}
