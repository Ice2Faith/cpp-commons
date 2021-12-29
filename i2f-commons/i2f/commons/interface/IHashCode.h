#ifndef _I2F_IHASHCODE_H_
#define _I2F_IHASHCODE_H_

class IHashCode
{
public:
	virtual ~IHashCode(){}
	virtual int hashcode() =0;
};

#endif // _I2F_IHASHCODE_H_