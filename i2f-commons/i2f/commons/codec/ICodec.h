#ifndef _I2F_ICODEC_H_
#define _I2F_ICODEC_H_
#include"../container/Array.hpp"
#include"../base/Base.hpp"

class ICodec
{
public:
	virtual ~ICodec(){}
	/*
	�������ͣ�
	ch���ݵ���Դ��size���õ����ݴ�С,from�����ݵ�ʲôλ�ö�ȡ,save�������ݵĵط�
	����ֵ���ͣ�
	1������0���ݲ�����-1�޷�����
	*/
	virtual int readUniChar16(const byte * ch, int size, int * from, UniChar16 * save) = 0;
	virtual int readUniChar32(const byte * ch, int size, int * from, UniChar32 * save) = 0;
	virtual Array<byte> writeUniChar32(UniChar32 u32) = 0;
	virtual Array<byte> writeUniChar16(UniChar16 u16) = 0;
};

#endif // _I2F_ICODEC_H_

