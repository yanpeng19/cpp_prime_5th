// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

class Screen
{
public:
	typedef std::string::size_type pos;

	Screen() = default;
	Screen(pos ht, pos wd, char c) :
		height(ht), width(wd), content(ht*wd, c) {};

	char get() const
	{
		return content[cursor];
	}

	inline char get(pos ht, pos wd) const;
	Screen& move(pos r, pos c);
	Screen& set(char);
	Screen& set(pos, pos, char);

private:
	string content;
	pos cursor = 0;
	pos height = 0;
	pos width = 0;
};

Screen& Screen::move(pos r, pos c)
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}

char Screen::get(pos r, pos c) const
{
	pos row = r * width;
	return content[row + c];
}

inline Screen& Screen::set(char c)
{
	content[cursor] = c;
	return *this;
}

inline Screen& Screen::set(pos r,pos w,char c)
{
	content[r*width+w] = c;
	return *this;
}

int main()
{
	Screen sc(10, 10, '%');
	cout << sc.get() << endl;
	cout << sc.get(2, 5) << endl;
	system("pause");
    return 0;
}

