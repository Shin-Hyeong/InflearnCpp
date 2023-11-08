#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Vector
{
public:
	Vector()
	{

	}

	~Vector()
	{	
		// 데이터 삭제
		if (_data)
			delete[] _data;

		_data = nullptr;
	}

	// value를 vector 맨 뒤에 입력
	// _data가 포인터 변수이기 떄문에 참조값(포인트)으로 받음.

	// 할당 받은 메모리보다 더 많은 값을 입력하게 되면 더 넓은 메모리를 할당 받고 기존의 값을 이동시킴.
	void push_back(const T& value)
	{
		// 할당받은 메모리를 다 사용하면
		if (_size == _capacity)
		{
			// 증설 작업
			int newCapacity = static_cast<int>(_capacity * 1.5);
			// _capacity * 1.5를 해도 증가가 안했다면 ex) 0 * 1.5 = 0 / 1 * 1.5 = 1
			if (newCapacity == _capacity)
				newCapacity++;

			reserve(newCapacity);
		}

		// 데이터 저장
		_data[_size] = value;

		// 데이터 개수 증가
		_size++;
	}

	// capacity 만큼 메모리 할당.
	void reserve(int capacity)
	{	
		// 기존의 capacity가 입력 받은 capacity보다 크면 무시
		if (_capacity >= capacity)
			return;

		// 새로운 capacity 저장.
		_capacity = capacity;

		// 새로운 capacity 만큼 새로 할당.
		T* newData = new T[_capacity];

		// 데이터 복사
		for (int i = 0; i < _size; i++)
			newData[i] = _data[i];

		// 기존 배열 메모리 해제
		if (_data)
			delete[] _data;

		// 시작 주소 교체
		_data = newData;

	}

	// 입력한 pos값을 통해서 해당 index 위치 값 반환
	T& operator[](const int pos) { return _data[pos]; }
	
	int size() { return _size; }
	int capacity() { return _capacity; }

	void clear()
	{	
		// 배열이 가지고 있는 값 삭제
		if (_data)
		{	
			// 메모리 해제 -> 단순한 자료형이 아닌 class형태이면 소멸자 호출
			delete[] _data;
			// 다시 _capacity 만큼 메모리 할당 -> clear를 해도 size는 0이 되지만 capacity는 유지되는 것을 표현
			_data = new T[_capacity];
		}
		_size = 0;
	}

private:
	// 동적 할당의 시작 위치
	T*		_data = nullptr;
	int		_size = 0;
	int		_capacity = 0;
};


int main()
{
	// vector<int> v;
	Vector<int> v;

	// vector.size() : 실질적으로 사용하고 있는 메모리 크기
	// vector.capacity() : 메모리에 할당 받아서 사용할 수 있는 메모리 크기, 한번 늘어난 capacity는 다시 줄어들지 않음.
	
	// 어느정도 사용할 것인지 알고 있으면 처음에는 capacity가 자주 변경되므로 처음부터 어느정도 크게 할당하고 하는 것이 성능면에서 좋음.
	// vector의 capacity를 변경함 -> size는 변경 없음.
	v.reserve(100);

	// vector의 size를 변경함 -> capacity도 변경함.
	// size : 100 -> size : 10 -> vector의 _data도 날라감
	// v.resize(10);

	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		cout << i << " " << v.size() << " " << v.capacity() << endl;
	}

	v.clear();
	cout << "clear() 이후 vector.size() :  " << v.size() << ", vector.capacity() :  " << v.capacity() << endl;


	return 0;
}