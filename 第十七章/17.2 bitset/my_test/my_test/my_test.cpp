// my_test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

class test_resault
{
public:

private:
	vector<int> res;
};

int main()
{
	bitset<32> a(1);
	a.set();
	a.flip();
	cout << a << endl;
	cout << a.size() << endl;
	a.set();

	cout << a << endl;
	cout << a.all() << endl;

	auto s = a.to_string(0, 1);
	cout << a << endl;

	system("pause");
    return 0;
}


