// 17.14-17。16.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>


using namespace std;

int main()
{
	string s("[^c]ei");

	//s = "[[:alpha:]]*" + s + "[[:alpha:]]*";
	regex r(s);

	try {
		string text;
		while (cin >> text)
		{
			smatch resault;
			if (regex_search(text, resault, r))
				cout << resault.str() << endl;
			else cout << "not find" << endl;
		}
	}
	catch (regex_error e)
	{
		cout << e.what() << "\ncode: " << e.code() << endl;
	}

	system("pause");
    return 0;
}

