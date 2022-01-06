#ifndef _I2F_ARRAY_H_
#define _I2F_ARRAY_H_

#include"../interface/IIterable.h"
#include"List.h"
#include<stdio.h>

template<typename T>
class Array : virtual public IIterable<T>
{
private:
	int m_size;
	T * m_data;
public:
	
	Array();

	Array(int size);

	Array(T data[], int count);

	Array(T data[], int from, int count);

	Array(const Array<T> & arr);

	Array(Array<T> && arr);

	Array<T>& operator=(const Array<T> & arr);

	Array<T>& operator=(Array<T> && arr);

	virtual ~Array();

	virtual T& get(int index);

	virtual void set(int index,const T& val);

	virtual T& operator[] (int index);

	virtual T* data();

	virtual int size();

	virtual void resize(int size);

	virtual void each(IExecutor<T>& executor);

	virtual void of(T data[], int count);

	virtual void of(T data[], int from, int count);

	virtual void of(List<T>& list);

	virtual void of(List<T>& list, int from, int count);

	void expand(int count);


};

template<typename T>
Array<T>::Array()
{
	this->m_data = NULL;
	this->m_size = 0;
}

template<typename T>
Array<T>::Array(int size)
{
	this->m_size = size;
	this->m_data = new T[size];
}

template<typename T>
void Array<T>::expand(int count)
{
	if (count <= 0){
		return;
	}
	int nsize = this->m_size + count;
	T* ndata = new T[nsize];
	if (this->m_data != NULL){
		for (int i = 0; i < this->m_size; i++){
			ndata[i] = this->m_data[i];
		}
		delete[] this->m_data;
	}
	this->m_size = nsize;
	this->m_data = ndata;
}


template<typename T>
Array<T>::Array(T data[], int count)
{
	this->m_size = count;
	this->m_data = new T[this->m_size];
	for (int i = 0; i < this->m_size; i++){
		this->m_data[i] = data[i];
	}
}

template<typename T>
Array<T>::Array(T data[], int from, int count)
{
	this->m_size = count;
	this->m_data = new T[this->m_size];
	for (int i = 0; i < this->m_size; i++){
		this->m_data[i] = data[from+i];
	}
}

template<typename T>
Array<T>::~Array()
{
	if (this->m_data != NULL){
		this->m_size = 0;
		delete[] this->m_data;
		this->m_data = NULL;
	}
}

template<typename T>
Array<T>::Array(const Array<T> & arr)
{
	this->m_size = arr.m_size;
	this->m_data = new T[this->m_size];
	for (int i = 0; i < this->m_size; i++){
		this->m_data[i] = arr.m_data[i];
	}
}

template<typename T>
Array<T>::Array(Array<T> && arr)
{
	this->m_size = arr.m_size;
	this->m_data = arr.m_data;
	arr.m_size = 0;
	arr.m_data = NULL;
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T> & arr)
{
	this->m_size = arr.m_size;
	this->m_data = new T[this->m_size];
	for (int i = 0; i < this->m_size; i++){
		this->m_data[i] = arr.m_data[i];
	}
	return *this;
}

template<typename T>
Array<T>& Array<T>::operator=(Array<T> && arr)
{
	this->m_size = arr.m_size;
	this->m_data = arr.m_data;
	arr.m_size = 0;
	arr.m_data = NULL;
	return *this;
}

template<typename T>
T& Array<T>::get(int index)
{
	return this->m_data[index];
}

template<typename T>
T& Array<T>::operator[] (int index)
{
	return this->m_data[index];
}

template<typename T>
void Array<T>::set(int index,const T& val)
{
	this->m_data[index] = val;
}

template<typename T>
T* Array<T>::data()
{
	return this->m_data;
}

template<typename T>
int Array<T>::size()
{
	return this->m_size;
}

template<typename T>
void Array<T>::resize(int size)
{
	T * ndata = new T[size];
	for (int i = 0; i < size && i<this->m_size; i++){
		ndata[i] = this->m_data[i];
	}
	if (this->m_data != NULL){
		delete[] this->m_data;
	}
	this->m_data = ndata;
	this->m_size = size;
}

template<typename T>
void Array<T>::each(IExecutor<T>& executor)
{
	for (int i = 0; i < this->m_size; i++){
		executor.execute(this->m_data[i]);
	}
}

template<typename T>
void Array<T>::of(T data[], int count)
{
	this->of(data, 0, count);
}

template<typename T>
void Array<T>::of(T data[], int from, int count)
{
	this->m_size = count;
	if (this->m_data != NULL){
		delete this->m_data;
	}
	this->m_data = new T[this->m_size];
	for (int i = 0; i < this->m_size; i++){
		this->m_data[i] = data[from + i];
	}
}

template<typename T>
void Array<T>::of(List<T>& list)
{
	this->of(list, 0, list.size());
}

template<typename T>
void Array<T>::of(List<T>& list, int from, int count)
{
	this->m_size = count;
	if (this->m_data != NULL){
		delete this->m_data;
	}
	this->m_data = new T[this->m_size];
	for (int i = 0; i < this->m_size; i++){
		this->m_data[i] = list.get(from+i);
	}
}

#endif // _I2F_ARRAY_H_
