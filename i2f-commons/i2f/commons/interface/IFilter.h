#ifndef _I2F_IFILTER_H_
#define _I2F_IFILTER_H_


template<typename T>
class IFilter
{
public:
	virtual ~IFilter(){}
	virtual bool filte(T t) =0;
};

#endif // _I2F_IFILTER_H_