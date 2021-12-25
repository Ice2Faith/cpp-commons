#ifndef _I2F_DOUBLE_LIST_NODE_H_
#define _I2F_DOUBLE_LIST_NODE_H_

template<typename T>
class DoubleListNode
{
private:
	T data;
	DoubleListNode * previous;
	DoubleListNode * next;
	
public:
	DoubleListNode();
	DoubleListNode(const T& data);
	virtual ~DoubleListNode();

	T& get();
	DoubleListNode& set(const T& data);

	DoubleListNode * previousNode();
	DoubleListNode * nextNode();
	DoubleListNode * previousNode(DoubleListNode * left);
	DoubleListNode * nextNode(DoubleListNode * right);

	DoubleListNode * linkPrevious(DoubleListNode * left);
	DoubleListNode * linkNext(DoubleListNode * right);

	T& previousVal();
	T& nextVal();
	DoubleListNode& previousVal(const T& data);
	DoubleListNode& nextVal(const T& data);

	bool isTail();
	bool isHead();

	bool hasPrevious();
	bool hasNext();

	DoubleListNode& cleanLink();
};


template<typename T>
DoubleListNode<T>::DoubleListNode()
{
	this->previous = NULL;
	this->next = NULL;
}
template<typename T>
DoubleListNode<T>::DoubleListNode(const T& data)
{
	this->data = data;
	this->previous = NULL;
	this->next = NULL;
}

template<typename T>
DoubleListNode<T>::~DoubleListNode()
{
	if (this->previous != NULL){
		this->previous->next = this->next;
	}
	if (this->next != NULL){
		this->next->previous = this->previous;
	}
}

template<typename T>
T& DoubleListNode<T>::get()
{
	return this->data;
}

template<typename T>
DoubleListNode<T>& DoubleListNode<T>::set(const T& data)
{
	this->data = data;
	return *this;
}

template<typename T>
DoubleListNode<T> * DoubleListNode<T>::previousNode()
{
	return this->previous;
}

template<typename T>
DoubleListNode<T> * DoubleListNode<T>::nextNode()
{
	return this->next;
}

template<typename T>
DoubleListNode<T> * DoubleListNode<T>::linkPrevious(DoubleListNode<T> * previous)
{
	if (this->hasPrevious())
	{
		DoubleListNode<T> * mp = this->previous;
		mp->next = previous;

		previous->previous = mp;
		previous->next = this;
		
		this->previous = previous;
	}
	else{
		this->previous = previous;
	}
	return previous;
}

template<typename T>
DoubleListNode<T> * DoubleListNode<T>::linkNext(DoubleListNode<T> * next)
{
	if (this->hasNext())
	{
		DoubleListNode<T> * mp = this->next;
		mp->previous = next;

		next->next = mp;
		next->previous = this;

		this->next = next;
	}
	else{
		this->next = next;
	}
	return next;
}
template<typename T>
DoubleListNode<T> * DoubleListNode<T>::previousNode(DoubleListNode * left)
{
	this->previous = left;
	return this;
}

template<typename T>
DoubleListNode<T> * DoubleListNode<T>::nextNode(DoubleListNode * right)
{
	this->next = right;
	return this;
}

template<typename T>
T& DoubleListNode<T>::previousVal()
{
	return this->previous->data;
}

template<typename T>
T& DoubleListNode<T>::nextVal()
{
	return this->next->data;
}

template<typename T>
DoubleListNode<T>& DoubleListNode<T>::previousVal(const T& data)
{
	if (this->hasPrevious())
	{
		this->previous->data = data;
	}
	else{
		DoubleListNode* node = new DoubleListNode(data);
		this->previous = node;
		node->next = this;
	}
	return this->previousNode();
}

template<typename T>
DoubleListNode<T>& DoubleListNode<T>::nextVal(const T& data)
{
	if (this->hasNext())
	{
		this->next->data = data;
	}
	else{
		DoubleListNode* node = new DoubleListNode(data);
		this->next = node;
		node->previous = this;
	}
	return this->nextNode();
}

template<typename T>
bool DoubleListNode<T>::isTail()
{
	return this->next == NULL;
}

template<typename T>
bool DoubleListNode<T>::isHead()
{
	return this->previous == NULL;
}

template<typename T>
bool DoubleListNode<T>::hasPrevious()
{
	return this->previous != NULL;
}

template<typename T>
bool DoubleListNode<T>::hasNext()
{
	return this->next != NULL;
}

template<typename T>
DoubleListNode<T>& DoubleListNode<T>::cleanLink()
{
	this->previous = NULL;
	this->next = NULL;
}
#endif //_I2F_DOUBLE_LIST_NODE_H_

