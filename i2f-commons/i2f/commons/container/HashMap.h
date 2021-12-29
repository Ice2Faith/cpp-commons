#ifndef _I2F_HASH_MAP_H_
#define _I2F_HASH_MAP_H_
#include"Container.h"

template<typename T,typename E>
class  HashMap : virtual public Container
{
public:
	virtual ~HashMap(){};

	virtual void put(const T& val) = 0;
	virtual bool contains() = 0;
	virtual T& get() = 0;
	virtual void clear() = 0;

	
};

#endif // _I2F_HASH_MAP_H_
