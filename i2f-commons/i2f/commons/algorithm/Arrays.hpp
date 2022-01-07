#ifndef _I2F_ARRAYS_H_
#define _I2F_ARRAYS_H_
#include"Algorithem.hpp"

template<typename T>
class Arrays
{
public:
	virtual bool equal(T* str1, T * str2, int low, int height);
};


template<typename T>
bool Arrays<T>::equal(T* str1, T * str2, int low, int height)
{
	AlgoEqual<T> algo;
	return algo.fastEqualArray(str1, str2, low, height);
}

#endif // _I2F_ARRAYS_H_
