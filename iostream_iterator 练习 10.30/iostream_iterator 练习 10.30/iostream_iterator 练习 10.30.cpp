// iostream_iterator 练习 10.30.cpp: 定义控制台应用程序的入口点。
//
#include <iostream>
#include "stdafx.h"
#include <iterator>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;


int main()
{
	istream_iterator<int> int_it(std::cin), eof;
	vector<int> int_v;
	while (int_it != eof)
	{
		int_v.push_back(*int_it++);
	}
	sort(int_v.begin(), int_v.end());
	for (auto a : int_v)
		cout << a << endl;
	system("pause");
	
    return 0;
}

