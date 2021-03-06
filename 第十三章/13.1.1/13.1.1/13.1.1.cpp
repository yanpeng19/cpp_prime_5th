// 13.1.1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class HasPtr
{
public:
	//HasPtr() = default;
	HasPtr(const std::string &s = std::string()) :
		ps(new std::string(s)), i(0) {
		cout << "一个创建" << endl;
	};

	HasPtr(HasPtr &h) :
		i(h.i), ps(new std::string(*h.ps) ) {
		cout << "一个创建" << endl;
	};
	HasPtr(const HasPtr &h) :
		i(h.i), ps(new std::string(*h.ps)) {
		cout << "一个创建" << endl;
	};


	HasPtr & operator=(const HasPtr& hp)
	{
		return HasPtr(hp);
	}

	~HasPtr() { cout << "销毁执行" << endl; };
//private:
	std::string *ps;
	int i;
};

HasPtr foo()
{
	HasPtr a, b;
	return a;
}
int main()
{
	
	/*a.i = 0;
	string s = "dizi";
	a.ps = &s;

	HasPtr b = a;

	cout << a.ps << endl;
	cout << b.ps << endl;

	cout << *(a.ps) << endl;
	cout << *(b.ps) << endl;*/

	HasPtr a(foo());
	a.i = 1;
	system("pause");
    return 0;
}

