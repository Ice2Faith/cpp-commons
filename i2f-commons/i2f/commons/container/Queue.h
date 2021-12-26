#ifndef _I2F_QUEUE_H_
#define _I2F_QUEUE_H_
#include"Container.h"
template<typename T>
class Queue : virtual public Container
{
public:
	virtual ~Queue(){}

	virtual void enque(const T& val) = 0;
	virtual T deque() = 0;
	virtual T& head() = 0;
	virtual T& tail() = 0;
};

#endif // _I2F_QUEUE_H_
