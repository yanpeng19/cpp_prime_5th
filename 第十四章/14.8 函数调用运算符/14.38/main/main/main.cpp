// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct string_size
{
public:
	void operator()(string&s)
	{
		auto p = s.find_first_not_of(f);
		while ( p != string::npos && !s.empty())//去除单词内符号
		{
			s.erase(p, 1);
			p = s.find_first_not_of(f);
		}

		/*if (sint.find(s.size()) != sint.end())
			++s_times[s.size()];*/
		if (s.size() <= 9)
			++s_times["1-9"];
		else ++s_times["10+"];
		
	}
	map<string, size_t> getmap() { return s_times; }
private:
	set<int> sint{ 1,2,3,4,5,6,7,8,9 };
	string f = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	map<string, size_t> s_times;
};

int main()
{
	ifstream inf("D://story.txt");
	string_size ss;

	if (inf)
	{
		string s;
		while (inf >> s)
		{
			ss(s);
		}
		
	}
	else
	{
		cout << "open file fail" << endl;
		return -1;
	}

	auto m = ss.getmap();
	for (auto a : m)
	{
		cout << "word leigh long  " << a.first << " time is" << a.second << " times."<< endl;
	}

	system("pause");
    return 0;
}

