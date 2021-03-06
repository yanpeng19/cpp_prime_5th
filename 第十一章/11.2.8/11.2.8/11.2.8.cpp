// 11.2.8.cpp: 定义控制台应用程序的入口点。
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
	vector<string> vec;
	set<string>  sst;
	string word;

	while (cin >> word)               //  set的内容是自动按照字典序排列的
	{
		sst.insert(word);

		if (find(vec.begin(), vec.end(), word) == vec.end())
			vec.push_back(word);
	}
	for (auto a : sst)
		cout << a << endl;
	cout << endl;
	for (auto a : vec)
		cout << a << endl;
	system("pause");
    return 0;
}

