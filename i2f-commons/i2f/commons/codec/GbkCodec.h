#ifndef _I2F_GBK_CODEC_H_
#define _I2F_GBK_CODEC_H_
#include"ICodec.h"
#include"GbkDict.h"

class GbkCodec : virtual public ICodec
{
public:
	virtual ~GbkCodec(){}
	virtual int readUniChar16(const byte * ch, int size, int * from, UniChar16 * save);
	virtual int readUniChar32(const byte * ch, int size, int * from, UniChar32 * save);
	virtual Array<byte> writeUniChar32(UniChar32 u32);
	virtual Array<byte> writeUniChar16(UniChar16 u16);
};

int GbkCodec::readUniChar16(const byte * ch, int size, int * from, UniChar16 * save)
{
	UniChar32 ch32 = 0;
	int ret = GbkCodec::readUniChar32(ch, size, from, &ch32);
	*save = (UniChar16)ch32;
	if (ret != 1){
		return ret;
	}
	if (*save != ch32){
		return -1;
	}
	return 1;
}

int GbkCodec::readUniChar32(const byte * ch, int size, int * from, UniChar32 * save)
{
	if (*from >= size){
		return 0;
	}
	byte bt = ch[*from + 0];
	if (bt < 0x80){
		(*save) = bt;
		(*from)++;
		return 1;
	}
	if ((*from) + 2 > size){
		return 0;
	}
	byte nbt = ch[*from + 1];
	unsigned short gcode = (((int)bt) << 8) | (nbt);
	unsigned short ucode = gbk2unicode(gcode, '?');
	*from += 2;
	*save = ucode;
	return 1;
}

Array<byte> GbkCodec::writeUniChar32(UniChar32 u32)
{
	if (u32 < 0x80){
		Array<byte> ret(1);
		ret[0] = (byte)u32;
		return ret;
	}
	unsigned short ucode = (unsigned short)u32;
	unsigned short gcode = unicode2gbk(ucode, '?');
	if (gcode < 0x80){
		Array<byte> ret(1);
		ret[0] = (byte)gcode;
		return ret;
	}
	else{
		Array<byte> ret(2);
		ret[0] = (byte)((gcode >> 8) & 0xff);
		ret[1] = (byte)(gcode & 0xff);
		return ret;
	}
}

Array<byte> GbkCodec::writeUniChar16(UniChar16 u16)
{
	return GbkCodec::writeUniChar32((UniChar32)u16);
}


#endif // _I2F_GBK_CODEC_H_

