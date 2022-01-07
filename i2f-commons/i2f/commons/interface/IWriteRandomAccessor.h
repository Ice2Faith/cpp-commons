#ifndef _I2F_IWRITE_RANDOM_ACCESSOR_H_
#define _I2F_IWRITE_RANDOM_ACCESSOR_H_
#include"Sizeable.h"

template<typename T>
class IWriteRandomAccessor : virtual Sizeable
{
public:
	virtual ~IWriteRandomAccessor(){}
	virtual void set(int index, const T& val) = 0;
};

#endif // _I2F_IWRITE_RANDOM_ACCESSOR_H_