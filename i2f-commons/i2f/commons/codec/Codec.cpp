#include"Codec.h"

#include<stdio.h>

#include"GbkCodec.h"
#include"Utf8Codec.h"

typedef unsigned short UniChar16;
typedef unsigned int UniChar32;



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


