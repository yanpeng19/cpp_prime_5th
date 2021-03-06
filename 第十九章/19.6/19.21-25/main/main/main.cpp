// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "Sales_data.h"

using namespace std;


class Token
{
public:
	Token() :tok(INT), ival(0) {};
	Token(const Token &t) :tok(t.tok) { copyUnion(t); };
	Token(const Token &&t) :tok(t.tok)
	{
		move_copyUnion(std::move(t));
	}

	Token& operator=(const Token &t)
	{
		if (this == &t)
			return *this;
		if (tok == STR&&t.tok!=STR)
			sval.~string();
		else if (tok == SALES&&t.tok!=SALES)
			sale_val.~Sales_data();
		tok = t.tok;
		copyUnion(t);
		return *this;
	}

	Token& operator=(const Token &&t)
	{
		if (this == &t)
			return *this;
		if (tok == STR && t.tok != STR)
			sval.~string();
		else if (tok == SALES && t.tok != SALES)
			sale_val.~Sales_data();
		tok = t.tok;
		move_copyUnion(std::move(t));
		return *this;
	}


	Token& operator=(const int&i) { tok = INT; ival = i; return *this; };
	Token& operator=(const char&c) { tok = CHAR; cval = c; return *this; };
	Token& operator=(const double& d) { tok = DBL; dval = d; return *this;}
	Token& operator=(const string& s)
	{
		if(tok==STR)
		sval = s; 
		else
		{
			tok = STR;
			new(&sval) string(s);
		}
		return *this;
	}
	Token& operator=(const Sales_data&s)
	{
		if (tok == SALES)
			sale_val = s;
		else
		{
			tok == SALES;
			new(&sale_val) Sales_data(s);
		}
		return *this;
	}

	Token(const int &i) :tok(INT), ival(i) {};
	Token(const char &c) :tok(CHAR), cval(c) {};
	Token(const double &d) :tok(DBL), dval(d) {};
	Token(const string &s) :tok(STR), sval(s) {};
	Token(const Sales_data &s) :tok(SALES), sale_val(s) {};

	void print()
	{
		switch (tok)
		{
		case Token::INT: cout << ival << endl; break;
		case Token::CHAR: cout << cval << endl; break;
		case Token::DBL: cout << dval << endl; break;
		case Token::STR: cout << sval << endl; break;
		case Token::SALES:cout << sale_val << endl; break;
		}
	}

	~Token()
	{
		if (tok==STR)
			sval.~string();
	}
	
private:
	enum { INT, CHAR, DBL, STR,SALES } tok;
	union
	{
		char cval;
		int ival;
		double dval;
		std::string sval;
		Sales_data sale_val;
	};
	void copyUnion(const Token&);
	void move_copyUnion(const Token&&);
};

void Token::copyUnion(const Token&t)
{
	switch (t.tok)
	{
	case Token::INT: ival = t.ival; break;
	case Token::CHAR: cval = t.cval; break;
	case Token::DBL: dval = t.dval; break;
	case Token::STR: new(&sval) string(t.sval);break;
	case Token::SALES: new(&sale_val) Sales_data(t.sale_val); break;
	}
}

void Token::move_copyUnion(const Token&&t)
{
	switch (t.tok)
	{
	case Token::INT: ival = std::move(t.ival); break;
	case Token::CHAR: cval = std::move(t.cval); break;
	case Token::DBL: dval = std::move(t.dval); break;
	case Token::STR: new(&sval) string(std::move(t.sval)); break;
	case Token::SALES: new(&sale_val) Sales_data(std::move(t.sale_val)); break;
	}
}

int main()
{
	
	Token a("dizibaobao");
	Token b(Sales_data("110", 2, 30));
	a.print();
	b.print();

	Token c = std::move(a);
	c.print();

	
	system("pause");
    return 0;
}

