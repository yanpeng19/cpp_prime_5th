// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>

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

int main()
{
	//17.20
	//string s("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");

	//17.22
	string s("(\\()?(\\d{3})(\\))?([-. ]\\s*)?(\\d{3})([-. ]\\s*)?(\\d{4})");
	
	regex r_phone(s);

	string temp;
	while (getline(cin,temp))
	{
		for (sregex_iterator it(temp.begin(), temp.end(), r_phone), end_if;
			it != end_if; it++)
		{
			if (check(*it))
				cout << "valid: " << it->str() << endl;
			else
				cout << "not valid" << it->str() << endl;
		}
	}

    return 0;
}

