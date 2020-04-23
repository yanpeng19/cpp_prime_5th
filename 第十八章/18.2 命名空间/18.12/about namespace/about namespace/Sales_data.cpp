#include "stdafx.h"
#include "Sales_data.h"
using namespace std;

using namespace test;

	Sales_data::Sales_data() try :price(0)
	{
		bookNo = "NUll";
		units_sold = 0;
		if (price != 0)
			throw logic_e("¥ÌŒÛ≤‚ ‘");
	}
	catch (logic_e &l)
	{
		cerr << l.what() << endl;
		system("pause");
		throw;
	};

	Sales_data::Sales_data(const string& s)
	{
		bookNo = s;
		units_sold = 0;
		price = 0.0;
	}

	Sales_data::Sales_data(const string&s, const unsigned& u, const double& p) :
		bookNo(s), units_sold(u), price(p) {};

	istream& test::operator >> (istream &is, Sales_data &item)
	{
		is >> item.bookNo >> item.units_sold >> item.price;
		return is;
	}

	ostream& test::operator <<(ostream &os, const Sales_data &item)
	{
		os << item.isbn() << " " << item.units_sold << " " << item.price;
		return os;
	}
	string Sales_data::isbn()const
	{
		return bookNo;
	}
	Sales_data operator + (Sales_data & lhs, Sales_data & rhs)
	{
		try {
			if (lhs.isbn() != rhs.isbn())
				throw runtime_error("isbn is not same");
		}
		catch (runtime_error&r)
		{
			cout << r.what() << endl;
			system("pause");
			exit(-1);
		}

	}


	bool test::operator == (const Sales_data &lhs, const Sales_data &rhs)
	{
		return lhs.units_sold == rhs.units_sold&&lhs.price == rhs.price&&lhs.isbn() == rhs.isbn();
	}
	Sales_data& Sales_data::operator=(const Sales_data &lhs)
	{
		bookNo = lhs.bookNo;
		units_sold = lhs.units_sold;
		price = lhs.price;
		return *this;
	}
	Sales_data& test::Sales_data::operator+=(const Sales_data &rhs)
	{
		units_sold += rhs.units_sold;
		revenue += rhs.revenue;
		return *this;
	}
	Sales_data& test::Sales_data::operator=(const string & s)
	{
		bookNo = s;
		return *this;
	}
	double Sales_data::avg_price()
	{
		average = revenue / units_sold;
		return average;
	}
	Sales_data& Sales_data::combine(const Sales_data &rhs)
	{
		units_sold += rhs.units_sold;
		revenue += rhs.revenue;
		return *this;
	}
	istream & test::read(istream & is, Sales_data &rhs)
	{
		is >> rhs.bookNo >> rhs.units_sold >> rhs.price;
		rhs.revenue = rhs.units_sold*rhs.price;
		return is;
	}
	Sales_data test::add(const Sales_data &lhs, const Sales_data &rhs)
	{
		Sales_data sum = lhs;
		sum.combine(rhs);
		sum.avg_price();
		return sum;
	}

	template <>
	struct hash<Sales_data>
	{

		typedef size_t resault_type;
		typedef Sales_data argument_type;
		size_t operator()(const Sales_data&)const;
	};

	size_t hash<Sales_data>::operator()(const Sales_data& s) const
	{
		return hash<string>()(s.bookNo) ^
			hash<unsigned>()(s.units_sold) ^
			hash<double>()(s.price);
	}

	bool compare_isbn(const Sales_data &r, const Sales_data &l)
	{
		return r.isbn() < l.isbn();
	}
