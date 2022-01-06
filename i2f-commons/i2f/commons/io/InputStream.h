#ifndef _I2F_INPUTSTREAM_H_
#define _I2F_INPUTSTREAM_H_

#include"../base/Base.hpp"
#include"../container/Array.hpp"
#include"../interface/Closeable.h"

class InputStream : virtual public Closeable
{
public:
	virtual ~InputStream(){};
	virtual int read() = 0;
	virtual int read(Array<byte>& buf) = 0;
	virtual int read(Array<byte>& buf, int offset, int count) = 0;
	virtual void skip(long len) = 0;
	virtual void reset() = 0;
	virtual bool avaliable() = 0;
};

#endif // _I2F_INPUTSTREAM_H_
