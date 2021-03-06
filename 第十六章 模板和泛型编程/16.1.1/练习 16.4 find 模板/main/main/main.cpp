// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

template<typename I,typename T>
I my_find(I begin,I end,T t)
{
	while (begin != end)
		if (*begin == t)
			return begin;
		else begin++;

		return end;

}

int main()
{
	vector<int> va{ 5,2,6 };
	list<string> ls{ "xiaoz","dizi","baoboa" };

	auto a = my_find(va.begin(),va.end(),9);
	auto b = my_find(ls.begin(),ls.end(),"dizi");

	cout << *a << endl;
	cout << *b << endl;

	system("pause");

    return 0;
}

