// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

template<unsigned t>
constexpr size_t my_size(const char(&p)[t])
{
	return t;
}

int main()
{
	string s = "dizibaobao";
	auto a = my_size("dizixiaobaoabo");
	cout << a;
	system("pause");
    return 0;
}

