#include <iostream>
#include <deque>
#include <vector>
using namespace std;

// Deque

// 시퀀스 컨테이너(Sequence Container) : 데이터가 삽입 순서대로 나열되는 형태의 컨테이너
// vector(동적 배열), list(이중 연결 리스트), deque(double-ended- queue(양방향 큐), 데크)

// deque
// vector와 list의 중간 느낌
// list처럼 공간이 부족하면 새로운 영역에 연결하는 식으로 함.
// 하나의 공간에 vector처럼 연속적으로 저장함.

// vector
// [1,2,3,4,5,6]

// list
// [1] <-> [2] <-> [3] <-> [4]

// deque
// [1,2,3] <-> [4,5,6] <-> [7,8]

// - deque의 동작원리
// - 중간 삽입/삭제 (BAD/BAD)
// - 처음/끝 삽입/삭제 (GOOD/GOOD)
// vector는 처음 삽입/삭제는 느림
// - 임의 접근 (GOOD)

int main ()
{   
    deque<int> dq1;

    dq1.push_back(1);
    dq1.push_front(0);

    //dq.capacity(); -> 동적할당이 아니기 때문에 없음.

    // 임의 접근 연산자 지원
    cout << dq1[0] << endl;

    // vector와 마찬가지로 배열 기반으로 동작
    // 다만 메모리 할당 정책이 다르다

    // ! - deque의 동작원리 & 처음/끝 삽입/삭제

    // size : 3, 원소값들을 1로 초기화
    vector<int> v1(3, 1);
    // deque
    // [1 1 1  ]
    deque<int> dq2(3,1);

    // 할당된 메모리보다 더 많은 데이터가 들어오면 더 넓은 메모리를 할당받아 다른 주소로 이동함.
    v1.push_back(2);
    v1.push_back(2);

    // deque 끝 삽입
    // [1 1 1 2]
    dq2.push_back(2);
    // deque
    // [1 1 1 2] <-> [2       ]
    dq2.push_back(2);

    // deque 처음 삽입
    // [      3] <-> [1 1 1 2] <-> [2       ]
    dq2.push_front(3);
    // [    3 3] <-> [1 1 1 2] <-> [2       ]
    dq2.push_front(3);

    // ! - 중간 삽입/삭제
    // vector와 동일하게 중간에 값이 삽입/삭제되면 원소들이 뒤로/앞으로 이동한다.
    
    // ! - 임의 접근
    // deque에 원하는 인덱스를 가르키는 수학적 수식을 통해 인덱스에 접근함.
    // _Size_type _Block = _MyCont->_GetBlock(_MyOff);  ->  원하는 인덱스가 몇번 block에 있는지 
    // _Size_type _Off = _MyOff % _DEQUESIZE(환경에 따라 다름. 예시에선 4);   ->  블록에서 몇번에 있는지
    // return _MyCont->_Map[_Block][_Off];  ->  찾아서 반환

    // 예시 : 아파트
    // [ 1호 2호 3호 4호 ] 1동
    // [ 1호 2호 3호 4호 ] 2동
    // [ 1호 2호 3호 4호 ] 3동
    // 2동 3호 인덱스 출력
    dq2[3] = 10;
    cout << dq2[3] << endl;

    // ! 중간 삽입/삭제가 느리다 -> 임의 접근을 하기 위함 -> 데이터가 빈칸 없이 있어야 함
    // ! 중간 삽입/삭제가 빠르다 -> 임의 접근이 어렵거나 느림 -> 데이터와 데이터 이동이 느림.

    return 0;
}