// about namespace.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Sales_data.h"

using namespace std;

namespace my
{
	int i = 0;
	double d = 0;
	const int ci = 1000;
}

using namespace my;

int main()
{
	
	int i = 111111;
	double d = 3.1316;
	int iobj = ci + 1;
	++i;
	++::i;

	cout << i << endl;
	cout << d << endl;
	cout << iobj << endl;
	cout << ::i << endl;

	system("pause");
    return 0;
}

