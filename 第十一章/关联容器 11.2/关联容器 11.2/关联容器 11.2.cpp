// 关联容器 11.2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>


using namespace std;

int main()
{
	map<string,vector<pair<string,string>>> family;
	string fir;
	string sec;
	string bri;

	cout << "Please input first name" << endl;

	while (cin >> fir && fir!="exit")
	{
		cout << "Please input secend name and birsday" << endl;
		while (cin >> sec&& sec != "exit")
		{
			cin >> bri;
			pair<string, string> temp = make_pair(sec, bri);
			family[fir].push_back(temp);
		}
		cout << "Please input first name :" << endl;
	}
	
	for (auto a : family)
	{
		cout << "Family " << a.first << ": " << endl;
		for (auto b : a.second)
		{
			cout << " " << b.first << " birsday is : " << b.second;
			cout << endl;
		}
			
	}

	system("pause");
    return 0;
}

