#ifndef _I2F_IITERATOR_H_
#define _I2F_IITERATOR_H_

template<typename T>
class IIterator
{
public:
	virtual ~IIterator(){}
	virtual bool hasNext() = 0;
	virtual T& get() = 0;
	virtual T next() = 0;
};

#endif // _I2F_IITERATOR_H_