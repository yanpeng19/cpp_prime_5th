// oop_test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>


using namespace std;

class Quote
{
public:
	Quote() = default;
	Quote(const string &book, double sales_price) :
		bookNo(book), price(sales_price) 
	{
		//cout << "QUOTE:直接初始化" << endl;
	};
	string isbn() const { return bookNo; };

	Quote(const Quote &q) :
		bookNo(q.bookNo), price(q.price) {
		//cout << "Quote：拷贝初始化" << endl;	
	};


	Quote(Quote &&q) :
		bookNo(std::move(q.bookNo)), price(std::move(q.price))
	{
		//cout << "QUOTE：移动拷贝" << endl;
	}



	Quote operator=(const Quote &q)
	{
		bookNo = q.bookNo;
		price = q.price*100;
		//cout << "QUOTE:赋值运算符赋值" << endl;
		return *this;
	}

	Quote operator=(Quote &&q)
	{
		bookNo = std::move(q.bookNo);
		price = std::move(q.price);
		//cout << "Quote：移动赋值" << endl;
		return *this;
	}

	virtual double net_price(std::size_t n) const
	{
		return n * price;
	}

	virtual void debug() const
	{
		cout << " ISBN = " << bookNo << " ;" << endl;
		cout << " price = " << price << " ." << endl;
	}
	virtual ~Quote()
	{
		bookNo = "";
		price = 0;
		//cout << "执行Queto 默认析构函数" << endl;
	}

	virtual shared_ptr<Quote> get_p()
	{
		auto a = new shared_ptr<Quote>(this);
		return *a;
	}

	std::string bookNo;
	double price = 0.0;
};

class Disc_quote:public Quote
{
public:
	Disc_quote() = default;
	Disc_quote(const string book, double price, size_t n, double dis) :
		Quote(book, price), quantity(n), discount(dis) {};

	double net_price(size_t n) const = 0;

protected:
	size_t quantity = 0;
	double discount = 0;
};

class Bulk_Quote : public Quote
{
public:
	
	Bulk_Quote() = default;
	
	Bulk_Quote(const string & s, double p,size_t min,double dis) :
		Quote(s, p),min_qty(min),discont(dis) {	};

	Bulk_Quote(const Bulk_Quote &rhs) :
		Quote(rhs),min_qty(rhs.min_qty),discont(rhs.discont){};

	Bulk_Quote(Bulk_Quote &&rhs) :Quote(std::move(rhs)), 
		min_qty(std::move(rhs.min_qty)), discont(std::move(rhs.discont)) {};
	
	Bulk_Quote operator=(const Bulk_Quote &rhs)
	{
		Quote::operator=(rhs);
		min_qty = rhs.min_qty;
		discont = rhs.discont;
		return *this;
	}

	Bulk_Quote operator=(Bulk_Quote &&rhs)
	{
		Quote(std::move(rhs));
		min_qty = std::move(rhs.min_qty);
		discont = std::move(rhs.discont);
		return *this;
	}
    
	virtual double net_price(std::size_t n) const override;

	virtual shared_ptr<Quote> get_p()
	{
		auto p = new shared_ptr<Bulk_Quote>(this);
		return *p;
	}

private:
	size_t min_qty = 0;
	double discont = 0.0;

};


double Bulk_Quote::net_price(std::size_t n) const
{
	if (n >= min_qty)
		return n * (1 - discont) * price;
	else
		return n * price;
}

double print_total(ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN " << item.isbn() << " # sold: " << n << " totla due: " << ret << endl;
	return ret;
}

void DEBUG(const Quote &item)
{
	item.debug();
	return;
}

class Basket
{
public:
	Basket()=default;
	static bool compare(const shared_ptr<Quote> q1, const shared_ptr<Quote> q2)
	{return q1->bookNo < q2->bookNo;}

	void print_total(ostream &); //输出所有
	double print_item(ostream &,shared_ptr<Quote>,size_t);                                   //输出当下
	void insert(shared_ptr<Quote>);
	void insert(Quote&);

private:
	multiset<shared_ptr<Quote>, decltype(compare)*> items{ compare };  // 此处存疑，有待修改
};

void Basket::insert(shared_ptr<Quote> pq)
{
	items.insert(pq);
}

void Basket::insert(Quote &q)
{
	auto a = q.get_p();
	items.insert(a);
}



void Basket::print_total(ostream &os)
{
	os << "         TOTLE         " << endl;
	double sum = 0;
	//for (auto item : Basket::items)                    逐个遍历
	//{
	//	sum += print_item(os,item,items.count(item));
	//}

	for (multiset<shared_ptr<Quote>>::iterator item = items.cbegin();
		item != items.cend();
		item = items.upper_bound(*item))
	{
		sum += print_item(os, *item, items.count(*item));
	}
	cout << endl;
	cout << "the sum is : " << sum << endl;
}

double Basket::print_item(ostream &os,shared_ptr<Quote> item,size_t n)
{
	double num = item->net_price(n);
	cout << item->bookNo << " " << (*item).price << " " << num << endl;
	return num;
}


int main()
{
	Basket bk;
	Quote q1("001", 50);
	Quote q2("002", 30);
	Quote q3("003", 25);
	Bulk_Quote bq1("101", 60, 1, 0.2);
	Bulk_Quote bq2("102", 10, 1, 0.15);
	Bulk_Quote bq3("103", 100, 5, 0.6);


	bk.insert(q1);
	bk.insert(make_shared<Quote>(q2));
	bk.insert(make_shared<Quote>(q3));
	bk.insert(bq1);
	bk.insert(bq2);
	bk.insert(bq3);
	bk.insert(bq3);
	bk.insert(bq3);
	bk.insert(bq3);
	bk.insert(bq3);
	bk.insert(bq3);
	bk.insert(bq3);
	bk.insert(bq3);
	

	bk.insert(bq3);

	bk.print_total(cout);


	system("pause");
	return 0;
}