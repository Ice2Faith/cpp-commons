#ifndef _I2F_STACK_H_
#define _I2F_STACK_H_

template<typename T>
class  Stack
{
public:
	virtual ~Stack(){};

	virtual void push(const T& val) = 0;
	virtual T pop() = 0;
	virtual T& top() = 0;

	
};

#endif // _I2F_STACK_H_
