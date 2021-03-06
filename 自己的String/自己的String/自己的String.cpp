
// 自己的简易String.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>

using namespace std;

static allocator<char> alloc;//内存分配器

class String
{
	friend 
		bool operator==(const String&,const String&);
public:
	String() :elements(NULL), cap(NULL), first_free(NULL) {};
	String(const char*);
	String(const String&);
	String& operator=(const String &);
	String& operator+=(const String &);
	String& operator<<(const String &);
	String& operator>>(String &);
	

	String(String && s)noexcept :
		elements(s.elements), first_free(s.first_free), cap(s.cap)
	{
		s.elements = s.first_free = s.cap = NULL;
	}
	String & operator=(String&& s)noexcept
	{
		elements = s.elements;
		first_free = s.first_free;
		cap = s.cap;
		s.elements = s.first_free = s.cap = NULL;
		return *this;
	}


	~String();
	void insert(char);
	int size() { return first_free - elements; };
	int capcity() { return cap - elements; };
	bool empty() { return first_free - elements ? false : true; };

	void check_n();//查询空间是否充足
	void relo();//重新分配空间
	void free();
	void out();

	char *begin() { return elements; }
	char *end() { return first_free; }

	const char* cbegin() const{ return elements; }
	const char* cend() const { return first_free; }

private:
	char *elements;
	char *cap;
	char *first_free;
	
};

bool operator== (const String &r, const String &l)
{
	string sr(r.elements, r.first_free);
	string sl(l.elements, l.first_free);
	//cout << sr << endl;
	//cout << sl << endl;
	return sr == sl;
}

void String::out()
{
	auto temp_l = elements;
	while (temp_l != first_free)
		cout << *temp_l++;
	cout << endl;
}
void String::check_n()
{
	if (!(cap - first_free))
		relo();
}
void String::free()
{
	auto temp_fir = first_free;
	while (temp_fir != elements)
		alloc.destroy(--temp_fir);
	alloc.deallocate(elements, capcity());
}
void String::relo()
{
	int leth;
	leth = elements ? capcity() * 2 : 1;
	auto temp_elem = alloc.allocate(leth);
	uninitialized_copy(elements, first_free, temp_elem);
	auto temp_first = temp_elem + size();
	auto temp_cap = temp_elem + leth;
	free();
	elements = temp_elem;
	first_free = temp_first;
	cap = temp_cap;
}
void String::insert(char c)
{
	check_n();
	alloc.construct(first_free++, c);
}
String::String(const char *c)
{
	for (int a = 0; *(c + a) != '\0'; a++)
		insert(*(c + a));
}

String::String(const String &s)
{
	int size = s.first_free - s.elements;
	elements = alloc.allocate(size);
	cap = first_free = elements + size;
	auto temp_s = s.elements;
	auto temp_ele = elements;
	while (temp_s != s.first_free)
		*temp_ele++ = *temp_s++;
	//cout << " copy " << endl;
}
String& String::operator=(const String &s)
{
	int size = s.first_free - s.elements;
	auto new_elem = alloc.allocate(size);
	auto new_first_free = new_elem;
	auto temp_ele = s.elements;
	for (auto i = s.elements; i != s.first_free; i++)
	{
		alloc.construct(new_first_free++, *(temp_ele++));
	}
	//cout << "run '=' once" << endl;
	free();
	elements = new_elem;
	first_free = new_first_free;
	cap = new_elem + size;
	return *this;
}

String& String::operator+=(const String &s)
{
	int s_size = s.first_free - s.elements;
	int size = first_free - elements;
	if ((cap-first_free) > s_size)
	{
		uninitialized_copy(s.cap, s.first_free, first_free);
		first_free += s_size;
		return *this;
	}
	auto new_elem = alloc.allocate(size + s_size);
	auto new_cap = new_elem + (size + s_size);
	auto new_first_free = new_cap;
	uninitialized_copy(elements, first_free, new_elem);
	uninitialized_copy(s.elements, s.first_free, new_elem+size);
	free();
	elements = new_elem;
	first_free = new_first_free;
	cap = new_cap;
	return *this;
}

String& String::operator<<(const String &s)
{
	String temp(" ");
	*this += temp;
	*this += s;
	return *this;
}

String& String::operator>>(String &s)
{
	String temp(" ");
	s += temp;
	s += *this;
	return s;
}

String ::~String()
{
	free();
}

ostream& operator << (ostream& out, const String & s)
{
	for (auto i = s.cbegin(); i != s.cend(); i++)
		cout << *i;
	return out;
}

int main()
{
	String s("dddddd");
	String s1("1231231231 !");
	cout << s << endl;
	cout << s1 << endl;

	system("pause");
	return 0;

}

