// if-then-else.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

struct ite
{
	ite(int temp = 10, int temp_t = 1, int temp_f = 0) :term(temp), t(temp_t), f(temp_f)
	{};
	int operator()(int n)
	{
		return n > term ? t : f;
	}

private:
	int term;
	int t;
	int f;
};
int main()
{
	ite a(2, 1, 0);
	cout << a(5);
	system("pause");
    return 0;
}

