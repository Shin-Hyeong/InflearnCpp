#include <iostream>
using namespace std;

#include "Function.h"
/*
#pragma once
void Test_1();
void Test_2();
*/


void Test_1()
{
    Test_2();
}

void Test_2()
{
    cout << "Test_1를 통해서 Test_2를 호출함" << endl;
}