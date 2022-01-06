#ifndef _I2F_IHASH_EQUALS_H_
#define _I2F_IHASH_EQUALS_H_

#include"IHashCode.h"
#include"IEquals.h"

template<typename T>
class IHashEquals : virtual public IHashCode, virtual public IEquals
{
public:
	virtual ~IHashEquals(){}
};

#endif // _I2F_IHASH_EQUALS_H_