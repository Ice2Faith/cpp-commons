#ifndef _I2F_IEX_EQUALS_H_
#define _I2F_IEX_EQUALS_H_


template<typename T>
class IExEquals
{
public:
	virtual ~IExEquals(){}
	virtual bool equal(T t1, T t2) = 0;
};

#endif // _I2F_IEX_EQUALS_H_