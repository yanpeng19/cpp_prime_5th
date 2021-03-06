// 练习 10.33.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>

using namespace std;

void file(vector<string> f_name)
{
	string path, suffix;
	path = "D://";
	suffix = ".txt";
	auto f = f_name.begin();
	while (f != f_name.end())             // 文件名路径处理
	{
		*f++ = path + *f + suffix;
	}

	ofstream os_1, os_2,os_temp;
	fstream if_1, if_temp;
	//const char temp1[]= f_name[1].c_str();
	//const char temp2[] = f_name[2].c_str();	
	os_1.open((const char*)f_name[1].c_str());
	os_2.open(f_name[2].c_str());
	if_1.open(f_name[0].c_str());
	os_temp.open("D://temp.txt");
	if_temp.open("D://temp.txt");

	if(os_1.is_open()&&os_2.is_open())
	{
		ostream_iterator<int> out1(os_1, " "), out2(os_2, "\n");
		istream_iterator<int> in_f(if_1), eof;
		string temp;
		string num("123456789");

		while (if_1 >> temp)
		{
			string::size_type pos = 0;
			while ((pos = temp.find_first_not_of(num,pos)) != string::npos)
			{
				temp[pos++] = ' ';
			}
			os_temp << temp << "\n";
		}
		os_temp.close();
		string temp_n;
		while (if_temp >> temp_n)
		{
			int n = atoi(temp_n.c_str());
			if (n%2) *out1 = n;
			else *out2 = n;
		}
	
	}
	


	return;
}

int main()
{
	vector<string> f_name = {"1","2","3"};
	//istream_iterator<string> in(cin);
	string temp;
	/*while(cin >> temp)
	{
		f_name.push_back(temp);
	}*/
	/*for (auto a : f_name)
	{
		cout << a << endl;
	}*/
	file(f_name);
	system("pause");
    return 0;
}

