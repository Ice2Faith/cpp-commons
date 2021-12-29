#ifndef _I2F_LINK_LIST_H_
#define _I2F_LINK_LIST_H_
#include"MultiList.h"
#include"../data/DoubleListNode.hpp"

template<typename T>
class LinkListIterator;

template<typename T>
class LinkList : virtual  public MultiList<T>
{
private:
	DoubleListNode<T> * m_head;
	DoubleListNode<T> * m_tail;
	int m_size;

	DoubleListNode<T> * findNode(int index);
	friend class LinkListIterator<T>;
public:
	LinkList();
	~LinkList();

	LinkList(const LinkList<T> & arr);

	LinkList(LinkList<T> && arr);

	LinkList<T>& operator=(const LinkList<T> & arr);

	LinkList<T>& operator=(LinkList<T> && arr);

	virtual T& get(int index);

	virtual void add(const T& val);
	virtual void addAll(T * arr, int count);
	virtual void addAll(T * arr, int from, int count);
	virtual void addAll(List<T>& list);
	virtual void addAll(List<T>& list, int from, int count);

	virtual T remove(int index);
	virtual void set(int index, const T& val);
	virtual void insert(int index,const  T& val);

	virtual int size();
	virtual bool isEmpty();


	virtual void clear();

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
	virtual T pop();
	virtual T& top();

	virtual void tail2Head();
	virtual void head2Tail();
	virtual void swapHeadTail();
};

template<typename T>
class LinkListIterator : virtual public ListIterator<T>
{
private:
	LinkList<T> * m_list;
	DoubleListNode<T> * m_node;
public:
	LinkListIterator(LinkList<T> * list){
		this->m_list = list;
		this->m_node = this->m_list->m_head;
	}
	virtual bool hasNext(){
		return this->m_node != NULL;
	}
	virtual T& get(){
		return this->m_node->get();
	}
	virtual void set(const T& val){
		this->m_node->set(val);
	}
	virtual T next(){
		T rv = this->m_node->get();
		this->m_node = this->m_node->nextNode();
		return rv;
	}
	virtual T remove(){
		T rv = this->m_node->get();
		if (this->m_node->hasPrevious())
		{
			if (this->m_node->hasNext()){
				this->m_node->nextNode()->previousNode(this->m_node->previousNode());
			}
			this->m_node->previousNode()->nextNode(this->m_node->nextNode());
			DoubleListNode<T> * node = this->m_node;
			this->m_node = this->m_node->nextNode();
			delete node;
			
			this->m_list->m_size--;
		}
		else{
			this->m_list->removeFirst();
		}
		return rv;
	}
	virtual void insert(T& val){
		if (this->m_node->hasPrevious()){
			DoubleListNode<T> * node = new DoubleListNode<T>(val);
			this->m_node->linkPrevious(node);
			this->m_list->m_size++;
		}
		else{
			this->m_list->addFirst(val);
		}
	}
};


template<typename T>
ListIterator<T>* LinkList<T>::iterator()
{
	return new LinkListIterator<T>(this);
}

template<typename T>
LinkList<T>::LinkList()
{
	this->m_size = 0;
	this->m_head = NULL;
	this->m_tail = this->m_head;
}

template<typename T>
LinkList<T>::~LinkList()
{
	this->clear();
}

template<typename T>
LinkList<T>::LinkList(const LinkList<T> & arr)
{
	this->m_size = 0;
	this->m_head = NULL;
	this->m_tail = NULL;
	DoubleListNode<T> * node = arr.m_head;
	while (node != NULL){
		this->addLast(node->get());
		node = node->nextNode();
	}
}

template<typename T>
LinkList<T>::LinkList(LinkList<T> && arr)
{
	this->m_size = arr.m_size;
	this->m_head = arr.m_head;
	this->m_tail = arr.m_tail;
	arr.m_size = 0;
	arr.m_head = NULL;
	arr.m_tail = NULL;
}

template<typename T>
LinkList<T>& LinkList<T>::operator=(const LinkList<T> & arr)
{
	this->m_size = 0;
	this->m_head = NULL;
	this->m_tail = NULL;
	DoubleListNode<T> * node = arr.m_head;
	while (node != NULL){
		this->addLast(node->get());
		node = node->nextNode();
	}
	return *this;
}

template<typename T>
LinkList<T>& LinkList<T>::operator=(LinkList<T> && arr)
{
	this->m_size = arr.size;
	this->m_head = arr.m_head;
	this->m_tail = arr.m_tail;
	arr.m_size = 0;
	arr.m_head = NULL;
	arr.m_tail = NULL;
	return *this;
}

template<typename T>
T& LinkList<T>::get(int index)
{
	DoubleListNode<T> * fnode = this->findNode(index);
	return fnode->get();
}


template<typename T>
void LinkList<T>::add(const T& val)
{
	this->addLast(val);
}

template<typename T>
void LinkList<T>::addAll(T * arr, int count)
{
	for (int i = 0; i < count; i++){
		this->addLast(arr[i]);
	}
}

template<typename T>
void LinkList<T>::addAll(T * arr, int from, int count)
{
	for (int i = 0; i < count; i++){
		this->addLast(arr[from + i]);
	}
}

template<typename T>
void LinkList<T>::addAll(List<T>& list)
{
	int psize = list.size();
	for (int i = 0; i < psize; i++){
		this->addLast(list.get(i));
	}
}

template<typename T>
void LinkList<T>::addAll(List<T>& list, int from, int count)
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
	for (int i = 0; i < psize; i++){
		this->addLast(list.get(from + i));
	}
}

template<typename T>
T LinkList<T>::remove(int index)
{
	if (index == 0){
		T rv = this->m_head->get();
		DoubleListNode<T> * pnode = this->m_head;
		this->m_head = this->m_head->nextNode();
		delete pnode;
		this->m_size--;
		return rv;
	}
	else{
		DoubleListNode<T> * fnode = this->findNode(index);

		T rv = fnode->get();
		if (fnode->hasNext()){
			fnode->nextNode()->linkPrevious(fnode->previousNode());
		}
		delete fnode;
		this->m_size--;
		return rv;
	}
}

template<typename T>
void LinkList<T>::set(int index,const T& val)
{
	if (index <= 0){
		this->addFirst(val);
		return;
	}
	if (index >= this->m_size){
		this->addLast(val);
		return;
	}
	DoubleListNode<T> * fnode = this->findNode(index);
	if (fnode == NULL){
		this->addFirst(val);
	}
	else{
		fnode->set(val);
	}
}

template<typename T>
void LinkList<T>::insert(int index,const T& val)
{
	if (index <= 0){
		this->addFirst(val);
		return;
	}
	if (index >= this->m_size){
		this->addLast(val);
		return;
	}
	DoubleListNode<T> * fnode = this->findNode(index);
	if (fnode == NULL){
		this->addFirst(val);
	}
	else{
		DoubleListNode<T> * node = new DoubleListNode<T>(val);
		fnode->linkPrevious(node);
	}
}

template<typename T>
DoubleListNode<T> * LinkList<T>::findNode(int index)
{
	if (index<0 || index>this->m_size - 1 || this->m_head == NULL){
		return NULL;
	}
	DoubleListNode<T> * enode = this->m_tail;
	int eidx = this->m_size - 1;
	DoubleListNode<T> * snode = this->m_head;
	int sidx = 0;
	while (true){
		if (eidx == index){
			return enode;
		}
		if (sidx == index){
			return snode;
		}
		if (sidx >= eidx){
			break;
		}
		enode = enode->previousNode();
		snode = snode->nextNode();
		eidx--;
		sidx++;
	}
	return NULL;
}

template<typename T>
int LinkList<T>::size()
{
	return this->m_size;
}

template<typename T>
bool LinkList<T>::isEmpty()
{
	return this->m_head == NULL;
}

template<typename T>
void LinkList<T>::clear()
{
	if (this->m_head != NULL){
		DoubleListNode<T> * pnode = this->m_head;
		while (pnode != NULL){
			DoubleListNode<T> * nnode = pnode->nextNode();
			delete pnode;
			pnode = nnode;
		}
	}
	this->m_size = 0;
	this->m_head = NULL;
	this->m_tail = this->m_head;
}

template<typename T>
T& LinkList<T>::first()
{
	return this->m_head->get();
}

template<typename T>
T& LinkList<T>::last()
{
	return this->m_tail->get();
}

template<typename T>
T LinkList<T>::removeFirst()
{
	DoubleListNode<T> * node = this->m_head->nextNode();
	if (node == NULL){
		T rv = this->m_head->get();
		delete this->m_head;
		this->m_head = NULL;
		this->m_tail = this->m_head;
		this->m_size--;
		return rv;
	}
	else{
		T rv = this->m_head->get();
		node->previousNode(NULL);
		this->m_head->nextNode(NULL);
		delete this->m_head;
		this->m_head = node;
		this->m_size--;
		return rv;
	}

}

template<typename T>
T LinkList<T>::removeLast()
{
	DoubleListNode<T> * node = this->m_tail->previousNode();
	if (node == NULL){
		T rv = this->m_head->get();
		delete this->m_head;
		this->m_head = NULL;
		this->m_tail = this->m_head;
		this->m_size--;
		return rv;
	}
	else{
		T rv = this->m_tail->get();
		node->nextNode(NULL);
		delete this->m_tail;
		this->m_tail = node;
		this->m_size--;
		return rv;
	}

}

template<typename T>
void LinkList<T>::addFirst(const T& val)
{
	DoubleListNode<T> * node = new DoubleListNode<T>(val);
	if (this->m_head == NULL){
		this->m_head = node;
		this->m_tail = this->m_head;
	}
	else{
		this->m_head->linkPrevious(node);
		node->linkNext(this->m_head);
		this->m_head = node;
	}
	this->m_size++;
}

template<typename T>
void LinkList<T>::addLast(const T& val)
{
	DoubleListNode<T> * node = new DoubleListNode<T>(val);
	if (this->m_head == NULL){
		this->m_head = node;
		this->m_tail = this->m_head;
	}
	else{
		this->m_tail->linkNext(node);
		node->linkPrevious(this->m_tail);
		this->m_tail = node;
	}
	this->m_size++;
}

template<typename T>
void LinkList<T>::each(IExecutor<T>& executor)
{
	if (this->m_head != NULL){
		DoubleListNode<T> * pnode = this->m_head;
		while (pnode != NULL){
			executor.execute(pnode->get());
			pnode = pnode->nextNode();
		}
	}
}

template<typename T>
void LinkList<T>::enque(const T& val)
{
	this->addLast(val);
}

template<typename T>
T LinkList<T>::deque()
{
	return this->removeFirst();
}

template<typename T>
T& LinkList<T>::head()
{
	return this->m_head->get();
}

template<typename T>
T& LinkList<T>::tail()
{
	return this->m_tail->get();
}

template<typename T>
void LinkList<T>::push(const T& val)
{
	this->addLast(val);
}

template<typename T>
T LinkList<T>::pop()
{
	return this->removeLast();
}

template<typename T>
T& LinkList<T>::top()
{
	return this->m_tail->get();
}

template<typename T>
void LinkList<T>::tail2Head()
{
	if (this->m_size >= 2){
		this->addFirst(this->removeLast());
	}
}

template<typename T>
void LinkList<T>::head2Tail()
{
	if (this->m_size >= 2){
		this->addLast(this->removeFirst());
	}
}

template<typename T>
void LinkList<T>::swapHeadTail()
{
	if (this->m_size >= 2){
		T fst=this->removeFirst();
		T lst = this->removeLast();
		this->addFirst(lst);
		this->addLast(fst);
	}
	
}
#endif // _I2F_LINK_LIST_H_
