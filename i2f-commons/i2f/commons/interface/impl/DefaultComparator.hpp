#ifndef _I2F_DEFAULT_COMPARATOR_H_
#define _I2F_DEFAULT_COMPARATOR_H_

#include"../IComparator.h"
#include"../../base/Base.hpp"

template<typename T>
class DefaultComparator : virtual public IComparator<T>
{
public:
	virtual ~DefaultComparator(){}
	virtual int compare(T t1, T t2)
	{
		return t2 - t1;
	}
};



#endif // _I2F_DEFAULT_COMPARATOR_H_