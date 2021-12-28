#ifndef _I2F_DEV_H_
#define _I2F_DEV_H_
/*
本章节无任何作用，
仅用作在C++中进行开发时常见错误的规避和指引
这里仅仅表达了极少的基本内容，具体的使用，可以参考i2f/base/String.hpp的实现
*/

/*
针对c++头文件的规范
一定要使用宏定义判定包含整个头文件，保证就算头文件被多次include也不会导致重复定义的问题
正确示范：
#ifndef _I2F_DEV_H_
#define _I2F_DEV_H_

#endif // _I2F_DEV_H_

普通的.h头文件中，只存放类声明、函数声明，具体实现放在.cpp中
但是如果是模板类或者模板方法，建议直接放在头文件中，并且头文件后缀为.hpp
*/


/*
模板类在类声明上限制模板
错误点1：在类名后面用模板
class Dev<T>{};
错误点2：虽然正确使用了模板关键字template,但是还是再类名后面用模板
template<typename T>
class Dev<T>{};
正确1：
template<typename T>
class Dev{};
同时，不管是模板方法还是模板类，模板类型可以不止一个
例如：
template<typename T,typename E>
T add(T v1,E v2);
*/
template<typename T>
class Dev
{
public:
	//建议析构函数一定是一个虚析构函数，这样保证在多态时能够正确释放内存
	virtual ~Dev();
	//对于允许子类进行重写的方法，一般使用虚函数
	virtual T* data();
	//也可以定义纯虚函数，包含纯虚函数的类为抽象类，不可实例化
	virtual int size() = 0;
	//这是一个模板方法的类外实现
	virtual Dev<T>& add(int num,const Dev<T>& p);

};

/*
模板方法的类外实现
需要注意的点：
模板方法，需要指定模板类型
template<typename T>
使用到的模板对象，需要带模板类型
Dev<T>&
模板类限定名需要带模板类型
Dev<T>::
*/
template<typename T>
Dev<T>& Dev<T>::add(int num, const Dev<T>& p)
{
	return *this;
}

/*
类声明可以提前
这样可以在多个类相互使用的时候保证编译的顺利进行
如果是模板类，需要带上末班申明
例如：
template<typename T>
class DevImpl;
*/
class DevImpl;

/*
这一个函数，作为下面的一个友元函数，与普通函数一样，
并且不用带类限定符号::,也不用带friend关键字
*/
DevImpl operator+(int num, const DevImpl& dev)
{
	DevImpl ret;
	ret.m_size = num + dev.m_size;
	return ret;
}

/*
c++的继承是多继承
需要注意：
继承方式包含公有继承、保护继承、私有继承
示例分别为：
class DevImpl : public Dev<int>{};
class DevImpl : protected Dev<int>{};
class DevImpl : private Dev<int>{};
并且还有虚继承
此类情况是针对，在多继承中，可能会出现重名的函数或者变量
使用虚继承之后，这些重名的函数或者声明，都将合并为一个（可以这么理解）
例如：A->B A->C B,C->D 这时候，D如果不使用虚继承，那么在D中，将会有两份来自A的副本
虚继承的使用，也就是在继承时加上virtual关键字
示例：
class DevImpl : virtual public Dev<int>{};
关于模板的继承
如果父类是模板，子类可以选择指明模板类型，从而子类不再是模板
子类也可以继续是模板类
示例：
子类直接指明类型，子类不是模板
class DevImpl : virtual public Dev<int>{};
子类也是模板：
template<typename T>
class DevImpl : virtual public Dev<T>{};
多继承示例：
class IronMan : virtual public Man , virtual public Machine{};
多继承时模板：
template<typename T,typename E>
class IronMan : virtual public Man<T> ,virtual public Animal<T> , virtial public Machine<E>{};
*/
class DevImpl : virtual public Dev<int>
{
private:
	//使用 m_ 开头定义类内部变量，由于在c++中不允许变量名和函数名同名
	int * m_data;
	int m_size;
	//静态变量需要在类外初始化
	static int max_size;
public:
	DevImpl()
	{
		this->m_size = 0;
		this->m_data = 0;
	}
	DevImpl(int size)
	{
		this->m_size = size;
		//在c++中，用new出来的使用delete释放，用new[]出来的用delete[]释放
		//这个是需要对应上的
		this->m_data = new int[size];
	}
	//普通拷贝构造
	DevImpl(const DevImpl& dev)
	{
		//普通拷贝构造，表示传进来的dev变量在构建完本对象之后，还会在其他地方使用
		//因此，需要做的就是克隆出一个dev的对象，不能修改dev
		//如下场景中会发生：
		//DevImpl p1;
		//DevImpl p2(p1);
		//复制常规变量
		this->m_size = dev.m_size;
		//开辟新内存作为副本
		this->m_data = new int[dev.m_size];
		//拷贝内容
		for (int i = 0; i < dev.m_size; i++){
			this->m_data[i] = dev.m_data[i];
		}
	}
	//移动拷贝构造
	DevImpl(DevImpl&& dev)
	{
		//移动构造的含义，表示传入的dev变量，在构造完毕本对象之后，就会释放掉
		//所以，函数的声明入参是&&，并且不带const
		//因此，需要做的就是把dev中的内存直接抢过来，让dev无内存可用
		//这样就避免了再申请内存，拷贝副本的开销
		//如下场景会发生：
		//DevImpl get(){return DevImpl();}
		//DevImpl p=get();
		//普通变量依旧还是复制
		this->m_size = dev.m_size;
		//内存直接抢过来
		this->m_data = dev.m_data;
		//为了保证dev变量释放能够正常进行，需要把dev掏空
		dev.m_size = 0;
		dev.m_data = 0;
	}
	//普通赋值
	DevImpl& operator=(const DevImpl& dev)
	{
		//类似普通构造，区别是这是赋值，因此本对象可能之前已经有内存了，需要释放
		//复制常规变量
		this->m_size = dev.m_size;
		//释放之前可能已经申请的内存
		if (this->m_data != 0){
			delete[] this->m_data;
		}
		//开辟新内存作为副本
		this->m_data = new int[dev.m_size];
		//拷贝内容
		for (int i = 0; i < dev.m_size; i++){
			this->m_data[i] = dev.m_data[i];
		}

	}
	//移动赋值
	DevImpl& operator=(DevImpl&& dev)
	{
		//类似移动构造，也是需要释放之前的内存
		//普通变量依旧还是复制
		this->m_size = dev.m_size;
		//释放之前可能已经申请的内存
		if (this->m_data != 0){
			delete[] this->m_data;
		}
		//内存直接抢过来
		this->m_data = dev.m_data;
		//为了保证dev变量释放能够正常进行，需要把dev掏空
		dev.m_size = 0;
		dev.m_data = 0;
	}
	//特殊的自增运算符，前置
	DevImpl& operator++()
	{
		//不带参数，表示前置，也就是： ++DevImpl;
		//自增运算，也就表示自身的值会受到影响
		//前置自增时，先对对象本身自增，返回对象本身
		this->m_size++;
		return *this;
	}
	//特殊的自增运算符，后置
	DevImpl operator++(int)
	{
		//带参数，表示后置，也就是： DevImpl++;
		//同样会影响自身，注意返回值类型和前置不同
		//后置自增时，先返回对象的副本，再对对象本身自增
		DevImpl ret = *this;
		this->m_size++;
		return ret;
	}
	//加法运算
	DevImpl operator+(int num)
	{
		//这种加法表示这种情景，本类型对象 + 其他类型的变量
		//因此从语义上来说，应该结果是一个新的对象，而不是参数加法的本类型对象发生改变
		//因此返回值是一个新的对象
		//同时，入参也可以是本类型的对象
		//本示例对应: DevImpl + int
		DevImpl ret;
		ret.m_size += num;
		return ret;
	}
	//自加运算
	DevImpl& operator+=(const DevImpl& dev)
	{
		//这种加法，表示的是本类型对象自身加上一个对象
		//因此语义上来说，本对象自身是发生改变的，返回的也应该是本对象
		this->m_size += dev.m_size;
		return *this;
	}
	//友元加法运算,在之前前置实现了，注意看
	friend DevImpl operator+(int num, const DevImpl& dev);
	//隐士类型转换
	operator int(){
		//这种表示本类对象可以隐式转换为起来类型
		//这个示例就表示可以隐式转换为int,因此你可以像使用int一样使用本类对象
		//例如这些都是合法的：int p=DevImpl; p+=DevImpl; 1+DevImpl+1;
		return this->m_size;
	}
	virtual ~DevImpl()
	{
		//析构函数，需要做判定是否已经释放
		//也就是说，可能在移动的时候，已经被掏空了
		if (this->m_data != 0){
			delete[] this->m_data;
		}
		this->m_data = 0;
		this->m_size = 0;
	}
	//实现类已经指明了父模板的类型，因此类型也需要做出调整
	//可以在类内部直接实现函数，成为内联实现
	virtual int* data()
	{
		return this->m_data;
	}
	//对于父类中的纯虚函数，需要在子类中重新声明一遍，并且实现，否则继承之后，依旧认为是纯虚函数
	//不声明实现，则此类还是抽象类，不可实例化
	virtual int size();
};

//在类外初始化静态变量
int DevImpl::max_size = 100;

//在类外实现函数
int DevImpl::size()
{
	return this->m_size;
}


/*
说到这里，顺便提一下，如果你要使用多态
一定使用引用类型或者使用指针
如果在引用类型可行的情况下，可以用引用类型，否则请使用指针
在某些场景下，使用引用类型可能导致虚函数表无法正确识别，导致运行或者编译失败

Dev<int>& p=DevImpl;
Dev<int>* p=new DevImpl;

针对c++中的运算符重载，我给出的建议是
如果你能正确的理解操作符对应的语义，那么你可以重载运算符
如果不能正确理解，则不建议这么做，否则可能导致你意料之外的结果

关于运算符重载的，可以参考基本数据类型的包装类i2f/commons/base/Base.hpp
*/


#endif // _I2F_DEV_H_

