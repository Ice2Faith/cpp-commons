#ifndef _I2F_CODEC_H_
#define _I2F_CODEC_H_
#include"../base/Base.hpp"
#include"../container/ArrayList.hpp"
#include"../container/Array.hpp"
#include<stdio.h>

typedef unsigned short UniChar16;
typedef unsigned int UniChar32;


class Codec
{
public:
	Codec();
	virtual ~Codec();
	static bool isBigEndian();
	static bool isLittleEndian();
	static bool readNextUtf8Char2UniChar16(const byte * ch,int * from,UniChar16 * save);
	static bool readNextUtf8Char2UniChar32(const byte * ch, int * from, UniChar32 * save);
	static Array<byte> writeUniChar32AsUtf8Chars(UniChar32 u32);
	static Array<byte> writeUniChar16AsUtf8Chars(UniChar16 u16);
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

bool Codec::readNextUtf8Char2UniChar16(const byte * ch, int * from, UniChar16 * save)
{
	UniChar32 ch32 = 0;
	bool ret = Codec::readNextUtf8Char2UniChar32(ch, from, &ch32);
	*save = (UniChar16)ch32;
	if (!ret){
		return ret;
	}
	if (*save != ch32){
		return false;
	}
	return true;
}
bool Codec::readNextUtf8Char2UniChar32(const byte * ch, int * from, UniChar32 * save)
{
	bool ret = true;
	byte bt = ch[*from+0];
	if (bt & 0x80){
		int count = 0;
		while (bt & 0x80){
			count++;
			if (count >= 8){
				break;
			}
			bt <<= 1;
		}
		if (count == 0 || count >= 8){
			ret = false;
		}
		else
		{
			UniChar32 c32 = 0;
			int bitCount = 8 - count - 1;
			int mask = 0;
			for (int i = 0; i < bitCount; i++){
				mask <<= 1;
				mask |= 1;
			}
			c32 |= ch[*from + 0] & mask;

			for (int i = 1; i < count; i++){
				c32 <<= 6;
				c32 |= (ch[*from+i] & 0x3f);
			}
			*save = c32;
			*from += count;
		}
	}
	else{
		*save = bt;
		*from++;
	}
	return ret;
}

Array<byte> Codec::writeUniChar16AsUtf8Chars(UniChar16 u16)
{
	return Codec::writeUniChar32AsUtf8Chars((UniChar32)u16);
}

Array<byte> Codec::writeUniChar32AsUtf8Chars(UniChar32 u32)
{
	ArrayList<byte> list(8);
	if (u32 < 0x80){
		list.add((byte)(u32 & 0xff));
	}
	else{
		UniChar32 pch = u32;
		int spaceBitCount = 0;
		while ((pch & 0x80000000) ==0)
		{
			spaceBitCount++;
			if (spaceBitCount >= 32){
				break;
			}
			pch <<= 1;
		}
		int bitCount = 32 - spaceBitCount;
		int b6Count = bitCount / 6;
		int leftCount = bitCount % 6;

		pch = u32;
		for (int i = 0; i < b6Count; i++){
			byte cch = 0x80 | (pch & 0x3f);
			list.addFirst(cch);
			pch >>= 6;
		}
		if (leftCount + b6Count+1 + 1>8){
			// ���UTF�ֽ�����6
			// 6λ�����֣�32/6=5--����2
			// ���ϱ�ʶ��Ҫ���ֽڣ�5+1=6
			// ���ʶλ�У�����Ϊ��1111110x
			// ��1λ���ã����������Ϊ2����unicode�������ֵӦ��Ϊ2^31
		}
		else{
			byte cch = 0;
			for (int i = 0; i < b6Count+1; i++){
				cch <<= 1;
				cch |= 1;
			}
			while ((cch & 0x80) == 0){
				cch <<= 1;
			}
			int mask = 0;
			for (int i = 0; i < leftCount; i++){
				mask <<= 1;
				mask |= 1;
			}

			cch |= pch & mask;
			
			list.addFirst(cch);
		}
	}
	Array<byte> arr;
	arr.of(list);
	return arr;
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

