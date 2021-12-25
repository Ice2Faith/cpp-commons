#ifndef _I2F_IMAPPER_H_
#define _I2F_IMAPPER_H_

template<typename T,typename E>
class IMapper
{
public:
	virtual ~IMapper(){}
	virtual E map(T t) = 0;
};

#endif // _I2F_IMAPPER_H_