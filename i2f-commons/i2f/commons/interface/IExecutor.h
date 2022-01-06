#ifndef _I2F_IEXECUTOR_H_
#define _I2F_IEXECUTOR_H_


template<typename T>
class IExecutor
{
public:
	virtual ~IExecutor(){}
	virtual void execute(T& t)=0;
};

#endif // _I2F_IEXECUTOR_H_