// main.cpp: 定义控制台应用程序的入口点。
//

/*仿制vector 模板

  0.存储方式: shared_ptr<T> 底层进行存储
  {
	T *elements   //内存开头
	T *first_free //第一个可以用内存位置
	T *cap        //尾后指针
  }
  1.构造函数以及析构函数
  {
    Vec()
	Vec(intializerd_list<T>);
	Vec(const Vec&)
	Vec(const Vec&&)
	Vec::operator=();
	~Vec();
  }
  2.动态内存分配-通过 alloctor<T> 进行分配和构造
  {
    2.0 free()     //释放现空间 析构和扩充时使用
	2.1 check()    //检查现阶段 内存是否够用 如果没有就进行重新分配 分配大小为size() * 2
	2.2 relocate() //分配空间函数 并拷贝原来内容到现位置
	2.3 pair<T*,T*> allc_n_copy() //拷贝工具函数 分配空间后帮助把旧空间内容拷贝至新空间

	#alloctor操作：  
		0.alloctor.allocate(n)        //分配n个空间（但不初始化）
		1.alloctor.deallocate(p，n)   //释放p指向的n个空间，！p必须是创建时的大小  ！每个元素都需要单独析构 alloctor.destory

		2.alloctor.construct(p,args)  //p指向的位置，使用args的值构造一个对象
		3.alloctor.destory(p)         //p指向的对象执行其本身的析构函数（析构P指向的对象）
  }

  3.功能：
	 3.1.push_back()
	 3.2 pop_back()
	 3.3 empty()
	 3.4 size()
	 3.5 capcity()   // 可用空间
	 3.6 front()
	 3.7 back()
	 3.8 begin()
	 3.9 end()
	 3.10 resize(size_t n)  // 分配n大小的空间，如果容器现阶段大于n，则删除n之后内容。
	                                            如果容器现阶段小于n，则分配空间，满足capcit()>n;
	 3.11 resize(size_t n,T) //同上，但如果有新分配空间，用T来填充

  4.需要重载运算符
	 4.1 Vec<T>::operator[]();

  5.构造及使用逻辑流程
     5.1 构造 ：  申请空间 - 检查大小 - 初始化内容 - 3指针赋值
	 5.2 插入：   检查大小 - 构造内存 - 调整first_free 及 cap
	 5.3 删除：   删除first_free-1,且first_free--;
	 5.4 检查：   如果空间大小为0（capcity()==0),再申请capcity()的空间，并且继续循环检查，直到空间足够
	 5.5 分配新内存： 如果检查大小不够，  申请新空间，其大小为 1或者capcity()*2,将类本身的指针指向新空间，
	                  并且析构原空间


*/

#include "stdafx.h"
#include <string>  
#include <memory>  
#include <utility>   
#include <initializer_list>  
#include <algorithm>  
#include <iostream>

using namespace std;

template<typename T> 
class vec
{
	using fuck = T * ;
	static allocator<T> alloc;

public:
	vec() :element(NULL), first_free(NULL), cap(NULL) {};
	vec(const vec&v) :element(NULL), first_free(NULL), cap(NULL) 
	{
		int i = v.size();
		element = alloc.allocate(i);
		first_free = element;
		cap = element + i + 1;
		auto temp = v.element;
		while (temp != v.first_free)
		{
			alloc.construct(first_free++, *temp++);
		}

	};
	vec(initializer_list<T>);
	vec(const vec&&v);
	vec<T> operator=(const vec<T>&);
	T operator[](unsigned i);
	~vec() { free(); };

	//以下为功能函数
	void push_back(T);
	void pop_back();
	bool empty()const { return size() ? 1 : 0; };
	unsigned size()const{ return first_free - element; };
	unsigned capcity() { return cap - element; };
	void check();
	void free();
	void relocate();

	T& front(); 
	T& back();
	T* begin() const { return element; };
	T* end() const { return cap; };

private:
	T* element;
	T* first_free;
	T* cap;
};

template<typename T> 
allocator<T> vec<T>::alloc;

template<typename T>
vec<T>::vec(initializer_list<T> li) :element(NULL),first_free(NULL),cap(NULL)
{
	while (capcity() < li.size())
		relocate();
	for (auto a : li)
		alloc.construct(first_free++,a);
}

template<typename T>
vec<T>::vec(const vec<T>&& vc) : element(vc.element), first_free(vc.first_free), cap(vc.cap)
{
	vc.element = NULL;
	vc.first_free = NULL;
	vc.cap = NULL;
}

template<typename T> 
vec<T> vec<T>::operator=(const vec<T>&vc)
{
	free();
	element = alloc.allocate(vc.size());
	first_free = element;
	cap = element + vc.size()+1;
	for (auto a : vc)
		alloc.construct(first_free++, a);
	return *this;
}

template<typename T>
T vec<T>::operator[](unsigned i)
{
	return *(element + i);
}

template<typename T> 
void vec<T>::check()
{
	if (size() == capcity())
		relocate();
}

template<typename T>
void vec<T>::free()
{
	if (element)
	{
		for (auto a = element; a != first_free; a++)
			alloc.destroy(a);
		alloc.deallocate(element, capcity());
	}
}

template<typename T> 
void vec<T>::relocate()
{
	auto n = capcity() ? capcity() * 2 : 1;

	T* temp_element = alloc.allocate(n);
	T* temp_cap = temp_element + n;
	T* temp_first_free = temp_element;

	cout << (temp_first_free - temp_element) << endl;

	for (auto i = element; i != first_free; i++)
	{
		alloc.construct(temp_first_free, *i);
		temp_first_free++;
	}

	free();
	element = temp_element;
	first_free = temp_first_free;
	cap = temp_cap;
}

template<typename T>
void vec<T>::push_back(T t)
{
	check();
	alloc.construct(first_free++, t);
}

template<typename T>
void vec<T>::pop_back()
{
	check();
	alloc.destory(--first_free);
}

template<typename T>
T& vec<T>::front()
{
	check();
	return *element;
}

template<typename T>
T& vec<T>::back()
{
	check();
	return *(--first_free);
}


int main()
{
	vec<string> vc, vc2;
	vc.push_back("baobao");
	vc.push_back("xiaodizi");

	vec<string> vc1(vc);
	vc2 = vc;

	cout << vc1[1] << endl;

	for (auto a : vc)
		cout << a << endl;
	system("pause");
    return 0;
}