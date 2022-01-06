#ifndef _I2F_IRANDOM_ACCESSOR_H_
#define _I2F_IRANDOM_ACCESSOR_H_


template<typename T>
class IRandomAccessor
{
public:
	virtual ~IRandomAccessor(){}
	virtual int size() = 0;
	virtual T& get(int index) = 0;
	virtual void set(int index, const T& val) = 0;
};

#endif // _I2F_IRANDOM_ACCESSOR_H_