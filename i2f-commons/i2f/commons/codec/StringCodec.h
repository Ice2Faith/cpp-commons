#ifndef _I2F_STRING_CODEC_H_
#define _I2F_STRING_CODEC_H_
#include"../io/InputStream.h"
#include"../container/Array.hpp"

class StringCodec
{
public:
	enum Charset{ ASCII = 0x00, GBK = 0x01, UTF8 = 0x02 };
	//��ȡָ���ַ������ַ�
	static Array<UniChar32> stringOf(InputStream& is, Charset charset);
	//д��Ϊָ���ַ������ַ�����
	static Array<byte> stringTo(Array<UniChar32>& str, Charset charset);
};

#endif // _I2F_STRING_CODEC_H_

