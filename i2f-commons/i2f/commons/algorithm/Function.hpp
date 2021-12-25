#ifndef _I2F_FUNCTION_H_
#define _I2F_FUNCTION_H_
#include"../interface/IExecutor.h"
#include"../interface/IIterable.h"
#include"../interface/IIterator.h"
#include"../interface/IComparator.h"
#include"../interface/impl/AdaptExecutor.hpp"


class Function 
{
public:
	template<typename T>
	static void each(T arr[], int count, IExecutor<T>& exec);

	template<typename T>
	static void each(T arr[], int from, int count, IExecutor<T>& exec);

	template<typename T>
	static void each(IIterable<T>& it, IExecutor<T>& exec);

	template<typename T>
	static void each(IIterator<T>* it, IExecutor<T>& exec);

	template<typename T>
	static T min(T arr[], int count, IComparator<T>& cmp);

	template<typename T>
	static T min(T arr[], int from, int count, IComparator<T>& cmp);

	template<typename T>
	static T min(IIterable<T>& it, IComparator<T>& cmp);

	template<typename T>
	static T min(IIterator<T>* it, IComparator<T>& cmp);

	template<typename T>
	static T max(T arr[], int count, IComparator<T>& cmp);

	template<typename T>
	static T max(T arr[], int from, int count, IComparator<T>& cmp);

	template<typename T>
	static T max(IIterable<T>& it, IComparator<T>& cmp);

	template<typename T>
	static T max(IIterator<T>* it, IComparator<T>& cmp);

	template<typename T>
	static T avg(T arr[], int count);

	template<typename T>
	static T avg(T arr[], int from, int count);

	template<typename T>
	static T avg(IIterable<T>& it);

	template<typename T>
	static T avg(IIterator<T>* it);

	template<typename T>
	static T sum(T arr[], int count);

	template<typename T>
	static T sum(T arr[], int from, int count);

	template<typename T>
	static T sum(IIterable<T>& it);

	template<typename T>
	static T sum(IIterator<T>* it);

};

template<typename T>
void Function::each(T arr[], int count, IExecutor<T>& exec)
{
	for (int i = 0; i < count; i++){
		exec.execute(arr[i]);
	}
}

template<typename T>
void Function::each(T arr[], int from, int count, IExecutor<T>& exec)
{
	for (int i = 0; i < count; i++){
		exec.execute(arr[from+i]);
	}
}

template<typename T>
void Function::each(IIterable<T>& it, IExecutor<T>& exec)
{
	it.each(exec);
}

template<typename T>
void Function::each(IIterator<T>* it, IExecutor<T>& exec)
{
	while (it->hasNext())
	{
		exec.execute(it->get());
		it->next();
	}
}


template<typename T>
T Function::min(T arr[], int count, IComparator<T>& cmp)
{
	T ret = arr[0];
	for (int i = 1; i < count; i++){
		if (cmp.compare(ret, arr[i]) < 0){
			ret = arr[i];
		}
	}
	return ret;
}

template<typename T>
T Function::min(T arr[], int from, int count, IComparator<T>& cmp)
{
	T ret = arr[from];
	for (int i = 1; i < count; i++){
		if (cmp.compare(ret, arr[from + i]) < 0){
			ret = arr[from + i];
		}
	}
	return ret;
}

template<typename T>
T Function::min(IIterable<T>& it, IComparator<T>& cmp)
{
	AdaptExecutor<T> adapter;
	it.each(adapter);
	IIterator<T>* itr = adapter.iterator();
	T ret = Function::min(itr, cmp);
	delete itr;
	return ret;
}

template<typename T>
T Function::min(IIterator<T>* it, IComparator<T>& cmp)
{
	T ret = it->next();
	while (it->hasNext()){
		T val = it->next();
		if (cmp.compare(ret, val)<0){
			ret = val;
		}
	}
	return ret;
}




template<typename T>
T Function::max(T arr[], int count, IComparator<T>& cmp)
{
	T ret = arr[0];
	for (int i = 1; i < count; i++){
		if (cmp.compare(ret, arr[i]) > 0){
			ret = arr[i];
		}
	}
	return ret;
}

template<typename T>
T Function::max(T arr[], int from, int count, IComparator<T>& cmp)
{
	T ret = arr[from];
	for (int i = 1; i < count; i++){
		if (cmp.compare(ret, arr[from + i]) > 0){
			ret = arr[from + i];
		}
	}
	return ret;
}

template<typename T>
T Function::max(IIterable<T>& it, IComparator<T>& cmp)
{
	AdaptExecutor<T> adapter;
	it.each(adapter);
	IIterator<T>* itr = adapter.iterator();
	T ret = Function::max(itr, cmp);
	delete itr;
	return ret;
}

template<typename T>
T Function::max(IIterator<T>* it, IComparator<T>& cmp)
{
	T ret = it->next();
	while (it->hasNext()){
		T val = it->next();
		if (cmp.compare(ret, val)>0){
			ret = val;
		}
	}
	return ret;
}

template<typename T>
T Function::avg(T arr[], int count)
{
	T ret = 0;
	for (int i = 1; i < count; i++){
		ret += arr[i];
	}
	return (T)(ret/count);
}

template<typename T>
T Function::avg(T arr[], int from, int count)
{
	T ret = 0;
	for (int i = 0; i < count; i++){
		ret += arr[from + i];
		
	}
	return (T)(ret/count);
}

template<typename T>
T Function::avg(IIterable<T>& it)
{
	AdaptExecutor<T> adapter;
	it.each(adapter);
	IIterator<T>* itr = adapter.iterator();
	T ret = Function::avg(itr);
	delete itr;
	return ret;
}

template<typename T>
T Function::avg(IIterator<T>* it)
{
	T ret = 0;
	int count = 0;
	while (it->hasNext()){
		ret += it->next();
		count++;
	}
	return (T)(ret/count);
}


template<typename T>
T Function::sum(T arr[], int count)
{
	T ret = 0;
	for (int i = 1; i < count; i++){
		ret += arr[i];
	}
	return (T)(ret);
}

template<typename T>
T Function::sum(T arr[], int from, int count)
{
	T ret = 0;
	for (int i = 0; i < count; i++){
		ret += arr[from + i];

	}
	return (T)(ret);
}

template<typename T>
T Function::sum(IIterable<T>& it)
{
	AdaptExecutor<T> adapter;
	it.each(adapter);
	IIterator<T>* itr = adapter.iterator();
	T ret = Function::sum(itr);
	delete itr;
	return ret;
}

template<typename T>
T Function::sum(IIterator<T>* it)
{
	T ret = 0;
	while (it->hasNext()){
		ret += it->next();
	}
	return (T)(ret);
}
#endif // _I2F_FUNCTION_H_
