#ifndef _I2F_ARRAY_LIST_H_
#define _I2F_ARRAY_LIST_H_
#include"MultiList.h"

template<typename T>
class ArrayListIterator;

template<typename T>
class ArrayList : virtual  public MultiList<T>
{
private:
	int m_capital;
	int m_size;
	T * m_data;
private:
	friend class ArrayListIterator<T>;
	
public:
	ArrayList();
	ArrayList(int initCapital);
	~ArrayList();

	ArrayList(const ArrayList<T> & arr);

	ArrayList(ArrayList<T> && arr);

	ArrayList<T>& operator=(const ArrayList<T> & arr);

	ArrayList<T>& operator=(ArrayList<T> && arr);

	void autoCapital(int requireSize);

	ArrayList& recapital(int capital);
	ArrayList& resize(int size);

	int capital();

	virtual T& get(int index) ;

	virtual void add(const T& val) ;
	virtual void addAll(T * arr, int count);
	virtual void addAll(T * arr, int from, int count);
	virtual void addAll(List<T>& list);
	virtual void addAll(List<T>& list, int from, int count);

	virtual T remove(int index) ;
	virtual void set(int index,const T& val);
	virtual void insert(int index,const T& val);

	virtual int size();
	virtual bool isEmpty() ;


	virtual void clear() ;

	virtual T& first();
	virtual T& last();

	virtual T removeFirst();
	virtual T removeLast();

	virtual void addFirst(const T& val);
	virtual void addLast(const T& val);

	virtual void each(IExecutor<T>& executor);

	virtual ListIterator<T>* iterator();

	virtual void enque(const T& val);
	virtual T deque();
	virtual T& head();
	virtual T& tail();

	virtual void push(const T& val);
	virtual T pop() ;
	virtual T& top() ;
};

template<typename T>
class ArrayListIterator : virtual public ListIterator<T>
{
private:
	ArrayList<T> * m_list;
	int m_index;
public:
	ArrayListIterator(ArrayList<T> * list){
		this->m_list = list;
		this->m_index = 0;
	}
	virtual ~ArrayListIterator(){

	}
	virtual bool hasNext(){
		return this->m_index < this->m_list->m_size;
	}
	virtual T& get(){
		return this->m_list->m_data[this->m_index];
	}
	virtual T next(){
		T rv = this->m_list->m_data[this->m_index];
		this->m_index++;
		return rv;
	}
	virtual T remove(){
		return this->m_list->remove(this->m_index);
	}
	virtual void insert(T& val){
		this->m_list->insert(this->m_index, val);
		this->m_index++;
	}
};

template<typename T>
ListIterator<T>* ArrayList<T>::iterator()
{
	return new ArrayListIterator<T>(this);
}

template<typename T>
ArrayList<T>::ArrayList()
{
	this->m_size = 0;
	this->autoCapital(32);
}

template<typename T>
ArrayList<T>::~ArrayList()
{
	if (this->m_data != NULL){
		delete[] this->m_data;
		this->m_data = NULL;
		this->m_size = 0;
		this->m_capital = 0;
	}
}


template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T> & arr)
{
	this->autoCapital(arr.m_size);
	this->m_size = arr.m_size;
	for (int i = 0; i < this->m_size; i++){
		this->m_data[i] = arr.m_data[i];
	}
}

template<typename T>
ArrayList<T>::ArrayList(ArrayList<T> && arr)
{
	this->m_capital = arr.m_capital;
	this->m_size = arr.m_size;
	this->m_data = arr.m_data;
	arr.m_capital = 0;
	arr.m_size = 0;
	arr.m_data = NULL;
}

template<typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T> & arr)
{
	this->autoCapital(arr.m_size);
	this->m_size = arr.m_size;
	for (int i = 0; i < this->m_size; i++){
		this->m_data[i] = arr.m_data[i];
	}
	return *this;
}

template<typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList<T> && arr)
{
	this->m_capital = arr.m_capital;
	this->m_size = arr.m_size;
	this->m_data = arr.m_data;
	arr.m_capital = 0;
	arr.m_size = 0;
	arr.m_data = NULL;
	return *this;
}

template<typename T>
ArrayList<T>::ArrayList(int initCapital)
{
	this->m_size = 0;
	this->autoCapital(initCapital);
}

template<typename T>
int ArrayList<T>::capital()
{
	return this->m_capital;
}

template<typename T>
void ArrayList<T>::autoCapital(int requireSize)
{
	if (requireSize > this->m_capital){
		int ncap = 2;
		while (ncap < requireSize){
			ncap <<= 1;
		}
		this->recapital(ncap);
	}
}

template<typename T>
ArrayList<T>& ArrayList<T>::resize(int size)
{
	if (size < this->m_size && size >= 0)
	{
		this->m_size = size;
	}
	return *this;
}

template<typename T>
ArrayList<T>& ArrayList<T>::recapital(int capital)
{
	if (capital >= 0){
		T * ndata = new T[capital];
		int size = 0;
		for (int i = 0; i < this->m_size && i < capital; i++, size++){
			ndata[i] = this->m_data[i];
		}
		this->m_data = ndata;
		this->m_capital = capital;
		this->m_size = size;
	}
	return *this;
}

template<typename T>
T& ArrayList<T>::get(int index)
{
	return this->m_data[index];
}

template<typename T>
void ArrayList<T>::add(const T& val)
{
	this->autoCapital(this->m_size + 1);
	this->m_data[this->m_size] = val;
	this->m_size++;
}

template<typename T>
void ArrayList<T>::addAll(T * arr, int count)
{
	this->autoCapital(this->m_size + count);
	for (int i = 0; i < count; i++){
		this->m_data[this->m_size++] = arr[i];
	}
}

template<typename T>
void ArrayList<T>::addAll(T * arr, int from, int count)
{
	this->autoCapital(this->m_size + count);
	for (int i = 0; i < count; i++){
		this->m_data[this->m_size++] = arr[from + i];
	}
}

template<typename T>
void ArrayList<T>::addAll(List<T>& list)
{
	int psize = list.size();
	this->autoCapital(this->m_size + psize);
	for (int i = 0; i < psize; i++){
		this->m_data[this->m_size++] = list.get(i);
	}
}

template<typename T>
void ArrayList<T>::addAll(List<T>& list, int from, int count)
{
	int psize = list.size();
	if (count<0){
		count = psize - from;
	}
	int msize = from + count;
	if (msize>psize){
		psize = psize - from;
	}
	else{
		psize = count;
	}
	this->autoCapital(this->m_size + psize);
	for (int i = 0; i < psize; i++){
		this->m_data[this->m_size++] = list.get(from + i);
	}
}

template<typename T>
T ArrayList<T>::remove(int index)
{
	T rv = this->m_data[index];
	for (int i = index + 1; i < this->m_size; i++){
		this->m_data[i - 1] = this->m_data[i];
	}
	this->m_size--;
	return rv;
}

template<typename T>
void ArrayList<T>::set(int index,const T& val)
{
	if (index < 0){
		this->insert(0, val);
		return;
	}
	if (index>this->m_size){
		this->add(val);
		return;
	}
	this->m_data[index] = val;
}

template<typename T>
void ArrayList<T>::insert(int index,const T& val)
{
	if (index < 0){
		index = 0;
	}
	if (index >= this->m_size){
		this->add(val);
		return;
	}
	this->autoCapital(this->m_size + 1);
	for (int i = this->m_size; i>index; i--){
		this->m_data[i] = this->m_data[i - 1];
	}
	this->m_data[index] = val;
	this->m_size++;
}

template<typename T>
int ArrayList<T>::size()
{
	return this->m_size;
}

template<typename T>
bool ArrayList<T>::isEmpty()
{
	return this->m_size == 0;
}

template<typename T>
void ArrayList<T>::clear()
{
	this->m_size = 0;
}

template<typename T>
T& ArrayList<T>::first()
{
	return this->m_data[0];
}

template<typename T>
T& ArrayList<T>::last()
{
	return this->m_data[this->m_size - 1];
}

template<typename T>
T ArrayList<T>::removeFirst()
{
	return this->remove(0);
}

template<typename T>
T ArrayList<T>::removeLast()
{
	return this->remove(this->m_size - 1);
}

template<typename T>
void ArrayList<T>::addFirst(const T& val)
{
	this->insert(0, val);
}

template<typename T>
void ArrayList<T>::addLast(const T& val)
{
	this->add(val);
}

template<typename T>
void ArrayList<T>::each(IExecutor<T>& executor)
{
	for (int i = 0; i < this->m_size; i++){
		executor.execute(this->m_data[i]);
	}
}

template<typename T>
void ArrayList<T>::enque(const T& val)
{
	this->add(val);
}

template<typename T>
T ArrayList<T>::deque()
{
	return this->remove(0);
}

template<typename T>
T& ArrayList<T>::head()
{
	return this->m_data[0];
}

template<typename T>
T& ArrayList<T>::tail()
{
	return this->m_data[this->m_size - 1];
}

template<typename T>
void ArrayList<T>::push(const T& val)
{
	this->add(val);
}

template<typename T>
T ArrayList<T>::pop()
{
	return this->remove(this->m_size - 1);
}

template<typename T>
T& ArrayList<T>::top()
{
	return this->m_data[this->m_size - 1];
}
#endif // _I2F_ARRAY_LIST_H_
