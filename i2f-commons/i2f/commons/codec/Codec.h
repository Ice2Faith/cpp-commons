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
	static bool isBigEndian();
	static bool isLittleEndian();

	/*
	�������ͣ�
	ch���ݵ���Դ��size���õ����ݴ�С,from�����ݵ�ʲôλ�ö�ȡ,save�������ݵĵط�
	����ֵ���ͣ�
	1������0���ݲ�����-1�޷�����
	*/
	static int readNextUtf8Char2UniChar16(const byte * ch,int size,int * from,UniChar16 * save);
	static int readNextUtf8Char2UniChar32(const byte * ch,int size, int * from, UniChar32 * save);
	static Array<byte> writeUniChar32AsUtf8Chars(UniChar32 u32);
	static Array<byte> writeUniChar16AsUtf8Chars(UniChar16 u16);

	static int readNextGbkChar2UniChar16(const byte * ch, int size, int * from, UniChar16 * save);
	static int readNextGbkChar2UniChar32(const byte * ch, int size, int * from, UniChar32 * save);
	static Array<byte> writeUniChar32AsGbkChars(UniChar32 u32);
	static Array<byte> writeUniChar16AsGbkChars(UniChar16 u16);

	/*
	���ӻ��ڴ�
	��������data��ָ�룬����data�Ĵ�Сsize
	ת��Ϊmode��ָ����ģʽ:2 8 10 16,�ֱ������ĸ����Ƶı�����ʽ��������Щֵ����2����
	isOne��ʶdata�Ƿ�Ҫ��Ϊһ�����忴�����⽫��������С�˵��ж���ͳһת��Ϊ���
	splitByteBySpace�Ƿ���Ҫʹ�ÿո�ָ�ÿ���ֽ�
	*/
	static ArrayList<char> visualMemory(void * data, int size, int mode, bool isOne, bool endWithZero, bool splitByteBySpace);
	static ArrayList<char> visualMemoryHex2(void * data, int size, bool isOne);
	static ArrayList<char> visualMemoryHex8(void * data, int size, bool isOne);
	static ArrayList<char> visualMemoryHex10(void * data, int size, bool isOne);
	static ArrayList<char> visualMemoryHex16(void * data, int size, bool isOne);
};

Codec::Codec()
{

}
Codec::~Codec()
{

}
bool Codec::isBigEndian()
{
	unsigned int testNum = 0x12345678;
	unsigned char * p = (unsigned char *)(void *)&testNum;
	return p[0] == 0x12;
}
bool Codec::isLittleEndian()
{
	unsigned int testNum = 0x12345678;
	unsigned char * p = (unsigned char *)(void *)&testNum;
	return p[0] == 0x78;
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

ArrayList<char> Codec::visualMemory(void * data, int size, int mode, bool isOne,bool endWithZero, bool splitByteBySpace)
{
	int psize = 8;
	if (mode == 2){
		psize = 2;
	}
	if (mode == 8){
		psize = 8;
	}
	if (mode == 10){
		psize = 10;
	}
	if (mode == 16){
		psize = 16;
	}
	ArrayList<char> ret(size * psize);
	int start = 0;
	int end = size;
	int step = 1;
	if (isOne){
		if (Codec::isLittleEndian()){
			start = size - 1;
			end = -1;
			step = -1;
		}
	}
	byte * bts = (byte *)data;
	char space = 0x20;//�ո��
	bool isFirst = true;
	char buf[10] = { 0 };
	for (int i = start; i != end; i += step){
		if (!isFirst){
			if (splitByteBySpace){
				ret.add(space);
			}
		}
		bool printMode = false;
		byte bt = bts[i];
		if (mode == 16){
			printMode = true;
			sprintf(buf, "%02x\0", bt);
		}else if (mode == 10){
			printMode = true;
			sprintf(buf, "%03d\0", bt);
		}
		else if (mode == 8){
			printMode = true;
			sprintf(buf, "%03o\0", bt);
		}
		
		if (printMode)
		{
			int j = 0;
			while (buf[j]){
				ret.add(buf[j]);
				j++;
			}
		}
		else
		{
			for (int i = 0; i < 8; i++){
				char ch = (bt & 0x80) == 0 ? '0' : '1';
				ret.add(ch);
				bt <<= 1;
			}
		}
		isFirst = false;
	}
	if (endWithZero){
		ret.add('\0');
	}
	return ret;
}

ArrayList<char> Codec::visualMemoryHex2(void * data, int size, bool isOne)
{
	return Codec::visualMemory(data, size, 2, isOne, true, true);
}
ArrayList<char> Codec::visualMemoryHex8(void * data, int size, bool isOne)
{
	return Codec::visualMemory(data, size, 8, isOne, true, true);
}
ArrayList<char> Codec::visualMemoryHex10(void * data, int size, bool isOne)
{
	return Codec::visualMemory(data, size, 10, isOne, true, true);
}
ArrayList<char> Codec::visualMemoryHex16(void * data, int size, bool isOne)
{
	return Codec::visualMemory(data, size, 16, isOne, true, true);
}

#endif // _I2F_CODEC_H_

