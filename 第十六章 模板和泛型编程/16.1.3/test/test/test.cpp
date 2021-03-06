// test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

template<typename T>
bool temp(T &i, T &j)
{
	return i < j;
}

bool temp_int(int &i, int&j)
{
	return i < j;
}



template<typename T>
T& compare(T&a, T&b)
{
	return a < b ? a : b;
}

template<typename IT>
auto fun3(IT beg, IT end) ->decltype(*beg + 0)
{
	return *beg;
}

template<typename T>
auto my_sum(T beg, T end) -> typename remove_reference<decltype(*beg)>::type
{
	auto sum = *beg;
	auto a = ++beg;
	while (a != end)
		sum = sum + *a++;
	return sum;
}

template<typename T>
void fun(T&t)
{
	t++;
}

template<typename T>
void g(T&& val)
{
	vector<T> v;
	system("pause");
	return;
}

template<typename F, typename T1, typename T2>
void flip1(F f,T1&& t1,T2&& t2)
{
	f(t2,forward<T1>(t1));
}

void fun1(int &i1, int &&i2)
{
	i1 += i1;
	i2 -= 1;
}

int main()
{
	int i1 = 50;
	int i2 = 20;
	flip1(fun1, 501,42);
	cout << i1 << endl;
	cout << i2 << endl;
	system("pause");
    return 0;
}