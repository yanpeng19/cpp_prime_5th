// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "Screen.h"
#include <string>

using namespace std;



int main()
{
	Screen a(10, 10, 'a');

	const string::size_type Screen::*pdata = Screen::get_cur();

	auto i = a.*pdata;
	
	cout << i << endl;

	system("pause");
    return 0;
}

