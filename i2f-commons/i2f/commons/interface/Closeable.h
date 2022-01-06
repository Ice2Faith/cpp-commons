#ifndef _I2F_CLOSEABLE_H_
#define _I2F_CLOSEABLE_H_


class Closeable
{
public:
	virtual ~Closeable(){}
	virtual void close() = 0;
};

#endif // _I2F_CLOSEABLE_H_