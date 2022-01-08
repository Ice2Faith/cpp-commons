#ifndef _I2F_MEMORY_H_
#define _I2F_MEMORY_H_

#define COUNT_ARRAY(arr) (sizeof(arr)/(sizeof(arr[0])))

#include"../container/ArrayList.hpp"
#include"Base.hpp"
#include<stdio.h>

class Memory
{
public:
	virtual ~Memory(){}
	/*
	检测主机是否大小端
	*/
	static bool isBigEndian();
	static bool isLittleEndian();
	/*
	将主机数据转换为大小端数据
	*/
	static void toBigEndian(void * data, int size);
	static void toLittleEndian(void * data, int size);
	/*
	将大小端数据转换为主机数据
	*/
	static void fromBigEndian(void * data, int size);
	static void fromLittleEndian(void * data, int size);

	/*
	翻转内存数据
	*/
	static void reverseMemory(void * mem, int size);
	/*
	交换内存空间的值
	*/
	static void swapMemory(void * a, void * b, int size);

	static void fillMemory(void * mem, int size, void * data, int dsize);

	static void copyMemory(void * dst, int dstMaxSize, void * src, int srcMaxSize, int from, int count);
	
	/*
	可视化内存
	给定数据data的指针，给定data的大小size
	转换为mode所指定的模式:2 8 10 16,分别是这四个进制的表现形式，不是这些值则按照2处理
	isOne标识data是否要作为一个整体看待，这将会引发大小端的判定，统一转换为大端
	splitByteBySpace是否需要使用空格分隔每个字节
	*/
	static ArrayList<char> visualMemory(void * data, int size, int mode, bool isOne, bool endWithZero, bool splitByteBySpace);
	static ArrayList<char> visualMemoryHex2(void * data, int size, bool isOne);
	static ArrayList<char> visualMemoryHex8(void * data, int size, bool isOne);
	static ArrayList<char> visualMemoryHex10(void * data, int size, bool isOne);
	static ArrayList<char> visualMemoryHex16(void * data, int size, bool isOne);
};


bool Memory::isBigEndian()
{
	unsigned int testNum = 0x12345678;
	unsigned char * p = (unsigned char *)(void *)&testNum;
	return p[0] == 0x12;
}

bool Memory::isLittleEndian()
{
	unsigned int testNum = 0x12345678;
	unsigned char * p = (unsigned char *)(void *)&testNum;
	return p[0] == 0x78;
}

void Memory::toBigEndian(void * data, int size)
{
	if (Memory::isLittleEndian()){
		Memory::reverseMemory(data, size);
	}
}

void Memory::toLittleEndian(void * data, int size)
{
	if (Memory::isBigEndian()){
		Memory::reverseMemory(data, size);
	}
}

void Memory::fromBigEndian(void * data, int size)
{
	if (Memory::isLittleEndian()){
		Memory::reverseMemory(data, size);
	}
}

void Memory::fromLittleEndian(void * data, int size)
{
	if (Memory::isBigEndian()){
		Memory::reverseMemory(data, size);
	}
}

void Memory::reverseMemory(void * mem, int size)
{
	unsigned char * pm = (unsigned char *)mem;
	int i = 0;
	int j = size - 1;
	while (i < j){
		Memory::swapMemory(&pm[i], &pm[j], 1);
		i++;
		j--;
	}
}

void Memory::swapMemory(void * a, void * b, int size)
{
	unsigned char * sp = (unsigned char *)a;
	unsigned char * dp = (unsigned char *)b;
	for (int i = 0; i < size; i++)
	{
		sp[i] = sp[i] ^ dp[i];
		dp[i] = sp[i] ^ dp[i];
		sp[i] = sp[i] ^ dp[i];
	}
}

void Memory::fillMemory(void * mem, int size, void * data, int dsize)
{
	unsigned char * pdst = (unsigned char *)mem;
	unsigned char * psrc = (unsigned char *)data;
	int i = 0;
	while (i < size){
		for (int j = 0; j < dsize && i<size; j++){
			pdst[i] = psrc[j];
			i++;
		}
	}
}

void Memory::copyMemory(void * dst, int dstMaxSize, void * src, int srcMaxSize, int from, int count)
{
	unsigned char * pdst = (unsigned char *)dst;
	unsigned char * psrc = (unsigned char *)src;
	for (int i = 0; i < count && (from+i)<srcMaxSize && i<dstMaxSize ; i++){
		pdst[i] = psrc[from+i];
	}
}


ArrayList<char> Memory::visualMemory(void * data, int size, int mode, bool isOne, bool endWithZero, bool splitByteBySpace)
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
		if (Memory::isLittleEndian()){
			start = size - 1;
			end = -1;
			step = -1;
		}
	}
	byte * bts = (byte *)data;
	char space = 0x20;//空格符
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
		}
		else if (mode == 10){
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

ArrayList<char> Memory::visualMemoryHex2(void * data, int size, bool isOne)
{
	return Memory::visualMemory(data, size, 2, isOne, true, true);
}
ArrayList<char> Memory::visualMemoryHex8(void * data, int size, bool isOne)
{
	return Memory::visualMemory(data, size, 8, isOne, true, true);
}
ArrayList<char> Memory::visualMemoryHex10(void * data, int size, bool isOne)
{
	return Memory::visualMemory(data, size, 10, isOne, true, true);
}
ArrayList<char> Memory::visualMemoryHex16(void * data, int size, bool isOne)
{
	return Memory::visualMemory(data, size, 16, isOne, true, true);
}

#endif // _I2F_MEMORY_H_