#ifndef BTree_H_
#define BTree_H_
#include "Queue.h"
#include "Node.h"

template<typename T>
class BTree {
private:
	Node<T>* head;
	Node<T>* searchHelper(T data, Node<T>* node);
	void insertHelper(T data, Node<T>*& node);
	void deleteminHelper(Node<T>*& node);
	Node<T>* findMin(Node<T>*& node);
	Node<T>* findMax(Node<T>*& node);
	void deletemaxHelper(Node<T>*& node);
	bool removeHelper(T data, Node<T>*& node);
	void splitNode(Node<T>*& node, Node<T>*& leftChild, Node<T>*& rightChild);
	Node<T>* findMin(Node<T>* node);
	Node<T>* makeTwoNode(T data, Node<T>* node);
	bool isTwoNode(Node<T>* node);

public:
	BTree();
	virtual ~BTree();
	void insert(T data);
	bool remove(T data);
	Node<T>* search(T data);
	void deletemin();
	void deletemax();
	void levelorder();
};

template<typename T>
BTree<T>::BTree() :
		head(NULL) {
}

template<typename T>
BTree<T>::~BTree() {

}

template<typename T>
void BTree<T>::insert(T data) {
	insertHelper(data, head);
}

template<typename T>
bool BTree<T>::remove(T data) {
	return removeHelper(data, head);
}

template<typename T>
Node<T>* BTree<T>::search(T data) {
	return searchHelper(data, head);
}

template<typename T>
void BTree<T>::deletemin() {
	return deleteminHelper(head);
}

template<typename T>
void BTree<T>::deletemax() {
	return deletemaxHelper(head);
}

template<typename T>
void BTree<T>::levelorder() {
	std::cout << "levelorder: ";
	if (head == NULL)
		return;
	Queue<Node<T>*>* q = new Queue<Node<T>*>();
	Node<T>* printNode = head;
	q->enqueue(printNode);

	do {
		printNode = q->dequeue();
		std::cout << printNode->key << " ";
		if (printNode->first != NULL)
			q->enqueue(printNode->first);
		if (printNode->second != NULL)
			q->enqueue(printNode->second);
		if (printNode->third != NULL)
			q->enqueue(printNode->third);
	} while (!q->isEmpty());

	delete q;

}

template<typename T>
Node<T>* BTree<T>::searchHelper(T data, Node<T>* node) {
	if (node == NULL)
		return NULL;
	else if (node->data == data)
		return node;
	if (data < node->data)
		return searchHelper(data, node->left);
	else
		return searchHelper(data, node->right);
}

template<typename T>
void BTree<T>::insertHelper(T data, Node<T>*& node) {
	if (node == NULL)
		node = new Node<T>(data);
	else if (node->parent == NULL && node->isLeaf()) {
		node->minSecond = node->key;
		node->first = new Node<T>(node->key, node);
		node->second = new Node<T>(data, node);
	} else if (node->isLeaf()) {
		Node<T>* parent = node->parent;
		if (isTwoNode(node->parent)) {
			if (data >= parent->minSecond) {
				parent->minThird = data;
				parent->third = new Node<T>(data);
			} else if (data < parent->minSecond) {
				parent->third = parent->second;
				parent->minThird = parent->minSecond;
				parent->minSecond = data;
				if (data >= node->key) {
					parent->second->key = data;
				} else {
					parent->second = parent->first;
					parent->first->key = data;
				}
			}
		} else {
			if(data > parent->second->key)
				Node<T>* rightChild = makeTwoNode(data,parent->third);
			Node<T>* leftChild;
			splitNode(parent, leftChild, rightChild);
		}
	} else if (data < node->minSecond) {
		insertHelper(data, node->first);
	} else if ((isTwoNode(node) && data >= node->minSecond)
			|| (data >= node->minSecond && data < node->minThird)) {
		insertHelper(data, node->second);
	} else if (data >= node->minThird) {
		insertHelper(data, node->third);
	}
}
/*
 template<typename T>
 void BTree<T>::deleteminHelper(Node<T>*& node) {
 if (node == NULL)
 return;
 else if (isLeaf(node)) {
 delete node;
 node = NULL;
 } else if (node->left == NULL && node->right != NULL) {
 node->data = findMin(node->right)->data;
 removeHelper(node->data, node->right);
 } else if (node->left->left == NULL) {
 delete node->left;
 node->left = NULL;
 } else
 deleteminHelper(node->left);
 }

 template<typename T>
 void BTree<T>::deletemaxHelper(Node<T>*& node) {
 if (node == NULL)
 return;
 else if (isLeaf(node)) {
 delete node;
 node = NULL;
 } else if (node->right == NULL && node->left != NULL) {
 node->data = findMax(node->left)->data;
 removeHelper(node->data, node->left);
 } else if (node->right->right == NULL) {
 delete node->right;
 node->right = NULL;
 } else
 deletemaxHelper(node->right);

 }

 template<typename T>
 Node<T>* BTree<T>::findMin(Node<T>*& node) {
 if (node == NULL)
 return NULL;
 return node->left == NULL ? node : findMin(node->left);
 }

 template<typename T>
 Node<T>* BTree<T>::findMax(Node<T>*& node) {
 if (node == NULL)
 return NULL;
 return node->right == NULL ? node : findMin(node->right);
 }

 template<typename T>
 bool BTree<T>::removeHelper(T data, Node<T>*& node) {
 if (node == NULL)
 return false;
 else if (data < node->key)
 return removeHelper(data, node->left);
 else if (data > node->data)
 return removeHelper(data, node->right);
 else if (node->left != NULL && node->right != NULL) {
 node->data = findMin(node->right)->data;
 return removeHelper(node->data, node->right);
 } else {
 Node<T>* delNode = node;
 node = node->left == NULL ? node->right : node->left;
 delete delNode;
 return true;
 }
 }
 */

template<typename T>
void BTree<T>::splitNode(Node<T>*& node,Node<T>*& leftChild ,Node<T>*& rightChild) {
	if(isTwoNode()) {

	}
}

template<typename T>
Node<T>* BTree<T>::findMin(Node<T>* node) {
	return (node->isLeaf()) ? node->key : findMin(node->first);
}

template<typename T>
Node<T>* BTree<T>::makeTwoNode(T data, Node<T>* node) {
	Node<T>* returnNode;
	Node<T>* firstOrSecond = new Node<T>(data);
	if(node->isLeaf() && data > node->key) {
		returnNode = new Node<T>(data,node,firstOrSecond,node->parent);
	} else if(node->isLeaf() && data < node->key){
		returnNode = new Node<T>(node->key,firstOrSecond,node,node->parent);
	} else if( data > node->isLeaf()) {

	}
	return returnNode;
}

template<typename T>
bool BTree<T>::isTwoNode(Node<T>* node) {
	if (node->third == NULL)
		return true;
	return false;
}

#endif /* BTree_H_ */
