#ifndef _I2F_STACK_H_
#define _I2F_STACK_H_
#include"Container.h"

template<typename T>
class  Stack : virtual public Container
{
public:
	virtual ~Stack(){};

	virtual void push(const T& val) = 0;
	virtual T pop() = 0;
	virtual T& top() = 0;

	
};

#endif // _I2F_STACK_H_
