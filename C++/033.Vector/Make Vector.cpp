#include <iostream>
#include <vector>
using namespace std;

// vector 만들기
template<typename T>
class Iterator
{
public:
    // 기본 생성자
    Iterator() : _ptr(nullptr)
    {

    }
    // 일반 생성자(ptr)
    Iterator(T* ptr) : _ptr(ptr)
    {

    }

    // ++Iterator
    // ++a -> OK
    // ++(++a) -> OK
    // ++(++a)이 되는 것은 (++a)의 반환값이 자기자신을 참조를 반환해줌 -> Iterator&
    Iterator& operator++()
    {   
        _ptr++;
        // 자기 자신의 주소를 반환
        return *this;
    }

    // Iterator++
    // a++ -> OK
    // (a++)++ -> No
    // (a++)++이 안되는 것 (a++)가 복사된 값을 반환해주기 때문 -> Iterator
    Iterator operator++(int)
    {
        Iterator temp = *this;
        _ptr++;
        return temp;
    }

    // --Iterator
    Iterator &operator--()
    {
        _ptr--;
        // 자기 자신의 주소를 반환
        return *this;
    }

    // Iterator++
    Iterator operator--(int)
    {
        Iterator temp = *this;
        _ptr--;
        return temp;
    }

    // Iterator1(기준) == Iterator2(right)
    bool operator==(const Iterator& right)
    {
        return _ptr == right._ptr;
    }

    // Iterator1(기준) != Iterator2(right)
    bool operator!=(const Iterator &right)
    {   
        // return !(*this == right);
        return _ptr != right._ptr;
    }

    // Iterator형태와 + 연산
    Iterator operator+(const int count)
    {
        Iterator temp = *this;
        temp._ptr += count;
        return temp;
    }

    // Iterator형태와 - 연산
    Iterator operator-(const int count)
    {
        Iterator temp = *this;
        temp._ptr -= count;
        return temp;
    }

    // Iterator*
    // (*it) = 3 같이 값을 수정할려면 참조값으로 반환해야함. 임의 접근 연산자와 같은 원리
    T& operator*()
    {
        return *_ptr;
    }

public:
    T* _ptr;
    // TODO 자신이 어떤 Container에 속해져 있는지 확인하는 정보
};

template<typename T>
class Vector
{
public:
    Vector() : _data(nullptr), _size(0), _capacity(0)
    {
    
    }
    ~Vector()
    {
        if (_data)
            delete[] _data;
    }

    // push_back : const형 참조
    void push_back(const T& val)
    {   
        // 할당된 배열이 가득참.
        if (_size == _capacity)
        {
            // TODO 증설 작업
            int newCapacity = static_cast<int>(_capacity * 2);

            // 0 -> 0, 1 -> 1(1.5)
            if (newCapacity == _capacity)
                newCapacity++;
            
            // 지정된 Capacity 만큼 증설
            reserve(newCapacity);
        }

        // 마지막 위치에 원소값 입력
        // _size = 3
        // [0][1][2][val]
        _data[_size] = val;

        // 원소 추가로 원소 갯수 증가
        _size++;
    }

    // reserve : capacity 증설
    void reserve(int capacity)
    {
        _capacity = capacity;

        // 새로운 capacity만큼 새로 생성
        T* newData = new T[_capacity];

        // 데이터 복사
        if(_data)
        {
            for (int i = 0; i < _size; i++)
                newData[i] = _data[i];
        }

        // 기존에 있던 데이터 날림.
        if (_data)
            delete[] _data;

        // 멤버변수 _data가 새로운 배열을 가르키도록 함.
        _data = newData;
    }

    // 임의 접근 연산자(v[1])
    // &를 붙여야 원소 값을 수정할 수 있다.
    T& operator[](const int pos) { return _data[pos]; }

    int size() { return _size; }
    int capacity() { return _capacity; }

    // Iterator<T>을 iterator라고 부르기로 함.
    // vector<int>::iterator
    typedef Iterator<T> iterator;

    // 첫번쨰 원소 주소를 넘겨줌.
    iterator begin() { return iterator(&_data[0]); }
    // 마지막 원소 주소를 넘겨줌.
    iterator end() { return begin() + _size; }

private:
    // 배열의 주소를 가르키는 포인터 변수
    T* _data;
    // 배열의 원소 갯수
    int _size;
    // 배열이 할당된 메모리 크기
    int _capacity;
};

int main ()
{
    vector<int> v1;

    // vector 초기화
    for (int i = 0; i < 10; ++i)
    {
        v1.push_back(i);
        cout << "STL Vector : " << v1.size() << " " << v1.capacity() << endl;
    }
    cout << "-----------------------------------------" << endl;

    // vector의 원소 확인
    for (int i = 0; i < v1.size(); ++i)
    {
        cout << v1[i] << " ";
    }
    cout << endl;

    // vector의 원소 확인
    for (vector<int>::iterator it = v1.begin(); it != v1.end(); ++it)
    {
        cout << (*it) << " ";
    }
    cout << endl << "-----------------------------------------" << endl;

    // ! --------------------------------------------------------------------------------

    Vector<int> v2;

    // vector 초기화
    for (int i = 0; i < 10; ++i)
    {
        v2.push_back(i);
        cout << "My Vector : " << v2.size() << " " << v2.capacity() << endl;
    }
    cout << "-----------------------------------------" << endl;

    // vector의 원소 확인
    for (int i = 0; i < v2.size(); ++i)
    {
        cout << v2[i] << " ";
    }
    cout << endl;
    
    for (Vector<int>::iterator it = v2.begin(); it != v2.end(); ++it)
    {
        cout << (*it) << " ";
    }

    return 0;
}