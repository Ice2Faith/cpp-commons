#ifndef _I2F_CHS_H_
#define _I2F_CHS_H_
#include"../codec/StringCodec.h"
#include"String.hpp"
#include"../codec/ICodec.h"
#include"../codec/GbkCodec.h"
#include"../codec/Utf8Codec.h"
#include"../../init/Eviroment.h"

template<typename T>
class TChs
{
public:
	static T charOf(char * chs,StringCodec::Charset charset);
	static TString<T> strOf(char * chs,StringCodec::Charset charset);

	static T charOf(char * chs);
	static TString<T> strOf(char * chs);
};

template<typename T>
T TChs<T>::charOf(char * chs)
{
	return TChs<T>::charOf(chs,Eviroment::defaultCharset());
}

template<typename T>
TString<T> TChs<T>::strOf(char * chs)
{
	return TChs<T>::strOf(chs, Eviroment::defaultCharset());
}

template<typename T>
T TChs<T>::charOf(char * chs, StringCodec::Charset charset)
{
	int size = 0;
	while (chs[size] != 0){
		size++;
	}
	if (charset == StringCodec::GBK){
		GbkCodec codec;
		int from = 0;
		UniChar32 u32 = 0;
		int errCode=codec.readUniChar32((const byte *)chs, size, &from, &u32);
		if (errCode == 1){
			return (T)u32;
		}
		else{
			return (T)chs[0];
		}
	}
	else if (charset == StringCodec::UTF8){
		Utf8Codec codec;
		int from = 0;
		UniChar32 u32 = 0;
		int errCode = codec.readUniChar32((const byte *)chs, size, &from, &u32);
		if (errCode == 1){
			return (T)u32;
		}
		else{
			return (T)chs[0];
		}
	}
	else{
		return (T)chs[0];
	}
}

template<typename T>
TString<T> TChs<T>::strOf(char * chs, StringCodec::Charset charset)
{
	int size = 0;
	while (chs[size] != 0){
		size++;
	}
	Array<byte> data(size);
	for (int i = 0; i < size; i++){
		data[i] = (byte)chs[i];
	}
	ByteArrayInputStream is(data);
	Array<UniChar32> arr = StringCodec::stringOf(is, charset);
	TString<T> ret;
	for (int i = 0; i < arr.size(); i++){
		ret.appendChar((T)arr[i]);
	}
	return ret;
}

typedef TChs<UniChar16> Chs;

#endif // _I2F_CHS_H_