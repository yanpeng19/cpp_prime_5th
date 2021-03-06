// 13.4 拷贝控制 Message 和 Folder.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

class Folder
{
	friend class Message;
	friend void swap(Folder &, Folder &);
public:
	Folder() = default;
	Folder(const Folder &);
	Folder & operator=(const Folder &);
	~Folder();

	
	void addMsg(Message &);
	void remMsg(Message &);
	void outMes();
private:
	//string name = "undefine";
	set<Message*> Messages;
	void remove_from_Msg();
	void add_to_Msg();
};

class Message
{
	friend class Folder;
	friend void swap(Message &, Message &);
	friend void swap(Folder &, Folder &);
public:
	Message(const std::string &s) :
		content(s) {};
	/*Message(const std::string &s) :
	content(s) {};*/
	Message(const Message &);
	Message & operator=(const Message &);
	~Message();

	void save(Folder &);
	void remove(Folder &);
	void addFolder(Folder &);
	void mesFolder(Folder &);
	void out()
	{
		cout << content << endl;
	}

private:
	string content;
	set<Folder*> folders;

	void add_to_folders(const Message&);
	void remove_from_folders();
};

void Message::addFolder(Folder &f)
{
	folders.insert(&f);
}

void Message::mesFolder(Folder &f)
{
	folders.erase(&f);
}

void Folder::outMes()
{
	for (auto a : Messages)
	{
		a->out();
	}
}
Folder::Folder(const Folder &f) :
	Messages(f.Messages)
{
	add_to_Msg();
}

void Folder::add_to_Msg()
{
	for (auto a : Messages)
	{
		a->save(*this);
	}
}

void Folder::remove_from_Msg()
{
	for (auto a : Messages)
	{
		a->folders.erase(this);
	}
}

Folder & Folder::operator=(const Folder & f)
{
	remove_from_Msg();
	Messages = f.Messages;
	add_to_Msg();
	return *this;
}

Folder::~Folder()
{
	remove_from_Msg();
	cout << "Folder is delete" << endl;
}

void Folder::addMsg(Message &ms)
{
	Messages.insert(&ms);
	//ms.folders.insert(this);
}

void Folder::remMsg(Message &ms)
{
	Messages.erase(&ms);
	//ms.folders.erase(this);
}

void swap(Folder & lhs, Folder &rhs)
{
	for (auto a : lhs.Messages)
	{
		a->folders.erase(&lhs);
	}
	for (auto a : rhs.Messages)
	{
		a->folders.erase(&rhs);
	}
	swap(lhs.Messages, rhs.Messages);
	for (auto a : lhs.Messages)
	{
		a->folders.insert(&lhs);
	}
	for (auto a : rhs.Messages)
	{
		a->folders.insert(&rhs);
	}
}


Message::Message(const Message &ms) :
	content(ms.content), folders(ms.folders)
{//////!!!!!!!!!!!!!!!!!!!!!!!!! 这里书本为ms，感觉逻辑不通，待定         //经测试两个都可以，传递&ms 感觉是为了安全考虑，因为ms.folders 是已经确认的列表
	//add_to_folders(*this);
	add_to_folders(ms);
}

void Message::add_to_folders(const Message& ms)     //此参数也可以改成 无参数类型，folders已经被ms.folders初始化，可以通过遍历folders 进行addMsg
{
	for (auto f : folders)
	{
		f->addMsg(*this);
	}
}
//void Message::add_to_folders()   
//{
//	for (auto f : folders)
//	{
//		f->addMsg(*this);
//	}
//}

void Message::remove_from_folders()
{
	for (auto f : folders)
	{
		f->remMsg(*this);
	}
}

Message & Message::operator=(const Message &ms)
{
	remove_from_folders();
	content = ms.content;
	folders = ms.folders;
	//////////////!!!!!!!!!!!!!!!!!!!!!!!注意，书本中 为add_to_folders(ms),暂未 测试
	add_to_folders(*this);
	return *this;
}

Message::~Message()
{
	remove_from_folders();
	cout << "Message is delete" << endl;
}

void swap(Message &lhs, Message &rhs)
{
	using std::swap;
	//仅从列表中删除指针
	for(auto f : lhs.folders)
	{
		f->remMsg(lhs);
	}
	for (auto f : rhs.folders)
	{
		f->remMsg(rhs);
	}
	swap(lhs.folders, rhs.folders);
	for (auto f : lhs.folders)
	{
		f->addMsg(lhs);
	}
	for (auto f : rhs.folders)
	{
		f->addMsg(rhs);
	}
}

void Message::save(Folder&f)
{
	folders.insert(&f);
	f.addMsg(*this);
}

void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(*this);
}

int main()
{
	Folder all;
	Folder pangzi;
	Folder dizi;
	Message a("dizibaobao: from pagnzi");
	Message b("pangzi : from pangzi");
	Message c("xiang dizi: from pangzi ");
	Message d("didaren yexiang pangzi from dizi");
	Message e("kuai guolai lai yifa from dizi");
	swap(a, b);
	


	a.out();
	b.out();
	c.out();
	d.out();
	e.out();
	cout << "Message test over" << endl;
	cout << endl;

	cout << "Folder test begin" << endl;
	cout << endl;

	

	a.save(all);
	a.save(pangzi);
	b.save(all);
	b.save(pangzi);
	c.save(all);
	c.save(pangzi);
	d.save(all);
	d.save(dizi);
	e.save(all);
	e.save(dizi);

	a = a;

	cout << "F:all :" << endl;
	all.outMes();
	cout << endl;
	
	cout << "F:pangzi :" << endl;
	pangzi.outMes();
	cout << endl;

	cout << "F:dizi :" << endl;
	dizi.outMes();
	cout << endl;

	system("pause");

    return 0;
}

