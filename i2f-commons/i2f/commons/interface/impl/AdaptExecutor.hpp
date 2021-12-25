#ifndef _I2F_ADAPT_EXECUTOR_H_
#define _I2F_ADAPT_EXECUTOR_H_
#include"../IExecutor.h"
#include"../../container/LinkList.hpp"

template<typename T>
class AdaptExecutor: virtual public IExecutor<T>
{
private:
	LinkList<T> list;
public:
	virtual ~AdaptExecutor()
	{
		this->list.clear();
	}
	virtual void execute(T& t)
	{
		list.add(t);
	}
	IIterator<T> * iterator()
	{
		return this->list.iterator();
	}
};

#endif // _I2F_ADAPT_EXECUTOR_H_