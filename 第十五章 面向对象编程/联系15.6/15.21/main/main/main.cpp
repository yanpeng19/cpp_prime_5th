// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Image
{
public:
	Image() = default;
	Image(vector<string> v) :
		vs(v) {};
	virtual ~Image() = default;
	string name{ "kong" };
protected:
	void s() { cout << size; }

private:
	vector<string> vs = { "xiang","bao","dizi","zi" };
	size_t size = 0;
};

class gif :Image
{
	;
};

int main()
{
    return 0;
}

