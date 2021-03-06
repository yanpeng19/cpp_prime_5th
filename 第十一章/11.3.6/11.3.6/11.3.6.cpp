// 11.3.6.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <iterator>
#include <fstream>
#include <sstream>

using namespace std;

map<string,string> build_map(ifstream &rule)//创建字典
{
	map<string, string> map;
	string key;
	string value;

	
	while(rule >> key && getline(rule, value))
	{
		if (value.size() > 1)
			//map[key] = value.substr(1);
			map.insert({ key,value.substr(1) });//隐式插入了一个pair?
		else throw runtime_error( "no rule for "+ key);
	}
	return map;
}

const string transform(const string word, const map<string, string> m)
{
	auto pos = m.find(word);
	if (pos != m.end())
	{
		return pos->second;
	}
	return word;
}


int main()
{
	ifstream rule_file("D://f1.txt");
	ifstream target_file("D://f2.txt");
	string line, word;
	if (rule_file.is_open() && target_file.is_open())
	{
		;
	}
	else
	{
		cout << "File error" << endl;
		return -1;
	}
	auto m = build_map(rule_file);   //生成字典
	while (getline(target_file,line))
	{
		istringstream i(line);
		bool first = true;
		while (i >> word)
		{
			if(first)
				first = false;
			else cout << " ";

			cout << transform(word, m);
		}
		cout << endl;
	}



	system("pause");
    return 0;
}

