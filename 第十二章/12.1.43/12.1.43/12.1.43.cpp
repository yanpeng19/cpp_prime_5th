// 12.1.43.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class A
{
public:
	void d() { cout << "ceshi" << endl; }
};

int de()
{
	cout << "de::ceshi" << endl;
	return 0;
}

int main()
{
	typedef unique_ptr<int> IntP;
	int ix = 1024;
	int *pi = &ix;
	int *pi2 = new int(2048);
	IntP p(pi2);
	IntP P2(p.get());
	cout << *P2 << endl;
	delete(pi2);
	//p2.reset(p.release());
	

	system("pause");
    return 0;
}

