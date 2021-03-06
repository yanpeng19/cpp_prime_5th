// 关联容器.cpp: 定义控制台应用程序的入口点。
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
	map<string, size_t> word_count;
	set<string> exclude = { "The","But","And" };
	string exclude_f(",.");

	string word;
	while (cin >> word)
		if (exclude.find(word) == exclude.end())
		{
			if (word[0] < 'a')
				word[0] += 32;
	
			auto pos = word.find_first_of(exclude_f);
			while (pos != string::npos)
			{
				word.erase(pos);
				pos = word.find_first_of(exclude_f);
			}
			++word_count[word];
		}
	for (auto &w : word_count)
		cout << w.first << " occurs" << w.second << endl;

	system("pause");
    return 0;
}

