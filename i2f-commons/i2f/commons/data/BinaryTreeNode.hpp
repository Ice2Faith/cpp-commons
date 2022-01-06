#ifndef _I2F_BINARY_TREE_NODE_H_
#define _I2F_BINARY_TREE_NODE_H_


template<typename T>
class BinaryTreeNode
{
private:
	T data;
	BinaryTreeNode * left;
	BinaryTreeNode * right;
public:
	BinaryTreeNode();
	BinaryTreeNode(T& data);
	virtual ~BinaryTreeNode();

	T& get();
	BinaryTreeNode& set(T& data);

	BinaryTreeNode * leftNode();
	BinaryTreeNode * rightNode();
	BinaryTreeNode * leftNode(BinaryTreeNode * left);
	BinaryTreeNode * rightNode(BinaryTreeNode * right);

	T& leftVal();
	T& rightVal();
	BinaryTreeNode& leftVal(T& data);
	BinaryTreeNode& rightVal(T& data);

	bool isLeaf();

	bool hasLeft();
	bool hasRight();

	BinaryTreeNode& cleanLink();
};


template<typename T>
BinaryTreeNode<T>::BinaryTreeNode()
{
	this->left = NULL;
	this->right = NULL;
}
template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(T& data)
{
	this->data = data;
	this->left = NULL;
	this->right = NULL;
}

template<typename T>
BinaryTreeNode<T>::~BinaryTreeNode()
{
	if (this->left != NULL){
		delete this->left;
		this->left = NULL;
	}
	if (this->right != NULL){
		delete this->right;
		this->right = NULL;
	}
}

template<typename T>
T& BinaryTreeNode<T>::get()
{
	return this->data;
}

template<typename T>
BinaryTreeNode<T>& BinaryTreeNode<T>::set(T& data)
{
	this->data = data;
	return &this;
}

template<typename T>
BinaryTreeNode<T> * BinaryTreeNode<T>::leftNode()
{
	return this->left;
}

template<typename T>
BinaryTreeNode<T> * BinaryTreeNode<T>::rightNode()
{
	return this->right;
}

template<typename T>
BinaryTreeNode<T> * BinaryTreeNode<T>::leftNode(BinaryTreeNode<T> * left)
{
	if (this->hasLeft())
	{
		delete this->left;
		this->left = left;
	}
	else{
		this->left = left;
	}
	return left;
}

template<typename T>
BinaryTreeNode<T> * BinaryTreeNode<T>::rightNode(BinaryTreeNode<T> * right)
{
	if (this->hasRight())
	{
		delete this->right;
		this->right = right;
	}
	else{
		this->right = right;
	}
	return right;
}

template<typename T>
T& BinaryTreeNode<T>::leftVal()
{
	return this->left->data;
}

template<typename T>
T& BinaryTreeNode<T>::rightVal()
{
	return this->right->data;
}

template<typename T>
BinaryTreeNode<T>& BinaryTreeNode<T>::leftVal(T& data)
{
	if (this->hasLeft())
	{
		this->left->data = data;
	}
	else{
		BinaryTreeNode* node = new BinaryTreeNode(data);
		this->left = node;
	}
	return this->leftNode();
}

template<typename T>
BinaryTreeNode<T>& BinaryTreeNode<T>::rightVal(T& data)
{
	if (this->hasRight())
	{
		this->right->data = data;
	}
	else{
		BinaryTreeNode* node = new BinaryTreeNode(data);
		this->right = node;
	}
	return this->rightNode();
}

template<typename T>
bool BinaryTreeNode<T>::isLeaf()
{
	return this->left == NULL && this->right == NULL;
}

template<typename T>
bool BinaryTreeNode<T>::hasLeft()
{
	return this->left != NULL;
}

template<typename T>
bool BinaryTreeNode<T>::hasRight()
{
	return this->right != NULL;
}

template<typename T>
BinaryTreeNode<T>& BinaryTreeNode<T>::cleanLink()
{
	this->left = NULL;
	this->right = NULL;
	return &this;
}
#endif //_I2F_BINARY_TREE_NODE_H_

