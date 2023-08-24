#include <iostream>
using namespace std;

// 동적 프로그래밍
int fibonacci(int n);
int f[100] = {0,};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int num;
    cin >> num;

    cout << fibonacci(num) << "\n";
    return 0;
}

int fibonacci(int n){
    if(f[n] != 0) {
        return f[n];
    }
    else{
        if(n == 1 || n == 2){
            f[n] = 1;
        }
        else {
            f[n] = fibonacci(n - 1) + fibonacci(n - 2);
        }
        return f[n];
    }
}

/* 동적프로그래밍 X
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int num;
    cin >> num;

    cout << fibonacci(num) << "\n";
    return 0;
}

int fibonacci(int n){
    if(n == 1 || n == 0){
        return 1;
    }
    else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}
*/