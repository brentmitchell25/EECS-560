#ifndef BTree_H_
#define BTree_H_
#include "Queue.h"
#include "Node.h"
#include <cmath>

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
	Node<T>* makeTwoNode(T data1, T data2, Node<T>* node);
	int getHeight(Node<T>* node, Node<T>* searchNode, int height);
	Node<T>* search(Node<T>* node, T data);

public:
	BTree();
	virtual ~BTree();
	void insert(T data);
	bool remove(T data);
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
/*
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
 */
template<typename T>
void BTree<T>::levelorder() {
	std::cout << "levelorder: " << std::endl;
	if (head == NULL)
		return;
	Queue<Node<T>*>* q = new Queue<Node<T>*>();
	Node<T>* printNode = head;
	q->enqueue(printNode);
	int prevHeight = 0;

	do {
		printNode = q->dequeue();
		int curHeight = getHeight(head, printNode, 0);

		if (curHeight != prevHeight) {
			std::cout << std::endl;
			prevHeight = curHeight;
		}

		if (printNode->isLeaf())
			std::cout << printNode->key << " ";
		else
			std::cout << printNode->minSecond << " " << printNode->minThird
					<< " ";

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
		node = new Node<T>(data, NULL);
	else if (node->parent == NULL && node->isLeaf()) {
		node->minSecond = std::max(node->key, data);
		node->first = new Node<T>(std::min(node->key, data), node);
		node->second = new Node<T>(std::max(node->key, data), node);
		node->key = -1;
		node->tag = 0;
	} else if (node->isLeaf()) {
		Node<T>* parent = node->parent;
		if (node->parent->isTwoNode()) {
			if (data >= parent->minSecond) {
				parent->minThird = data;
				parent->third = new Node<T>(data, parent);
			} else if (data < parent->minSecond) {
				parent->third = parent->second;
				parent->minThird = parent->minSecond;
				parent->minSecond = std::max(data,parent->first->key);
				if (data >= node->key) {
					parent->second = new Node<T>(data,parent);
				} else {
					parent->second = new Node<T>(parent->first->key,parent);
					parent->first = new Node<T>(data,parent);
				}
			}
		} else {
			Node<T>* rightChild;
			Node<T>* leftChild;
			if (data < parent->second->key) {
				leftChild = makeTwoNode(parent->first->key, data, parent);
				rightChild = makeTwoNode(parent->second->key,
						parent->third->key, parent);
			} else {
				leftChild = makeTwoNode(parent->first->key, parent->second->key,
						parent);
				rightChild = makeTwoNode(data, parent->third->key, parent);
			}
			splitNode(parent->parent, leftChild, rightChild);
		}
	} else if (data < node->minSecond) {
		insertHelper(data, node->first);
	} else if ((node->isTwoNode() && data >= node->minSecond)
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
void BTree<T>::splitNode(Node<T>*& node, Node<T>*& leftChild,
		Node<T>*& rightChild) {
	if (node == NULL) {
		head = new Node<T>(findMin(rightChild)->key, leftChild, rightChild, NULL);
		head->first->parent = head;
		head->second->parent = head;
		delete node;

	} else if (node->isTwoNode()) {
		if (node->minSecond > leftChild->minSecond) {
			node->minThird = node->minSecond;
			node->minSecond = findMin(rightChild)->key;
			node->third = node->first;
			node->first = leftChild;
			node->second = rightChild;
		} else {
			node->minThird = findMin(rightChild)->key;
			node->second = leftChild;
			node->third = rightChild;
		}
	} else {
		Node<T>* newLeftChild;
		Node<T>* newRightChild;
		if(rightChild->minSecond < node->second->minSecond) {
			newLeftChild = new Node<T>(findMin(rightChild)->key,leftChild,rightChild,node->parent);
			leftChild->parent = newLeftChild;
			rightChild->parent = newLeftChild;
			newRightChild = new Node<T>(findMin(node->third)->key,node->second,node->third,node->parent);
			node->second->parent = newRightChild;
			node->third->parent = newRightChild;
			delete node;
		} else if(rightChild->minSecond < node->third->minSecond) {
			newLeftChild = new Node<T>(findMin(leftChild)->key,node->first,leftChild,node->parent);
			node->first->parent = newLeftChild;
			leftChild->parent = newLeftChild;
			newRightChild = new Node<T>(findMin(node->third)->key,rightChild,node->third,node->parent);
			rightChild->parent = newRightChild;
			node->third->parent = newRightChild;
			delete node;
		} else {
			newLeftChild = new Node<T>(findMin(node->third)->key,node->second,node->third,node->parent);
			node->second->parent = newLeftChild;
			node->third->parent = newLeftChild;
			newRightChild = new Node<T>(findMin(rightChild)->key,leftChild,rightChild,node->parent);
			leftChild->parent = newRightChild;
			rightChild->parent = newRightChild;
			delete node;
		}
		splitNode(node->parent,newLeftChild,newRightChild);
	}

}

template<typename T>
Node<T>* BTree<T>::findMin(Node<T>*& node) {
	return (node->isLeaf()) ? node : findMin(node->first);
}

template<typename T>
Node<T>* BTree<T>::findMax(Node<T>*& node) {
	return (node->isLeaf()) ? node : findMin((node->isTwoNode) ? node->second : node->third);
}

template<typename T>
Node<T>* BTree<T>::makeTwoNode(T data1, T data2, Node<T>* node) {
	Node<T>* returnNode = NULL;
	Node<T>* leaf1 = new Node<T>(data1, returnNode);
	Node<T>* leaf2 = new Node<T>(data2, returnNode);
	if (data1 > data2) {
		returnNode = new Node<T>(data1, leaf2, leaf1, node);
	} else {
		returnNode = new Node<T>(data2, leaf1, leaf2, node);
	}
	returnNode->first->parent = returnNode;
	returnNode->second->parent = returnNode;
	return returnNode;
}

template<typename T>
int BTree<T>::getHeight(Node<T>* node, Node<T>* searchNode, int height) {
	if (node == searchNode)
		return height;
	else if (searchNode != node) {
		if ((searchNode->isLeaf() && searchNode->key < node->minSecond)
				|| (!searchNode->isLeaf()
						&& searchNode->minSecond < node->minSecond))
			return getHeight(node->first, searchNode, ++height);
		else if (!node->isTwoNode()
				&& ((searchNode->isLeaf() && searchNode->key >= node->minThird)
						|| (!searchNode->isLeaf()
								&& searchNode->minSecond >= node->minThird)))
			return getHeight(node->third, searchNode, ++height);
		else
			return getHeight(node->second, searchNode, ++height);
	}
	return height;
}

template<typename T>
Node<T>* BTree<T>::search(Node<T>* node, T data) {
	if(node->isLeaf())
		return node->key == data ? node : NULL;
	else if( data < node->minSecond)
		return search(node->first,data);
	else if(!node->isTwoNode() && data >= node->minThird)
		return search(node->third,data);
	else
		return search(node->second,data);
}

#endif /* BTree_H_ */
