#ifndef _I2F_ICODEC_H_
#define _I2F_ICODEC_H_
#include"../container/Array.hpp"
#include"../base/Base.hpp"

class ICodec
{
public:
	virtual ~ICodec(){}
	/*
	参数解释：
	ch数据的来源，size可用的数据大小,from从数据的什么位置读取,save保存数据的地方
	返回值解释：
	1正常，0数据不够，-1无法解析
	*/
	virtual int readUniChar16(const byte * ch, int size, int * from, UniChar16 * save) = 0;
	virtual int readUniChar32(const byte * ch, int size, int * from, UniChar32 * save) = 0;
	virtual Array<byte> writeUniChar32(UniChar32 u32) = 0;
	virtual Array<byte> writeUniChar16(UniChar16 u16) = 0;
};

#endif // _I2F_ICODEC_H_

