#ifndef _I2F_ARRAY_READ_RANDOM_ACCESSOR_H_
#define _I2F_ARRAY_READ_RANDOM_ACCESSOR_H_
#include"../IReadRandomAccessor.h"

template<typename T>
class ArrayReadRandomAccesor : virtual public IReadRandomAccessor<T>
{
private:
	int m_size;
	T* m_data;
public:
	ArrayReadRandomAccesor(T* data,int size);
	ArrayReadRandomAccesor(const ArrayReadRandomAccesor<T>& acsr);
	ArrayReadRandomAccesor<T>& operator=(const ArrayReadRandomAccesor<T>& acsr);
	virtual ~ArrayReadRandomAccesor(){}
	virtual int size();
	virtual T& get(int index);
};

template<typename T>
ArrayReadRandomAccesor<T>::ArrayReadRandomAccesor(T* data, int size)
{
	this->m_data = data;
	this->m_size = size;
}

template<typename T>
ArrayReadRandomAccesor<T>::ArrayReadRandomAccesor(const ArrayReadRandomAccesor<T>& acsr)
{
	this->m_data = acsr.m_data;
	this->m_size = acsr.m_size;
}

template<typename T>
ArrayReadRandomAccesor<T>& ArrayReadRandomAccesor<T>::operator=(const ArrayReadRandomAccesor<T>& acsr)
{
	this->m_data = acsr.m_data;
	this->m_size = acsr.m_size;
	return *this;
}

template<typename T>
int ArrayReadRandomAccesor<T>::size()
{
	return this->m_size;
}

template<typename T>
T& ArrayReadRandomAccesor<T>::get(int index)
{
	return this->m_data[index];
}

#endif // _I2F_ARRAY_READ_RANDOM_ACCESSOR_H_