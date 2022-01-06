#ifndef _I2F_PRINT_EXECUTOR_H_
#define _I2F_PRINT_EXECUTOR_H_

#include"../IExecutor.h"

template<typename T>
class PrintExecutor : virtual public IExecutor<T>
{
private:
	char * m_format;
public:
	PrintExecutor(char * format){
		this->m_format = format;
	}
	virtual void execute(T& t)
	{
		printf(this->m_format, t);
	}
};

#endif // _I2F_PRINT_EXECUTOR_H_