// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	fstream f("D:/1.txt",fstream::ate|fstream::in|fstream::out);
	if (!f)
	{
		cout << "文件不存在" << endl;
		return EXIT_FAILURE;
	}
	auto end_mark = f.tellg();
	f.seekg(0, fstream::beg);
	int i = 0, sum = 0;
	char line[256];
	string sline;
	ostringstream oss;

	while (f.getline(line, 256, '\n'))
	{
		ostringstream temp;
		temp << line;
		i = temp.str().size()+1;
		sum += i;
		oss << sum << " ";
	}
	f.close();
	ofstream of("D:/1.txt", ofstream::app);
	of << '\n' << oss.str();

	system("pause");
    return 0;
}

