// 11.3 关联容器操作.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <utility>

using namespace std;

int main()
{
	//map<const string, size_t>::iterator  imp;
	map<string, int> my_map;
	auto it_map = back_inserter(my_map);
	string ts;
	int ti;

	cin >> ts;
	cin >> ti;
	//my_map.insert(pair<string, int>(ts, ti));
	pair<string, int> temp = make_pair(ts, ti);
	*it_map = temp;
	for (auto a : my_map)
	{
		cout << a.first << " " << a.second;
	}

	system("pause");
    return 0;
}

