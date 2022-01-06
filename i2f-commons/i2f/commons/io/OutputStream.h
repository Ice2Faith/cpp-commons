#ifndef _I2F_OUTPUTSTREAM_H_
#define _I2F_OUTPUTSTREAM_H_

#include"../base/Base.hpp"
#include"../container/Array.hpp"
#include"../interface/Closeable.h"

class OutputStream : virtual public Closeable
{
public:
	virtual ~OutputStream(){};
	virtual int write(int bt) = 0;
	virtual int write(Array<byte>& buf) = 0;
	virtual int write(Array<byte>& buf, int offset, int count) = 0;
	virtual void flush() = 0;
	virtual bool avaliable() = 0;
};

#endif // _I2F_OUTPUTSTREAM_H_
