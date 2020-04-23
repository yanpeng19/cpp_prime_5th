#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include<algorithm>

using namespace std;

namespace test
{
	template <class T> struct std::hash;

	class logic_e
	{
	public:
		logic_e() = delete;
		logic_e(const string&s) :error(s) {};
		string what() { return error; }

	private:
		string error;
	};

	class test_e
	{
	public:
		test_e() = delete;
		test_e(const string &s) :error(s) {};
		string what() { return error; };
	private:
		string error;
	};


	class Sales_data
	{
		friend struct hash<Sales_data>;
	private: //共有成员，外部接口
		string bookNo;
		unsigned units_sold;
		double price;
		double discount;
		double average;
		double revenue;

	public:  //私有成员，外部无法访问
		Sales_data();
		Sales_data(const string&);
		Sales_data(const string&, const unsigned&, const double&);
		friend std::istream& operator >> (istream&, Sales_data&);
		friend ostream& operator << (ostream&, const Sales_data&);
		string isbn() const;
		friend Sales_data operator + (Sales_data &, Sales_data &);
		//Sales_data& operator = (const Sales_data &);
		Sales_data& operator = (const Sales_data&);
		Sales_data& operator = (const string &);
		friend bool operator == (const Sales_data &, const Sales_data &);
		Sales_data & operator += (const Sales_data &);

		double avg_price();
		Sales_data& combine(const Sales_data &);
		friend istream & read(istream &, Sales_data &);
		friend ostream & print(ostream &, Sales_data &);
		friend Sales_data add(const Sales_data &, const Sales_data &);
	};

}