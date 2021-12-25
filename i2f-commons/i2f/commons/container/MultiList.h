#ifndef _I2F_MULTI_LIST_H_
#define _I2F_MULTI_LIST_H_
#include"List.h"
#include"Stack.h"
#include"Queue.h"

template<typename T>
class MultiList : virtual public List<T>,virtual public Stack<T>,virtual public Queue<T>
{
public:
	virtual ~MultiList(){}

};

#endif // _I2F_MULTI_LIST_H_
