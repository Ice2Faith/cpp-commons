#ifndef _I2F_ICOMPARATOR_H_
#define _I2F_ICOMPARATOR_H_

template<typename T>
class IComparator
{
public:
	virtual ~IComparator(){}
	virtual int compare(T t1, T t2) = 0;
};

#endif // _I2F_ICOMPARATOR_H_