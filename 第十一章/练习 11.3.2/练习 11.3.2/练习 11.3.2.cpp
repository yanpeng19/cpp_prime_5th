// 练习 11.3.2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main()
{
	map<string, size_t> word_cound;
	string fir, sec;
	
	multimap<string, vector<string>> my_map;
	
	// 练习11.22  pair<string,vector<int>     map<string,vector<int>> :: iterator
	cout << "Please input first name" << endl;
	while (cin >> fir &&fir!="exit")
	{
		//++word_cound.insert({ word,0 }).first->second;                 //练习 11.21
		/*//练习11.20/auto a = word_cound.insert(make_pair(word, 1));
		if (!a.first->second)
			a.first->second++;*/

		//练习11.24
		cout << "Please input second name" << endl;
		vector<string> v_sec;
		while (cin >> sec && sec != "exit")
		{
			v_sec.push_back(sec);
			cout << "Please continue" << endl;
		}
		my_map.insert(make_pair(fir, v_sec));
		cout << "Please input first name" << endl;
	}

	for (auto a : my_map)
	{
		cout << a.first << " :";
		for (auto b : a.second)
			cout << b << " ";
		cout << endl;
	}
	system("pause");
    return 0;
}

