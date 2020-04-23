// 14.37.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

struct eq
{

public:
	eq(int m) :i(m){};
	void operator()(int &n)
	{
		if (n == i) n = -1;
		else cout << n;
	}


private:
	int i;
};

int main()
{
	vector<int> vi;
	for (int i = 0; i < 10; i++)
	{
		vi.push_back(i);
	}

	for_each(vi.begin(), vi.end(), eq(5));	
	cout << endl;

	for (auto a : vi)
		cout << a << endl;

	system("pause");
    return 0;
}

