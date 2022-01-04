#ifndef _I2F_MAP_H_
#define _I2F_MAP_H_
#include"Container.h"
#include"../data/Entry.hpp"

template<typename T,typename E>
class  Map
{
public:
	virtual ~Map(){};
    virtual void put( Entry<T,E>& val) = 0;
	virtual void put(const T& key,const E& val) = 0;
	virtual bool contains(const T& key) = 0;
	virtual E& get(const T& key) = 0;
	virtual void remove(const T& key) = 0;
	virtual void clear() = 0;
    virtual IIterator<Entry<T,E>>* iterator() = 0;
	
};

#endif // _I2F_MAP_H_
