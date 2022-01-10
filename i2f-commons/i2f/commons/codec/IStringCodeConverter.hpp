#ifndef _I2F_ISTRING_CODE_CONVERTER_H_
#define _I2F_ISTRING_CODE_CONVERTER_H_
#include"../base/String.hpp"

/*
适用于字符串在字符串的某种表现形式之间转换
比如：
在\u5634的U码之间转换
在0x56,0x32的十六进制之间转换
再%56%32的URL之间转换
*/
enum StringCodeset{ UCODE = 0x01, HEXCODE=0x02,URICODE=0x03 };

template<typename T>
class IStringCodeConverter
{
public:
	virtual ~IStringCodeConverter(){}
	virtual TString<T> stringOf(TString<T> str) = 0;
	virtual TString<T> stringTo(TString<T> str) = 0;
	
};

#endif // _I2F_ISTRING_CODE_CONVERTER_H_

