// #ifndef 보다 #pragma once가 최적화가 좋다.
#pragma once

// #pragma once의 옛날방식
// _FUNCTION_H__이 정의 되어 있지 않으면
// #ifndef _FUNCTION_H__

// _FUNCTION_H__를 정의해라
// 정의 되어있다면 endif 다음으로 넘어간다.
// #define _FUNCTION_H__

// 헤더 파일은 간단하게 유지해야 한다.
// #include <iostream>를 헤더에 넣으면 #include하는 파일이 할일이 증폭된다.
// #include <iostream>
// using namespace std;

// 함수나 구조체 등 선언용으로 사용해야 한다.

void Test_1();

void Test_2();

// #endif