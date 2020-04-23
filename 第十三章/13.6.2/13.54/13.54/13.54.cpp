// 13.54.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <Windows.h>

using namespace std;

class H
{
public:
	H(const string ss)
	{
		s = ss;
	}

	H(H&h) :
		s(h.s) {
		cout << "拷贝初始化" << endl;
	};
	H(H&&h) :
		s(h.s)
	{
		cout << "移动初始化" << endl;
	}
	H & operator = (H h)
	{
		s = h.s;
		cout << "赋值运算符" << endl;
	}
	//H &operator =(H &&h)
	//{
	//	cout << "移动复制运算符" << endl;
	//}

	string s;


};

int main()
{
	H a("baozi");
	H b = a;

	system("pause");
    return 0;
}

