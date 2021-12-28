#ifndef _I2F_OBJECT_H_
#define _I2F_OBJECT_H_
#include"String.hpp"

class Object
{
public:
	virtual ~Object(){};
	template<typename T>
	virtual TString<T> toString() = 0;
};



#endif // _I2F_OBJECT_H_

