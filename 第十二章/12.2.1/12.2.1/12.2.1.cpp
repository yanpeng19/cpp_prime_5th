// 12.2.1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

//std::string lin(const string &a, const string &b)
//{
//	return a+b;
//}


int main()
{
	string a;
	cin >> a;
	char *p = new char[a.size() + 1];
	for (size_t i = 0; i < a.size() + 1; i++)
	{
		p[i] = a[i];
	}
	

	//unique_ptr<string[]> u(new string[10]);
	////u[0] = lin("dizi", "baobao");

	//for (size_t i = 0; i < 10; i++)
	//{
	//	cout << u[i] << endl;
	//}
	//cout << p << endl;
	for (size_t i = 0; i < a.size() + 1; i++)
	{
		cout << p[i];
	}
	cout << endl;
	delete[] p;
	system("pause");
    return 0;
}

