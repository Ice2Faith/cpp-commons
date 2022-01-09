#include"Utf8Codec.h"
#include"ICodec.h"
#include"../container/ArrayList.hpp"


int Utf8Codec::readUniChar16(const byte * ch, int size, int * from, UniChar16 * save)
{
	UniChar32 ch32 = 0;
	int ret = Utf8Codec::readUniChar32(ch, size, from, &ch32);
	*save = (UniChar16)ch32;
	if (ret != 1){
		return ret;
	}
	if (*save != ch32){
		return -1;
	}
	return 1;
}

int Utf8Codec::readUniChar32(const byte * ch, int size, int * from, UniChar32 * save)
{
	if (*from >= size){
		return 0;
	}
	byte bt = ch[*from + 0];
	if (bt >= 0x80){
		int count = 0;
		while (bt & 0x80){
			count++;
			if (count >= 8){
				break;
			}
			bt <<= 1;
		}
		if (count == 0 || count >= 8){
			return -1;
		}
		if ((*from) + count > size){
			return 0;
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
				c32 |= (ch[*from + i] & 0x3f);
			}
			*save = c32;
			*from += count;
		}
	}
	else{
		*save = bt;
		(*from)++;
	}
	return 1;
}

Array<byte> Utf8Codec::writeUniChar32(UniChar32 u32)
{
	ArrayList<byte> list(8);
	if (u32 < 0x80){
		list.add((byte)(u32 & 0xff));
	}
	else{
		UniChar32 pch = u32;
		int spaceBitCount = 0;
		while ((pch & 0x80000000) == 0)
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
		if (leftCount + b6Count + 1 + 1>8){
			// 最大UTF字节数：6
			// 6位整部分：32/6=5--余数2
			// 加上标识需要已字节：5+1=6
			// 则标识位中，可用为：1111110x
			// 仅1位可用，而最大余数为2，则unicode编码最大值应该为2^31
		}
		else{
			byte cch = 0;
			for (int i = 0; i < b6Count + 1; i++){
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

Array<byte> Utf8Codec::writeUniChar16(UniChar16 u16)
{
	return Utf8Codec::writeUniChar32((UniChar32)u16);
}



