// amin.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	bool a = true;
	int i = 10;
	double d = 3.1415926;

	auto n = cout.precision(1);

	cout << d << endl;
	system("pause");

    return 0;
}

