// main.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <map>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

void get_file(vector<string> &file, map<string, vector<string>>&rule, ifstream &text, ifstream &frule)
{
	string line;
	while (getline(text, line))
		file.push_back(line);
	while (getline(frule, line))
	{
		istringstream is(line);
		string first, temp;
		is >> first;
		while (is >> temp)
			rule[first].push_back(temp);
	}
	return;
}

void print(const vector<string> &file, map<string, vector<string>>&rule)
{
	static default_random_engine e(time(0));
	static uniform_int_distribution<unsigned> u(0, 1);

	for (auto line : file)
	{
		string word;
		istringstream is_line(line);
		ostringstream os_line;
		unsigned i = u(e);

		//for (auto a : rule)
		//{
		//	for (auto b : a.second)
		//	{
		//		cout << b << " ";
		//	}
		//	cout << endl;
		//}


		while (is_line >> word)
		{
			if (rule.find(word) != rule.end())
			{
				if (i > rule[word].size())
				{
					cerr << "下标错误" << endl;
				}

				else os_line << rule[word][i] << " ";
			}
			else os_line << word << " ";
		}
		cout << os_line.str() << endl;
	}
	return;
}

int main()
{


	vector<string> file;
	map<string, vector<string>> rule;
	ifstream text("D:/text.txt");
	ifstream frule("D:/rule.txt");
	if (text.is_open() && frule.is_open())
	{
		get_file(file, rule, text, frule);
		print(file, rule);
	}

	system("pause");

	return 0;
}
