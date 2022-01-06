#ifndef _I2F_HASH_SET_H_
#define _I2F_HASH_SET_H_

#include"Set.h"
#include"Container.h"
#include"../interface/IHashCode.h"
#include"../interface/IEquals.h"
#include"ArrayList.hpp"

template<typename T>
class HashSetIterator;

/*
T 元素要求，实现IHashCode和IEquals
或者实现IHashEquals
*/
template<typename T>
class  HashSet : virtual public Set<T>, virtual public Container
{
private:
	//真实记录数据的容器，使用一个数组实现hash存储
	//内部元素使用数组解决hash值冲突
	ArrayList<ArrayList<T>> m_data;
	//hash占用在容器中的位置
	int * m_map;
	//hash的总大小
	int m_capital;
	//总个数
	int m_size;
	//hash因子
	double m_factor;
	friend class HashSetIterator<T>;
	virtual int indexOfHash(int hash);
	virtual void createCleanMap();
public:
	HashSet();
	virtual ~HashSet();
	virtual void put(const T& val);
	virtual bool contains(const T& val);
	virtual IIterator<T>* iterator() ;
	virtual void autoCapitalReHash();
	virtual bool isEmpty();
};

template<typename T>
class HashSetIterator : virtual public IIterator<T>
{
private:
	HashSet<T>* m_set;
	int m_map_idx;
	int m_list_idx;
public:
	HashSetIterator(HashSet<T>* set);
	virtual ~HashSetIterator();
	virtual bool hasNext();
	virtual T& get();
	virtual void set(const T& val);
	virtual T next();
};

template<typename T>
HashSetIterator<T>::HashSetIterator(HashSet<T>* st)
{
	this->m_set = st;
	this->m_map_idx = 0;
	this->m_list_idx = 0;
}

template<typename T>
HashSetIterator<T>::~HashSetIterator()
{
	this->m_map_idx = 0;
	this->m_list_idx = 0;
}

template<typename T>
bool HashSetIterator<T>::hasNext()
{
	int mapSize = this->m_set->m_data.size();
	int mapChildSize = (this->m_set->m_data.get(this->m_map_idx)).size();
	return this->m_map_idx < mapSize 
		|| this->m_list_idx < mapChildSize;
}

template<typename T>
T& HashSetIterator<T>::get()
{
	return (this->m_set->m_data.get(this->m_map_idx)).get(this->m_list_idx);
}

template<typename T>
void HashSetIterator<T>::set(const T& val)
{
	this->m_set->put(val);
}

template<typename T>
T HashSetIterator<T>::next()
{
	T ret = this->get();
	this->m_list_idx++;
	if (this->m_list_idx >= (this->m_set->m_data.get(this->m_map_idx).size())){
		this->m_map_idx++;
		this->m_list_idx = 0;
	}
	return ret;
}

template<typename T>
HashSet<T>::HashSet()
{
	this->m_capital = 32;
	this->m_factor = 0.75;
	this->m_map = NULL;
	this->createCleanMap();
}

template<typename T>
HashSet<T>::~HashSet()
{
	if (this->m_map != NULL){
		delete[] this->m_map;
	}
	this->m_map = NULL;
	this->m_capital = 0;
	this->m_size = 0;
	this->m_factor = 0.75;
}

template<typename T>
int HashSet<T>::indexOfHash(int hash)
{
	double dhash = hash;
	while (dhash < this->m_capital){
		dhash = (dhash * 31.0 / 7);
	}
	hash = (int)dhash;
	return ((unsigned int)(hash)) % this->m_capital;
}

template<typename T>
void HashSet<T>::createCleanMap()
{
	if (this->m_map != NULL){
		delete[] this->m_map;
	}
	this->m_map = new int[this->m_capital];
	for (int i = 0; i < this->m_capital; i++){
		this->m_map[i] = 0;
	}
}

template<typename T>
bool HashSet<T>::isEmpty()
{
	return this->m_size == 0;
}

template<typename T>
void HashSet<T>::put(const T& val)
{
	IHashCode& hash = (IHashCode&)val;
	int code = hash.hashcode();
	int idx = this->indexOfHash(code);
	if (this->m_map[idx] == 0){
		ArrayList<T> arr;
		arr.add(val);
		this->m_data.add(arr);
		this->m_map[idx] = this->m_data.size();
		this->m_size++;
		this->autoCapitalReHash();
	}
	else{
		IEquals& eqsVal = (IEquals&)val;
		ArrayList<T>& arr = this->m_data.get(idx);
		for (int i = 0; i < arr.size(); i++){
			IEquals& eqsItem = (IEquals&)arr.get(i);
			if (eqsItem.equals(eqsVal)){
				return;
			}
		}
		(this->m_data.get(idx)).add(val);
		this->m_map[idx] = this->m_data.size();
		this->m_size++;
		this->autoCapitalReHash();
	}

}

template<typename T>
bool HashSet<T>::contains(const T& val)
{
	IHashCode& hash = (IHashCode&)val;
	int code = hash.hashcode();
	int idx = this->indexOfHash(code);
	if (this->m_map[idx] != 1){
		return false;
	}
	IEquals& eqsVal = (IEquals&)val;
	ArrayList<T> arr = this->m_data.get(idx);
	for (int i = 0; i < arr.size(); i++){
		IEquals& eqsItem = (IEquals&)arr.get(i);
		if (eqsItem.equals(eqsVal)){
			return true;
		}
	}
	return false;
}

template<typename T>
IIterator<T>* HashSet<T>::iterator()
{
	return new HashSetIterator<T>(this);
}

template<typename T>
void HashSet<T>::autoCapitalReHash()
{
	int ncap=(int)(this->m_size / this->m_factor);
	if (this->m_capital < ncap){
		ArrayList<T> sumData;
		for (int i = 0; i < this->m_data.size(); i++){
			for (int j = 0; j < this->m_data.get(i).size(); j++){
				sumData.add((this->m_data.get(i)).get(j));
			}
		}
		this->m_data=ArrayList<ArrayList<T>>();
		this->m_capital = ncap;
		this->m_size = 0;
		this->createCleanMap();
		for (int i = 0; i < sumData.size(); i++){
			this->put(sumData.get(i));
		}
	}
}

#endif // _I2F_HASH_SET_H_
