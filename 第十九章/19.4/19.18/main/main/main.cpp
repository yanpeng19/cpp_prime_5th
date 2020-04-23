// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;


int main()
{
	vector<string> vt{ "dizi","baobao","pang","","","xiangdizi","baoao!" };

	//auto i = count_if(vt.begin(), vt.end(), [](const string&t) {return t.empty(); });
	//auto i = count_if(vt.begin(), vt.end(), mem_fn(&string::empty));
	auto i = count_if(vt.begin(), vt.end(), bind(&string::empty, std::placeholders::_1));

	cout << i;

	system("pause");
    return 0;
}

