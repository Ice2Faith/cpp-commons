#ifndef _I2F_READER_H_
#define _I2F_READER_H_
#include"../base/Base.hpp"
#include"../base/String.hpp"
#include"../interface/Closeable.h"

class Reader : virtual public Closeable
{
public:
	virtual ~Reader(){};
	virtual int read() = 0;
	virtual String readLine() = 0;
	virtual String readAll() = 0;
};


#endif // _I2F_READER_H_
