// 11.3.5 访问元素.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <iostream>

using namespace std;

int main()
{
	//	map<int, int> my_map;
	//	for (int i = 0; i < 10; i++)
	//	{
	//		my_map[i] = i;
	//	}
	//	int a = 8;
	//	/*auto beg = my_map.lower_bound(a);
	//	auto end = my_map.upper_bound(a);
	//*/
	//	auto pos = my_map.equal_range(10);
	//	while (pos.first != pos.second)
	//	{
	//		cout << pos.first++->second << " ";
	//	}

	multimap<string, string> my_map{ {"dizi","jiuyangzhenjing"}, {"pangzi","jiuyinzhenjing"},{"dizi","dabaojian"},{"yizhongtian","pinsanguo"} };
	string temp;
	cin >> temp;
	//if(my_map.count(temp))
	//{
	//	my_map.erase(temp);//方法一

	//}

	auto pos = my_map.equal_range(temp);
	if (pos.first != pos.second)
	{
		my_map.erase(pos.first, pos.second);
	}
	else cout << " Not find " << temp << endl;

	for (auto a : my_map)
	{
		cout << a.first << " " << a.second << endl;
	}
	system("pause");
    return 0;
}

