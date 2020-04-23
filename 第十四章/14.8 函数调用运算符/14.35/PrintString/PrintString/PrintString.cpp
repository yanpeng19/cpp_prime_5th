// PrintString.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Myin
{
public:
	Myin(istream &i = cin, string t = "") :is(i), s(t) {};

	vector<string> operator()()
	{
		while (is >> s)
			vs.push_back(s);
		return vs;
	}

private:
	istream& is;
	string s;
	vector<string> vs;
};

int main()
{
	Myin s;
	vector<string> vs = s();
	for (auto a : vs)
	{
		cout << a << endl;
	}

	system("pause");
    return 0;
}

