// 练习16.2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include "Sales_data.h"

using namespace std;

template<typename T> bool compare(const T&l, const T&r)
{
	return l < r;
}

template<unsigned l, unsigned r>bool compare(const char(&a)[r], const char(&b)[l])
{
	return l < r;
}

int main()
{
	auto a = compare(1, 2);
	cout << a << endl;

	auto b = compare("baozi", "xiaodizi");
	cout << b;

	Sales_data sa, sb;
	sa = string("baobao");
	sb = string("xiaodzii");

	auto c = compare(sa, sb);

	system("pause");
    return 0;
}

