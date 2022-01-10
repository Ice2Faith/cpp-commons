#ifndef _I2F_IDATA_CONVERTER_H_
#define _I2F_IDATA_CONVERTER_H_
#include"../base/String.hpp"
#include"../container/Array.hpp"

template<typename T>
class IDataConverter
{
public:
	virtual ~IDataConverter(){}
	virtual Array<byte> dataOf(TString<T> str)=0;
	virtual TString<T> dataTo(Array<byte> data)=0;
};


#endif // _I2F_IDATA_CONVERTER_H_
