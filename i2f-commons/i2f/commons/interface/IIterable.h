#ifndef _I2F_IITERABLE_H_
#define _I2F_IITERABLE_H_
#include"IExecutor.h"

template<typename T>
class IIterable
{
public:
	virtual ~IIterable(){}
	virtual void each(IExecutor<T>& executor) = 0;
};

#endif // _I2F_IITERABLE_H_