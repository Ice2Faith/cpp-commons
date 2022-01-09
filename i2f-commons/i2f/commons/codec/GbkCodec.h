#ifndef _I2F_GBK_CODEC_H_
#define _I2F_GBK_CODEC_H_
#include"ICodec.h"
#include"GbkDict.h"
#include"../container/Array.hpp"

class GbkCodec : virtual public ICodec
{
public:
	virtual ~GbkCodec(){}
	virtual int readUniChar16(const byte * ch, int size, int * from, UniChar16 * save);
	virtual int readUniChar32(const byte * ch, int size, int * from, UniChar32 * save);
	virtual Array<byte> writeUniChar32(UniChar32 u32);
	virtual Array<byte> writeUniChar16(UniChar16 u16);
};


#endif // _I2F_GBK_CODEC_H_

