#ifndef _I2F_ISTRING_CODE_CONVERTER_H_
#define _I2F_ISTRING_CODE_CONVERTER_H_
#include"../base/String.hpp"

/*
�������ַ������ַ�����ĳ�ֱ�����ʽ֮��ת��
���磺
��\u5634��U��֮��ת��
��0x56,0x32��ʮ������֮��ת��
��%56%32��URL֮��ת��
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

