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

int main()
{
	string s("(\\()?(\\d{3})(\\))?([-.]\\s*)?(\\d{3})([-.]\\s*)?(\\d{4})");
	regex r(s);
	string r2("$2.$5.$7");
	ifstream inf("D:/phone.txt");
	

	if (inf)
	{
		string line;
		while (getline(inf, line))
		{

			
			smatch stemp;
			string temp;
			// 17.24
			//temp = regex_replace(line, r, r2);
			//17.25
			istringstream is(line);
			is >> temp;
			cout << temp << " ";
			temp = is.str();
			regex_search(temp, stemp,r);

			cout << stemp.str() << endl;

			

		}

	}

	system("pause");

    return 0;
}

