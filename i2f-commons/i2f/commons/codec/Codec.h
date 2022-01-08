#ifndef _I2F_CODEC_H_
#define _I2F_CODEC_H_

#include<stdio.h>

#include"GbkCodec.h"
#include"Utf8Codec.h"

typedef unsigned short UniChar16;
typedef unsigned int UniChar32;


class Codec
{
public:
	Codec();
	virtual ~Codec();
	
	/*
	参数解释：
	ch数据的来源，size可用的数据大小,from从数据的什么位置读取,save保存数据的地方
	返回值解释：
	1正常，0数据不够，-1无法解析
	*/
	static int readNextUtf8Char2UniChar16(const byte * ch,int size,int * from,UniChar16 * save);
	static int readNextUtf8Char2UniChar32(const byte * ch,int size, int * from, UniChar32 * save);
	static Array<byte> writeUniChar32AsUtf8Chars(UniChar32 u32);
	static Array<byte> writeUniChar16AsUtf8Chars(UniChar16 u16);

	static int readNextGbkChar2UniChar16(const byte * ch, int size, int * from, UniChar16 * save);
	static int readNextGbkChar2UniChar32(const byte * ch, int size, int * from, UniChar32 * save);
	static Array<byte> writeUniChar32AsGbkChars(UniChar32 u32);
	static Array<byte> writeUniChar16AsGbkChars(UniChar16 u16);

	
};

Codec::Codec()
{

}
Codec::~Codec()
{

}

int Codec::readNextUtf8Char2UniChar16(const byte * ch, int size, int * from, UniChar16 * save)
{
	ICodec& codec = Utf8Codec();
	return codec.readUniChar16(ch, size, from, save);
}
int Codec::readNextUtf8Char2UniChar32(const byte * ch, int size, int * from, UniChar32 * save)
{
	ICodec& codec = Utf8Codec();
	return codec.readUniChar32(ch, size, from, save);
}

Array<byte> Codec::writeUniChar16AsUtf8Chars(UniChar16 u16)
{
	ICodec& codec = Utf8Codec();
	return codec.writeUniChar16(u16);
}

Array<byte> Codec::writeUniChar32AsUtf8Chars(UniChar32 u32)
{
	ICodec& codec = Utf8Codec();
	return codec.writeUniChar32(u32);
}

int Codec::readNextGbkChar2UniChar16(const byte * ch, int size, int * from, UniChar16 * save)
{
	ICodec& codec = GbkCodec();
	return codec.readUniChar16(ch,size,from,save);
}
int Codec::readNextGbkChar2UniChar32(const byte * ch, int size, int * from, UniChar32 * save)
{
	ICodec& codec = GbkCodec();
	return codec.readUniChar32(ch, size, from, save);
}
Array<byte> Codec::writeUniChar32AsGbkChars(UniChar32 u32)
{
	ICodec& codec = GbkCodec();
	return codec.writeUniChar32(u32);
}
Array<byte> Codec::writeUniChar16AsGbkChars(UniChar16 u16)
{
	ICodec& codec = GbkCodec();
	return codec.writeUniChar16(u16);
}

#endif // _I2F_CODEC_H_

