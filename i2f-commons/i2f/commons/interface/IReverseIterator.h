#ifndef _I2F_IREVERSE_ITERATOR_H_
#define _I2F_IREVERSE_ITERATOR_H_


template<typename T>
class IReverseIterator
{
public:
	virtual ~IReverseIterator(){}
	virtual bool hasPrevious() = 0;
	virtual T previous() = 0;
	virtual T& get() = 0;
	virtual void set(const T& val) = 0;
};

#endif // _I2F_IREVERSE_ITERATOR_H_