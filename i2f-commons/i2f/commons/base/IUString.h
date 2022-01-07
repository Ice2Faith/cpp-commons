#ifndef _I2F_IUSTRING_H_
#define _I2F_IUSTRING_H_

#include"../base/Base.hpp"
#include"../container/Array.hpp"
#include"../codec/StringCodec.h"

class IUString
{
public:
	virtual ~IUString(){}
	virtual void ofBytes(Array<byte>& bts,StringCodec::Charset charset) = 0;
	virtual Array<byte> toBytes(StringCodec::Charset charset) = 0;
	
};

#endif // _I2F_IUSTRING_H_