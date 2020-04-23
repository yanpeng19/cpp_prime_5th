#pragma once

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

class Screen
{
public:
	typedef std::string::size_type pos;

	static const pos Screen::*get_cur() { return &Screen::cursor; }

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

inline Screen& Screen::set(pos r, pos w, char c)
{
	content[r*width + w] = c;
	return *this;
}
