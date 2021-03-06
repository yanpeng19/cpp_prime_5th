// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <sstream>

using namespace std;


bool check(const smatch&m)
{
	if (m[1].matched)
	{
		return m[3].matched && (m[4].matched == 0 || m[4].str() == " ");
	}
	else
		return !m[3].matched && m[4].str() == m[6].str();
}

struct p
{
	string name;
	vector<string> phone;
};
int main()
{
	vector<p> data;
	ifstream f("D:/phone.txt");
	if (f)
	{
		string line;
		while (getline(f,line))
		{
			string word;
			p temp;
			istringstream ifs(line);
			ifs >> word;
			temp.name = word;
			while (ifs >> word)
				temp.phone.push_back(word);
			data.push_back(temp);
		}
	}
	else
	{
		cerr << "input error " << endl;
		system("pause");
		return 0;
	}


	//while (getline(cin, temp))
	//{
	//	for (sregex_iterator it(temp.begin(), temp.end(), r_phone), end_if;
	//		it != end_if; it++)
	//	{
	//		if (check(*it))
	//			cout << "valid: " << it->str() << endl;
	//		else
	//			cout << "not valid" << it->str() << endl;
	//	}
	//}
	string s("(\\()?(\\d{3})(\\))?([-. ]\\s*)?(\\d{3})([-. ]\\s*)?(\\d{4})");
	regex r_phone(s);
	for (auto a : data)
	{
		ostringstream oss, error;
		oss << a.name << " :";
		if (!a.phone.empty())
			for (auto n : a.phone)
			{
				sregex_iterator item(n.begin(), n.end(), r_phone), end_if;
				if (item == end_if|| !check(*item)) error << n << " ";
				else oss << n << " ";
			}
		cout << oss.str() << endl;
		if (error.str() != "")
			cout << "wrong numbers: " << error.str() << endl << endl;
	}

	system("pause");
    return 0;
}

