// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Sales_data.h"

using namespace std;


int main()
{
	Sales_data a("110", 5, 20);
	Sales_data b("333", 5, 33);
	cout << a + b << endl;
	system("pause");
    return 0;
}





