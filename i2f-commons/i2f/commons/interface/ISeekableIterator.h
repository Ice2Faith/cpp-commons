#ifndef _I2F_ISEEKABLE_ITERATOR_H_
#define _I2F_ISEEKABLE_ITERATOR_H_

#include"IIterator.h"

template<typename T>
class ISeekableIterator : virtual IIterator<T>
{
public:
	virtual ~ISeekableIterator(){}
	virtual void seek(int index) = 0;
};

#endif // _I2F_ISEEKABLE_ITERATOR_H_