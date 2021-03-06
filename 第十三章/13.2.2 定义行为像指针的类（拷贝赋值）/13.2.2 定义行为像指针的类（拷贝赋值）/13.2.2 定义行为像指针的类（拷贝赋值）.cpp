// 13.2.2 定义行为像指针的类（拷贝赋值）.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class HasPtr
{
public:
	HasPtr(const std::string &s = std::string()) :                   //默认构造函数
		ps(new std::string(s)), i(0), use(new std::size_t(1)),ceshi("dizi") {};
	HasPtr(const HasPtr & hp):                                        //拷贝控制的初始化
		ps(hp.ps), i(hp.i), use(hp.use) {
		++*use;
	}
	HasPtr& operator =(const HasPtr & hp)
	{
		++*hp.use;
		if (--*use == 0)
		{
			delete ps;
			delete use;
		}

		ps = hp.ps;
		i = hp.i;
		use = hp.use;
		return *this;
	}
	~HasPtr()
	{
		if (--*use == 0)
		{
			delete ps;
			delete use;
			//cout << "shifang neicun " << endl;
		}
	}
	string ceshi;

private:
	std::string *ps;
	int i;
	std::size_t *use;
	
};

class TreeNode
{

public:
	TreeNode(const string &s =  string()) :
		value(new std::string(s)), count(0), /*left(new TreeNode), right(new TreeNode),*/use(new size_t(1)) {};

	TreeNode(TreeNode & tn) :
		value(tn.value), count(tn.count), left(tn.left), right(tn.right), use(tn.use)
	{
		++*use;
	}

	TreeNode& operator =(const TreeNode & tn)
	{
		++*tn.use;
		if (--*use == 0)
		{
			delete value;
		}
		value = tn.value;
		count = tn.count;
		left = tn.left;
		right = tn.right;
	}

	~TreeNode()
	{
		if (--*use == 0)
		{
			delete value;
			
		}
		cout << "xigou hanshu zhixing" << endl;

		cout << " " << endl;
	}
	

private:
	std::string *value;
	int count;
	TreeNode *left;
	TreeNode *right;
	size_t *use;
};

class BinStrTree
{
public:
	BinStrTree() = default;
	BinStrTree( TreeNode& tn) :
		root(&tn) {};
	BinStrTree(BinStrTree& bt) :
		root(bt.root) {};
	BinStrTree &operator =(BinStrTree &bt)
	{
		root = bt.root;
	}
	~BinStrTree() = default;

private:
	TreeNode *root;
};

int main()
{
	HasPtr a("1");
	cout << a.ceshi << endl;
	HasPtr b(a);
	cout << b.ceshi << endl;
	HasPtr c = a;
	cout << c.ceshi << endl;
	a = a;
	cout << a.ceshi << endl;




	system("pause");
    return 0;
}

//C++ 赋值运算符销毁左侧对象的资源 需要自己进行销毁，左侧对象不会调用析构函数
//赋值运算符的实质是 ：  将左侧对象的数据内容，根据右侧的对象的内容，进行定制修改