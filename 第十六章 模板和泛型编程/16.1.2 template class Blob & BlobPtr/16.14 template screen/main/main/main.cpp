// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

template<const unsigned h,const unsigned w>
class screen
{
	using pos = string::size_type;

	template<const unsigned h, const unsigned w>
	friend ostream& operator<<(ostream& os, const screen<h, w>& s);

	template<const unsigned h, const unsigned w>
	friend istream& operator>>(istream& is, screen<h, w>& s);

public:
	screen() = default;
	screen(const char&c) :
		contents(h*w, c) {};

	
	screen(const screen<h,w> &c) :
		contents(c.contents), corsor(c.corsor) {};


	char get() const { return contents[corsor]; };
	char get(pos ht, pos wd) const
	{
		if (ht*wd > contents.size())
			throw out_of_range("xiabiaocuowu ");
		return contents[ht*w + wd];
	}
	screen& operator=(const screen<h,w>& s)
	{
		contents = s.contents;
		corsor = s.corsor;
		return *this;
	}
	screen& operator++();
	screen& move(pos r, pos c);
	screen& set(char);
	screen& set(pos, pos, char);

private:
	string contents;
	pos corsor = 0;
};

template<const unsigned h,const unsigned w>
screen<h,w>& screen<h,w>::move(pos r, pos c)
{
	if (r <= h & c <= w)
	{
		cursor = r * w + c;
		return *this;
	}
	throw out_of_range("xiao biao yue jie");
}

template<const unsigned h, const unsigned w>
screen<h, w>& screen<h, w>::set(char c)
{
	contents[corsor] = c;
	return *this;
}

template<const unsigned h, const unsigned w>
screen<h, w>& screen<h, w>::set(pos r,pos y,char c)
{
	if(r<=h&y<w) conments[r*w+y] = c;
	return *this;
}

template<const unsigned h, const unsigned w>
screen<h,w>& screen<h,w>::operator++()
{
	corsor++;
	return *this;
}

template<const unsigned h, const unsigned w>
ostream& operator<<(ostream& os,const screen<h, w>& s)
{
	int i = 0;
	for (auto a : s.contents)
	{
		if (i == h)
		{
			cout << endl;
			i = 0;
		}
		cout << a;
		i++;
	}
	return os;
}

template<const unsigned h, const unsigned w>
istream& operator>>(istream& is, screen<h, w>& s)
{
	string temp;
	is >> temp;
	
	for (auto a : temp)
	{
		s.set(a);
		s.corsor++;
	}
	return is;
}



int main()
{
	const unsigned i = 10;
	screen<i,10> sc('&');

	cout << sc.get() << endl;
	cout << sc << endl;
	
	screen<10, 10> sc1(sc);
	screen<10, 10> sc2;
	sc2 = sc1;
	//sc2++;
	cout << sc1 << endl;
	cout << sc2 << endl;
	
	cin >> sc;
	cout << sc << endl;

	system("pause");
    return 0;
}

