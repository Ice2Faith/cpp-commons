#ifndef _I2F_IREAD_RANDOM_ACCESSOR_H_
#define _I2F_IREAD_RANDOM_ACCESSOR_H_
#include"Sizeable.h"

template<typename T>
class IReadRandomAccessor : virtual Sizeable
{
public:
	virtual ~IReadRandomAccessor(){}
	virtual T& get(int index) = 0;
};

#endif // _I2F_IREAD_RANDOM_ACCESSOR_H_