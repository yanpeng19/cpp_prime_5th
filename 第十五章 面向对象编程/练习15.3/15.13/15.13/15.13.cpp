// 15.13.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class base
{
public:
	base() :basename("dizi") {};
	string name() { return basename; };
	virtual void print(ostream &os)
	{
		os << name();
	}
	void newname()
	{
		getline(cin, basename);
	}

private:
	string basename;
};

class derived :public base
{
public:
	void print(ostream &os)
	{
		base::print(os);
		os << " " << i;
	}

private:
	int i;
};

void out(base &item)
{
	item.print(cout);
}

int main()
{
	base a;
	derived b;
	
	b.newname();
	
	cout << a.name() << endl;
	cout << b.name() << endl;

	system("pause");

    return 0;
}

