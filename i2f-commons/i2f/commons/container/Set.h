#ifndef _I2F_SET_H_
#define _I2F_SET_H_

#include"../interface/IIterator.h"


template<typename T>
class  Set 
{
public:
	virtual ~Set(){};

	virtual void put(const T& val) = 0;
	virtual bool contains(const T& val) = 0;
	virtual IIterator<T>* iterator() = 0;
};

#endif // _I2F_SET_H_
