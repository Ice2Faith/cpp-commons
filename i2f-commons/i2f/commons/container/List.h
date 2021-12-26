#ifndef _I2F_LIST_H_
#define _I2F_LIST_H_
#include"../interface/IIterable.h"
#include"../interface/IIterator.h"
#include"Container.h"

template<typename T>
class ListIterator : virtual public IIterator<T>
{
public:
	virtual ~ListIterator(){}
	virtual T remove() = 0;
	virtual void insert(T& val) = 0;
};

template<typename T>
class List : virtual public IIterable<T> , virtual public Container
{
public:
	virtual ~List(){}

	virtual T& get(int index) = 0;

	virtual void add(const T& val) = 0;
	virtual void addAll(T * arr, int count) = 0;
	virtual void addAll(T * arr, int from, int count) = 0;
	virtual void addAll(List<T>& list) = 0;
	virtual void addAll(List<T>& list, int from, int count) = 0;

	virtual T remove(int index) = 0;
	virtual void set(int index,const T& val) = 0;
	virtual void insert(int index,const T& val) = 0;

	virtual int size() = 0;
	
	virtual void clear() = 0;

	virtual T& first() = 0;
	virtual T& last() = 0;

	virtual T removeFirst() = 0;
	virtual T removeLast() = 0;

	virtual void addFirst(const T& val) = 0;
	virtual void addLast(const T& val) = 0;

	virtual ListIterator<T>* iterator() = 0;


};

#endif // _I2F_LIST_H_
