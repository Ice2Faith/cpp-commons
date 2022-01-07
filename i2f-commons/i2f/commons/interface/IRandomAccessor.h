#ifndef _I2F_IRANDOM_ACCESSOR_H_
#define _I2F_IRANDOM_ACCESSOR_H_
#include"IReadRandomAccessor.h"
#include"IWriteRandomAccessor.h"


template<typename T>
class IRandomAccessor : virtual public IReadRandomAccessor<T>, virtual public IWriteRandomAccessor<T>
{
public:
	virtual ~IRandomAccessor(){}
};

#endif // _I2F_IRANDOM_ACCESSOR_H_