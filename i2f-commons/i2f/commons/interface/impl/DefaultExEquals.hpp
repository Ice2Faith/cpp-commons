#ifndef _I2F_DEFAULT_EX_EQUALS_H_
#define _I2F_DEFAULT_EX_EQUALS_H_
#include"../IExEquals.h"

template<typename T>
class DefaultExEquals : virtual public IExEquals<T>
{
public:
	virtual ~DefaultExEquals(){}
	virtual bool equal(T t1, T t2);
};

template<typename T>
bool DefaultExEquals<T>::equal(T t1, T t2)
{
	return t1 == t2;
}

#endif // _I2F_DEFAULT_EX_EQUALS_H_