// 12.263.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main()
{
	allocator<string> allc_s;
	int n;
	cin >> n;
	//分配空间
	auto p = allc_s.allocate(n);
	auto q = p;

	string s;
	//构造函数
	while (q != p + n&&cin >> s)
		allc_s.construct(q++, s);


	while (q != p)
	{
		cout << *--q << endl;
		allc_s.destroy(q);
	}

	allc_s.deallocate(p, n);

	system("pause");
    return 0;
}

