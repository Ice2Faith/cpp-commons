#ifndef _I2F_MATRIX_2_H_
#define _I2F_MATRIX_2_H_
#include"Array.hpp"

template<typename T>
class Matrix2
{
private:
	int m_width;
	int m_height;
	T* m_data;
	int flat(int x, int y);
public:
	Matrix2();
	virtual ~Matrix2();
	Matrix2(T * arr, int count);
	Matrix2(T * map, int width, int height);
	Matrix2(const Matrix2<T>& mtx);
	Matrix2(Matrix2<T> && mtx);
	Matrix2<T>& operator=(const Matrix2<T>& mtx);
	Matrix2<T>& operator=(Matrix2<T> && mtx);
	Matrix2(int width, int height);
	virtual int width();
	virtual int height();
	virtual int count();
	virtual T& get(int offset);
	virtual bool isEmpty();
	virtual T& get(int x, int y);
	virtual void set(int x, int y, const T& val);
	virtual Array<T> row(int y);
	virtual Array<T> col(int x);
	virtual void row(int y, Array<T> row);
	virtual void col(int x, Array<T> col);
	virtual void fill(const T& val);
};

template<typename T>
Matrix2<T>::Matrix2()
{
	this->m_width = 0;
	this->m_height = 0;
	this->m_data = NULL;
}

template<typename T>
Matrix2<T>::Matrix2(T * arr, int count)
{
	this->m_height = 1;
	this->m_width = count;
	this->m_data = new T[this->m_width * this->m_height];
	for (int i = 0; i < this->m_width; i++){
		this->m_data[i] = arr[i];
	}
}

template<typename T>
Matrix2<T>::Matrix2(T * map, int width, int height)
{
	this->m_height = height;
	this->m_width = width;
	this->m_data = new T[this->m_width * this->m_height];
	for (int i = 0; i < this->m_width; i++){
		for (int j = 0; j < this->m_height; j++){
			this->m_data[this->flat(i, j)] = map[this->flat(i, j)];
		}
	}
}

template<typename T>
Matrix2<T>::~Matrix2()
{
	if (this->m_data != NULL){
		delete[] this->m_data;
		this->m_data = NULL;
	}
	this->m_width = 0;
	this->m_height = 0;
	this->m_data = NULL;
}

template<typename T>
Matrix2<T>::Matrix2(const Matrix2<T>& mtx)
{
	this->m_width = mtx.m_width;
	this->m_height = mtx.m_height;
	int count = this->m_width * this->m_height;
	this->m_data = new T[count];
	for (int i = 0; i < count; i++){
		this->m_data[i] = mtx.m_data[i];
	}
}

template<typename T>
Matrix2<T>::Matrix2(Matrix2<T> && mtx)
{
	this->m_width = mtx.m_width;
	this->m_height = mtx.m_height;
	this->m_data = mtx->m_data;
	mtx.m_width = 0;
	mtx.m_height = 0;
	mtx.m_data = NULL;
}

template<typename T>
Matrix2<T>& Matrix2<T>::operator=(const Matrix2<T>& mtx)
{
	this->m_width = mtx.m_width;
	this->m_height = mtx.m_height;
	int count = this->m_width * this->m_height;
	this->m_data = new T[count];
	for (int i = 0; i < count; i++){
		this->m_data[i] = mtx.m_data[i];
	}
	return *this;
}

template<typename T>
Matrix2<T>& Matrix2<T>::operator=(Matrix2<T> && mtx)
{
	this->m_width = mtx.m_width;
	this->m_height = mtx.m_height;
	this->m_data = mtx->m_data;
	mtx.m_width = 0;
	mtx.m_height = 0;
	mtx.m_data = NULL;
	return *this;
}

template<typename T>
Matrix2<T>::Matrix2(int width, int height)
{
	this->m_width = width;
	this->m_height = height;
	this->m_data = new T[this->m_width * this->m_height];
}

template<typename T>
int Matrix2<T>::flat(int x, int y)
{
	return y*this->m_width + x;
}

template<typename T>
int Matrix2<T>::width()
{
	return this->m_width;
}

template<typename T>
int Matrix2<T>::height()
{
	return this->m_height;
}

template<typename T>
int Matrix2<T>::count()
{
	return this->m_width * this->m_height;
}

template<typename T>
T& Matrix2<T>::get(int offset)
{
	return this->m_data[offset];
}

template<typename T>
bool Matrix2<T>::isEmpty()
{
	return this->m_height == 0 && this->m_width == 0;
}

template<typename T>
T& Matrix2<T>::get(int x, int y)
{
	return this->m_data[this->flat(x,y)];
}

template<typename T>
void Matrix2<T>::set(int x, int y, const T& val)
{
	this->m_data[this->flat(x, y)] = val;
}

template<typename T>
Array<T> Matrix2<T>::row(int y)
{
	Array<T> arr(this->m_width);
	for (int i = 0; i < this->m_width; i++){
		arr[i] = this->m_data[flat(i,y)];
	}
	return arr;
}

template<typename T>
Array<T> Matrix2<T>::col(int x)
{
	Array<T> arr(this->m_height);
	for (int i = 0; i < this->m_height; i++){
		arr[i] = this->m_data[flat(x, i)];
	}
	return arr;
}

template<typename T>
void Matrix2<T>::row(int y, Array<T> row)
{
	for (int i = 0; i < this->m_width && i<row.size(); i++){
		this->m_data[flat(i, y)]=row[i] ;
	}
}

template<typename T>
void Matrix2<T>::col(int x, Array<T> col)
{
	for (int i = 0; i < this->m_height && i<col.size(); i++){
		this->m_data[flat(x, i)]=col[i] ;
	}
}

template<typename T>
void Matrix2<T>::fill(const T& val)
{
	for (int i = 0; i < this->m_width; i++)
	{
		for (int j = 0; j < this->m_height; j++){
			this->m_data[this->flat(i, j)] = val;
		}
	}
}

#endif // _I2F_MATRIX_2_H_