#ifndef _I2F_IDOUBLE_DIRECTION_ITERATOR_H_
#define _I2F_IDOUBLE_DIRECTION_ITERATOR_H_
#include"IIterator.h"
#include"IReverseIterator.h"

template<typename T>
class IDoubleDirectionIterator : virtual public IIterator<T>, virtual public IReverseIterator<T>
{
public:
	virtual ~IDoubleDirectionIterator(){}
	virtual void toBegin() = 0;
	virtual void toEnd() = 0;
};

#endif // _I2F_IDOUBLE_DIRECTION_ITERATOR_H_