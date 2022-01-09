#ifndef _I2F_WRITER_H_
#define _I2F_WRITER_H_
#include"../base/Base.hpp"
#include"../base/String.hpp"
#include"../interface/Closeable.h"

class Writer : virtual public Closeable
{
public:
	virtual ~Writer(){};
	virtual void write(int ch) = 0;
	virtual void write(String str) = 0;
	virtual void writeLine(String str) = 0;
};


#endif // _I2F_WRITER_H_
