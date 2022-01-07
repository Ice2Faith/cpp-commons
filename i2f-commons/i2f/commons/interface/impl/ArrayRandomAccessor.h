#ifndef _I2F_ARRAY_RANDOM_ACCESSOR_H_
#define _I2F_ARRAY_RANDOM_ACCESSOR_H_
#include"../IRandomAccessor.h"


template<typename T>
class ArrayRandomAccessor : virtual public IRandomAccessor<T>
{
private:
	T* m_data;
	int m_size;
public:
	virtual ~ArrayRandomAccessor(){}
	ArrayRandomAccessor(T* data, int size);
	ArrayRandomAccessor(const ArrayRandomAccessor<T>& acs);
	ArrayRandomAccessor<T>& operator=(const ArrayRandomAccessor<T>& acs);
	virtual T& get(int index);
	virtual void set(int index, const T& val);
	virtual int size();

};

template<typename T>
ArrayRandomAccessor<T>::ArrayRandomAccessor(T* data, int size)
{
	this->m_data = data;
	this->m_size = size;
}

template<typename T>
ArrayRandomAccessor<T>::ArrayRandomAccessor(const ArrayRandomAccessor<T>& acs)
{
	this->m_data = acs.m_data;
	this->m_size = acs.m_size;
}

template<typename T>
ArrayRandomAccessor<T>& ArrayRandomAccessor<T>::operator=(const ArrayRandomAccessor<T>& acs)
{
	this->m_data = acs.m_data;
	this->m_size = acs.m_size;
	return *this;
}

template<typename T>
T& ArrayRandomAccessor<T>::get(int index)
{
	return this->m_data[index];
}

template<typename T>
void ArrayRandomAccessor<T>::set(int index, const T& val)
{
	this->m_data[index] = val;
}

template<typename T>
int ArrayRandomAccessor<T>::size()
{
	return this->m_size;
}

#endif // _I2F_ARRAY_RANDOM_ACCESSOR_H_