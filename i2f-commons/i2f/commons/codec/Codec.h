#ifndef _I2F_CODEC_H_
#define _I2F_CODEC_H_

#include"../base/Base.hpp"
#include"../container/Array.hpp"

typedef unsigned short UniChar16;
typedef unsigned int UniChar32;


class Codec
{
public:
	Codec();
	virtual ~Codec();
	
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

	
};


#endif // _I2F_CODEC_H_

