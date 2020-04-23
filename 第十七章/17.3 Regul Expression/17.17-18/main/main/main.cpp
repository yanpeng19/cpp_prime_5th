// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

int main()
{
	string s("[^c]ei");
	s = "[[:alpha:]]*" + s + "[[:alpha:]]*";
	regex r(s,regex::icase);
	string text("dizi baobao pangzi xiang hei lai baozi qei");

	//smatch resault;
	//regex_search(text, resault, r);

	//cout << resault.str() << endl;

	for (sregex_iterator it(text.begin(), text.end(), r), end_it;
		it != end_it; it++)
		cout << it->str() << endl;

	system("pause");
    return 0;
}

