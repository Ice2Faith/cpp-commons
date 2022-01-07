#ifndef _I2F_SIZEABLE_H_
#define _I2F_SIZEABLE_H_


class Sizeable
{
public:
	virtual ~Sizeable(){}
	virtual int size() = 0;
};

#endif // _I2F_SIZEABLE_H_