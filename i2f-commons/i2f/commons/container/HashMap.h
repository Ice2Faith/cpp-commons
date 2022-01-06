#ifndef _I2F_HASH_MAP_H_
#define _I2F_HASH_MAP_H_

#include"Container.h"
#include"Map.h"


template<typename T,typename E>
class HashMapIterator;

/*
T 元素要求，实现IHashCode和IEquals
或者实现IHashEquals
*/
template<typename T,typename E>
class  HashMap : virtual public Map<T,E>, virtual public Container
{
private:
	//真实记录数据的容器，使用一个数组实现hash存储
	//内部元素使用数组解决hash值冲突
	ArrayList<ArrayList<Entry<T,E>>> m_data;
	//hash占用在容器中的位置
	int * m_map;
	//hash的总大小
	int m_capital;
	//总个数
	int m_size;
	//hash因子
	double m_factor;
	friend class HashMapIterator<T,E>;
	virtual int indexOfHash(int hash);
	virtual void createCleanMap();
public:
	HashMap();
	virtual ~HashMap();
	virtual void put( Entry<T,E>& val);
	virtual void put(const T& key,const E& val);
	virtual bool contains(const T& key);
	virtual E& get(const T& key);
	virtual void remove(const T& key);
	virtual void clear();
	virtual IIterator<Entry<T,E>>* iterator() ;
	virtual void autoCapitalReHash();
	virtual bool isEmpty();
};

template<typename T,typename E>
class HashMapIterator : virtual public IIterator<Entry<T,E>>
{
private:
	HashMap<T,E>* m_set;
	int m_map_idx;
	int m_list_idx;
public:
	HashMapIterator(HashMap<T,E>* set);
	virtual ~HashMapIterator();
	virtual bool hasNext();
	virtual Entry<T,E>& get();
	virtual void set(const Entry<T,E>& val);
	virtual Entry<T,E> next();
};

template<typename T,typename E>
HashMapIterator<T,E>::HashMapIterator(HashMap<T,E>* st)
{
	this->m_set = st;
	this->m_map_idx = 0;
	this->m_list_idx = 0;
}

template<typename T,typename E>
HashMapIterator<T,E>::~HashMapIterator()
{
	this->m_map_idx = 0;
	this->m_list_idx = 0;
}

template<typename T,typename E>
bool HashMapIterator<T,E>::hasNext()
{
	int mapSize = this->m_set->m_data.size();
	int mapChildSize = (this->m_set->m_data.get(this->m_map_idx)).size();
	return this->m_map_idx < mapSize
		|| this->m_list_idx < mapChildSize;
}

template<typename T,typename E>
Entry<T,E>& HashMapIterator<T,E>::get()
{
	return (this->m_set->m_data.get(this->m_map_idx)).get(this->m_list_idx);
}

template<typename T,typename E>
void HashMapIterator<T,E>::set(const Entry<T,E>& val)
{
	Entry<T, E> pval = val;
	this->m_set->put(pval);
}

template<typename T,typename E>
Entry<T,E> HashMapIterator<T,E>::next()
{
	Entry<T,E> ret = this->get();
	this->m_list_idx++;
	if (this->m_list_idx >= (this->m_set->m_data.get(this->m_map_idx).size())){
		this->m_map_idx++;
		this->m_list_idx = 0;
	}
	return ret;
}

template<typename T,typename E>
HashMap<T,E>::HashMap()
{
	this->m_capital = 32;
	this->m_factor = 0.75;
	this->m_map = NULL;
	this->createCleanMap();
}

template<typename T,typename E>
HashMap<T,E>::~HashMap()
{
	if (this->m_map != NULL){
		delete[] this->m_map;
	}
	this->m_map = NULL;
	this->m_capital = 0;
	this->m_size = 0;
	this->m_factor = 0.75;
}

template<typename T,typename E>
int HashMap<T,E>::indexOfHash(int hash)
{
	double dhash = hash;
	while (dhash < this->m_capital){
		dhash = (dhash * 31.0 / 7);
	}
	hash = (int)dhash;
	return ((unsigned int)(hash)) % this->m_capital;
}

template<typename T,typename E>
void HashMap<T,E>::createCleanMap()
{
	if (this->m_map != NULL){
		delete[] this->m_map;
	}
	this->m_map = new int[this->m_capital];
	for (int i = 0; i < this->m_capital; i++){
		this->m_map[i] = -1;
	}
}

template<typename T,typename E>
bool HashMap<T,E>::isEmpty()
{
	return this->m_size == 0;
}

template<typename T,typename E>
void HashMap<T,E>::put( Entry<T,E>& val)
{
	T k = val.gkey();
	E v = val.gval();
    this->put(k,v);
}

template<typename T,typename E>
void HashMap<T,E>::put(const T& key,const E& val)
{
	IHashCode& hash = (IHashCode&)key;
	int code = hash.hashcode();
	int idx = this->indexOfHash(code);
	if (this->m_map[idx] < 0){
		ArrayList<Entry<T,E>> arr;
		Entry<T,E> e(key,val);
		arr.add(e);
		this->m_map[idx] = this->m_data.size();
		this->m_data.add(arr);
		this->m_size++;
		this->autoCapitalReHash();
	}
	else{
		bool processed = false;
		IEquals& eqsVal = (IEquals&)key;
		ArrayList<Entry<T,E>>& arr = this->m_data.get(this->m_map[idx]);
		for (int i = 0; i < arr.size(); i++){
			IEquals& eqsItem = (IEquals&)arr.get(i).key();
			if (eqsItem.equals(eqsVal)){
			    arr.get(i).val(val);
				processed = true;
				break;
			}
		}
		if (!processed){
			Entry<T, E> e(key, val);
			(this->m_data.get(idx)).add(e);
			this->m_size++;
			this->autoCapitalReHash();
		}
	}


}

template<typename T,typename E>
bool HashMap<T,E>::contains(const T& key)
{
	IHashCode& hash = (IHashCode&)key;
	int code = hash.hashcode();
	int idx = this->indexOfHash(code);
	if (this->m_map[idx] < 0){
		return false;
	}
	IEquals& eqsVal = (IEquals&)key;
	ArrayList<Entry<T,E>> arr = this->m_data.get(this->m_map[idx]);
	for (int i = 0; i < arr.size(); i++){
		IEquals& eqsItem = (IEquals&)arr.get(i).key();
		if (eqsItem.equals(eqsVal)){
			return true;
		}
	}
	return false;
}

template<typename T,typename E>
E& HashMap<T,E>::get(const T& key)
{
    IHashCode& hash = (IHashCode&)key;
    int code = hash.hashcode();
    int idx = this->indexOfHash(code);
    ArrayList<Entry<T,E>>& loc=this->m_data.get(this->m_map[idx]);
    IEquals& ke=(IEquals&)key;
    for(int i=0;i<loc.size();i++){
        Entry<T,E>& e=loc.get(i);
        IEquals& kt=(IEquals&)e.key();
        if(ke.equals(kt)){
            return e.val();
        }
    }
    return E();
}

template<typename T,typename E>
void HashMap<T,E>::remove(const T& key)
{
    IHashCode& hash = (IHashCode&)key;
    int code = hash.hashcode();
    int idx = this->indexOfHash(code);
    ArrayList<Entry<T,E>>& loc=this->m_data.get(this->m_map[idx]);
    IEquals& ke=(IEquals&)key;
    for(int i=0;i<loc.size();i++){
        Entry<T,E>& e=loc.get(i);
        IEquals& kt=(IEquals&)e.key();
        if(ke.equals(kt)){
            loc.remove(i);
			this->m_size--;
			if (loc.size() == 0){
				int ridx = this->m_map[idx];
				this->m_map[idx] = -1;
				this->m_data.remove(ridx);
				for (int j = 0; j < this->m_capital; j++){
					if (this->m_map[j] >= ridx){
						this->m_map[j]--;
					}
				}
				
			}
            break;
        }
    }
}

template<typename T,typename E>
void HashMap<T,E>::clear()
{
    this->m_data= ArrayList<ArrayList<Entry<T,E>>>();
    this->m_size=0;
    this->createCleanMap();
}

template<typename T,typename E>
IIterator<Entry<T,E>>* HashMap<T,E>::iterator()
{
	return new HashMapIterator<T,E>(this);
}

template<typename T,typename E>
void HashMap<T,E>::autoCapitalReHash()
{
	int ncap=(int)(this->m_size / this->m_factor);
	if (this->m_capital < ncap){
		ArrayList<Entry<T,E>> sumData;
		for (int i = 0; i < this->m_data.size(); i++){
			for (int j = 0; j < this->m_data.get(i).size(); j++){
				sumData.add((this->m_data.get(i)).get(j));
			}
		}
		this->m_data=ArrayList<ArrayList<Entry<T,E>>>();
		this->m_capital = ncap;
		this->m_size = 0;
		this->createCleanMap();
		for (int i = 0; i < sumData.size(); i++){
			this->put(sumData.get(i));
		}
	}
}

#endif // _I2F_HASH_MAP_H_
