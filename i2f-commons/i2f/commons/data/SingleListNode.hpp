#ifndef _I2F_SINGLE_LIST_NODE_H_
#define _I2F_SINGLE_LIST_NODE_H_


template<typename T>
class SingleListNode
{
private:
	T data;
	SingleListNode * next;
public:
	SingleListNode();
	SingleListNode(T& data);
	virtual ~SingleListNode();

	T& get();
	SingleListNode& set(T& data);

	SingleListNode * nextNode();
	SingleListNode * nextNode(SingleListNode * next);

	T& nextVal();

	SingleListNode& nextVal(T& data);

	bool isTail();

	bool hasNext();

	SingleListNode& cleanLink();
};


template<typename T>
SingleListNode<T>::SingleListNode()
{
	this->next = NULL;
}

template<typename T>
SingleListNode<T>::~SingleListNode()
{
	if (this->next != NULL){
		delete this->next;
		this->next = NULL;
	}
}

template<typename T>
SingleListNode<T>::SingleListNode(T& data)
{
	this->data = data;
	this->next = NULL;
}

template<typename T>
T& SingleListNode<T>::get()
{
	return this->data;
}

template<typename T>
SingleListNode<T>& SingleListNode<T>::set(T& data)
{
	this->data = data;
	return *this;
}

template<typename T>
SingleListNode<T> * SingleListNode<T>::nextNode()
{
	return this->next;
}

template<typename T>
SingleListNode<T> * SingleListNode<T>::nextNode(SingleListNode<T> * next)
{
	if (this->hasNext())
	{
		delete this->next;
		this->next = next;
	}
	else{
		this->next = next;
	}
	return next;
}

template<typename T>
T& SingleListNode<T>::nextVal()
{
	return this->next->data;
}

template<typename T>
SingleListNode<T>& SingleListNode<T>::nextVal(T& data)
{
	if (this->hasNext())
	{
		this->next->data = data;
	}
	else{
		SingleListNode* node = new SingleListNode(data);
		this->next = node;
	}
	return this->nextNode();
}

template<typename T>
bool SingleListNode<T>::isTail()
{
	return this->next == NULL;
}

template<typename T>
bool SingleListNode<T>::hasNext()
{
	return this->next != NULL;
}

template<typename T>
SingleListNode<T>& SingleListNode<T>::cleanLink()
{
	this->next = NULL;
	return *this;
}

#endif // _I2F_SINGLE_LIST_NODE_H_
