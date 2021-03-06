// my_setbit.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>

using namespace std;

////17.11
//class Text_Resault
//{
//public:
//	void text(const int&, const bool&);
//private:
//	vector<bool> res;
//};
//
//void Text_Resault::text(const int& i,const bool &b)
//{
//	res[i] = b;
//}


//17.13
class Text_Resault
{
public:
	void text(const unsigned int&, const bool&);
	void get_res();
	void print() 
	{ 
		for (size_t i = 0; i < 100; i++)
			cout << "No." << i+1 << " : "
			<< res[i] << endl;
	}
private:
	bitset<100> res;
};

void Text_Resault::text(const unsigned int&i, const bool& b)
{
	res.set(i, b);
}

void Text_Resault::get_res() // 生成成绩
{
	
	stringstream is;

	for(int i=0;i<100;i++)
		is << (rand() % 2);
	is >> res;
}

int main()
{
	Text_Resault t;
	t.get_res();

	t.print();

	system("pause");
    return 0;
}

