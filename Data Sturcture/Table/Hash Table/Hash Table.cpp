#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

// 해시 테이블

// Q) map과 hash_map의 차이 (C++11 표준 unordred_map)
// map : Red-Black Tree로 이루어짐
// - 추가 / 탐색 / 삭제의 시간 복잡도		O(logN) 

// C# dictionary = C++ map				(X)
// C# dictionary = C++ unordered_map	(O)

// hash_map (unordered_map)
// - 추가 / 탐색 / 삭제의 시간 복잡도		O(1)
// 메모리를 손해를 보고 속도를 얻어냄
// 메모리가 제한되지 않는다면 단순하게 필요한 배열만큼 생성함
// userID가 1 ~ 999임
// [1][2][3][4][5][...][999]를 단순하게 생성함

// "해시" "테이블"의 의미가 중요함
// 해시 : hash를 통해 key값을 얻어 key값에 맞는 테이블위치에 저장함
// 테이블 : 메모리를 사용하여 빠르게 접근하고 삭제, 수정 등이 가능함

// Red-Black Tree : HashTable보다 추가 / 탐색 / 삭제가 느리지만 정렬이 됨		O(logN)
// HashTable : Red-Black Tree보다 추가 / 탐색 / 삭제가 빠르지만 정렬은 안됨		O(1)

// 테이블
void TestTable()
{
	struct User
	{
		int userId = 0;
		string userName;	
	};

	vector<User> users;
	users.resize(1000);

	// 777번의 유저 정보 설정
	// 777 -> 키값
	users[777] = User{ 777, "Temp" };

	// 777번의 유저의 이름은?
	if (users[777].userId != 0)
	{
		string name = users[777].userName;
		cout << name << endl;
	}

	// 테이블
	// 키를 알면, 데이터를 단번에 찾을 수 있다.

	// 문제의 상황
	// int32_Max (3억 언저리)
	// 메모리를 손해를 봐도 정도가 있음 -> 메모리가 무한은 아니기 때문
	// hash 기법을 사용하여 문제를 해결
}

// 해시
// 개념 : 보안이라도 연관있음
// - 특정 사이트에 가입할 때 ID(Temp) + PW(qwe123)를 입력함
// - 가입되면 DB에 [Temp, qwe123]으로 저장되면 해킹시 위험이 큼
// - hash 함수를 통해 비밀번호를 암화화함 -> hash(qwe123) -> sxazfasdfas234#$@#
// - DB에 [Temp, sxazfasdfas234#$@#]으로 저장됨
// - 이런 시스템에 의해 비밀번호를 찾기하면 비밀번호를 알수 있는게 아니라 새 비밀번호를 설정하도록 함
// -- 사이트 운영사측에서도 비밀번호를 알수 없음
void TestHash()
{
	struct User
	{
		int userId = 0; // 1 ~ int32_max
		string userName;
	};

	vector<User> users;
	users.resize(1000);

	// 123456번의 유저 정보 설정
	// 777 -> 키값
	const int userId = 123456;
	// Hash 기능
	// Hash는 모두 다른 알고리즘에 의해 값을 암호화함
	int key = (userId % 1000); 
	// 555번에 123456번 유저 정보를 저장함
	users[key] = User{ userId, "Temp" };

	// 123456번의 유저의 이름은?
	// key을 통해 user에 저장된 위치를 찾아옴
	User& user = users[key];
	// 찾은 위치에 맞는 데이터가 있는지 확인
	if (user.userId == userId)
	{
		string name = user.userName;
		cout << name << endl;
	}

	// 충돌 문제가 발생할 수 있음
	// - 동일한 key를 가질 경우
	// 충돌이 발생한 자리를 대신해서 다른 빈자리를 찾아나서면 됨.
	// - 선형 조사법 (linear probing)
	// hash(key)가 자리가 있다면 바로 다음값(+N)에 넣을려고 시도함
	// - [충돌][시도] -> [충돌][충돌][시도] -> [충돌][충돌][성공]
	// 
	// - 이차 조사법 (quadratic probing)
	// hash(key)가 자리가 있다면 + N^2 자리에 넣을려고 시도함. 선형조사법보다 좀더 분산시킴
	// - 10 : 충돌 -> 10 + 1^2 = 11에 시도 / 11 : 충돌  -> 10 + 2^2 = 14에 시도


	
}

// 체이닝
// 데이터가 엄청나게 방대할 경우(테이블을 늘리는 것만으로 부족할 경우)
// 테이블을 단순한 구조체로 설계하지 않고 list나 vector로 설계하여 동일한 key값을 같은 곳에 저장할 수 있도록 함
void TestHashTableChaining()
{
	struct User
	{
		int userId = 0; // 1 ~ int32_max
		string userName;
	};

	//		 [777]
	// [][][][777][][]
	vector<vector<User>> users;
	users.resize(1000);

	// 1번 유저
	const int userID1 = 777;
	int key1 = userID1 % 1000;

	users[key1].push_back(User{ userID1, "Temp1" });
	
	// 2번 유저
	const int userID2 = 1777;
	int key2 = userID2 % 1000;
	users[key2].push_back(User{ userID2, "Temp2" });

	// 1번, 2번 유저 둘다 key 777이고 같은 위치에 저장됨

	// 2번 유저의 이름은?
	// 2번 유저가 저장된 key 위치을 찾음
	vector<User>& bucket = users[key2];
	// key위치에 저장된 vector를 순회하면서 같은 ID가 있는지 찾음
	for (User& user : bucket)
	{
		if (user.userId == userID2)
		{
			string name = user.userName;
			cout << name << endl;
		}
	}


}

int main()
{
	// TestHash();
	TestHashTableChaining();

	return 0;
}