// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

template<unsigned i>
void print(const char(&p)[i])
{
	for (auto a : p)
		cout << a;
	cout << endl;
}

int main()
{
	char a[] = "guaibaoabo";
	char b[] = "xiaodizibaobei";

	print(a);
	print(b);

	system("pause");

    return 0;
}

