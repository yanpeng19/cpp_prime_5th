// 范形算法结构.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include < algorithm >

using namespace std;


int main()
{
	list<string> lst{ "fox","the","red","jumps","over","quick","red","slow","the","turtle" };
	lst.sort();
	lst.unique();

	for (auto a : lst)
		cout << a << endl;

	system("pause");
    return 0;
}

