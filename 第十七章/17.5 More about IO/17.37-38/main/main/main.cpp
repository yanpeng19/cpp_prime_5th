// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
	ifstream is("D:/story.txt");
	if (is.is_open())
	{
		string temp;
		char c[2000];
		int i = 0;
		while (is.getline(c, 2000, '\n'))
		{
			cout << "line " << ++i << " : "<< c << '\n';
		}
		
	}
	system("pause");
    return 0;
}

