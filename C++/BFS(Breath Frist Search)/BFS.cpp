#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int number = 7;
int c[7];
vector<int> a[7 + 1]; // 8개의 배열이 각각 vector 형태를 띔.
void bfs(int start);

int main(){
    ios_base:: sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    /*1과 2를 연결*/
    a[1].push_back(2);
    a[2].push_back(1);
    /*1과 3를 연결*/
    a[1].push_back(3);
    a[3].push_back(1);
    /*2과 3를 연결*/
    a[2].push_back(3);
    a[3].push_back(2);
    /*2과 4를 연결*/
    a[2].push_back(4);
    a[4].push_back(2);
    /*2과 5를 연결*/
    a[2].push_back(5);
    a[5].push_back(2);
    /*4과 5를 연결*/
    a[4].push_back(5);
    a[5].push_back(4);
    /*3과 6를 연결*/
    a[3].push_back(6);
    a[6].push_back(3);
    /*3과 7를 연결*/
    a[3].push_back(7);
    a[7].push_back(3);
    /*6과 7를 연결*/
    a[7].push_back(6);
    a[6].push_back(7);

    bfs(1);

    return 0;
}

void bfs(int start){
    queue<int> q;
    q.push(start); //처음 시작점을 Queue에 담음.
    c[start] = true; // 시작점을 확인했다(방문했다)
    while(!q.empty()){ //Queue에 내용이 있다면 실행
        int x = q.front();
        q.pop();
        cout << x << " "; //Queue 맨 앞에 있는 노드 번호를 출력
        for(int i = 0; i < a[x].size(); i++){
            int y = a[x][i];    //Queue 맨 앞에 있는 노드와 인접한 노드 검색
            if(!c[y]){          //검색 된 노드가 방문한 적이 없다면 실행
                q.push(y);      //방문한 적 없는 노드를 Queue에 입력
                c[y] = true;    //방문한 적 있다고 표시.
            }
        }
    }
}