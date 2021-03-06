// 13.56-58.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Foo
{
public:
	Foo sorted() && ;
	Foo sorted() const &;

private:
	vector<int> data{ 1,2,3,5,60 };
};

Foo Foo::sorted() &&
{
	sort(data.begin(), data.end());
	cout << "右值版本" << endl;
	return *this;
}

Foo Foo::sorted() const &
{
	//Foo ret(*this);
	//sort(ret.data.begin(), ret.data.end());
	cout << "左值版本" << endl;
	//return ret;

	return Foo(*this).sorted();
}

int main()
{
	Foo f1;
	Foo f2 = f1.sorted();

	system("pause");
    return 0;
}

