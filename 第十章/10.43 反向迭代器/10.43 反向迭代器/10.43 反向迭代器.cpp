// 10.43 反向迭代器.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <list>

using namespace std;

int main()
{
	vector<int> int_l{ 1,2,3,4,5,6,7,8,9,10};
	list<int> lst;
	auto coma = int_l.rbegin() + 4;
	while (coma != int_l.rend() - 2)
		lst.push_back(*coma++.base());

	for (auto a : lst)
	{
		cout << a << endl;
	}

	system("pause");

    return 0;
}

