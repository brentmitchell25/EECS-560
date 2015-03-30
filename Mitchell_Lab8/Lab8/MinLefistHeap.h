/*
 * SkewHeap.h
 *
 *  Created on: Mar 29, 2015
 *      Author: brentmitchell
 */

#ifndef MINLEFISTHEAP_H_
#define MINLEFISTHEAP_H_
#include "BinaryNode.h"
#include "Queue.h"

template<typename T>
class MinLefistHeap {

private:
	void destroy(BinaryNode<T> *node);
	BinaryNode<T>* merge(BinaryNode<T> *h1, BinaryNode<T> *h2);
	int rank(BinaryNode<T> *h1, int count);
	void swap(BinaryNode<T>*& a, BinaryNode<T>*& b);
	BinaryNode<T>* head;
	void inorderTraversal(BinaryNode<T> *node);
	void preorderTraversal(BinaryNode<T> *node);
public:
	MinLefistHeap();
	virtual ~MinLefistHeap();
	void insert(T data);
	bool deletemin();
	void preorder();
	void inorder();
	void levelorder();
};

template<typename T>
MinLefistHeap<T>::MinLefistHeap() :
		head(NULL) {

}

template<typename T>
MinLefistHeap<T>::~MinLefistHeap() {
	destroy(head);
}

template<typename T>
void MinLefistHeap<T>::destroy(BinaryNode<T> *node) {
	if (node == NULL)
		return;
	destroy(node->left);
	destroy(node->right);
	delete node;
}

template<typename T>
void MinLefistHeap<T>::insert(T data) {
	BinaryNode<T> *newNode = new BinaryNode<T>(data);
	head = merge(newNode,head);
}

template<typename T>
bool MinLefistHeap<T>::deletemin() {

}

template<typename T>
void MinLefistHeap<T>::preorder() {
	std::cout << "preorder: ";
	preorderTraversal(head);
}

template<typename T>
void MinLefistHeap<T>::inorder() {
	std::cout << "inorder: ";
	inorderTraversal(head);
}

template<typename T>
void MinLefistHeap<T>::levelorder() {
	std::cout << "levelorder: ";
	if (head == NULL)
		return;
	Queue<BinaryNode<T>*> q;
	BinaryNode<T>* printNode = head;
	q.enqueue(printNode);

	do {
		printNode = q.dequeue();
		std::cout << printNode->key << " ";
		if (printNode->left != NULL)
			q.enqueue(printNode->left);
		if (printNode->right != NULL)
			q.enqueue(printNode->right);
	} while (!q.isEmpty());

}

template<typename T>
void MinLefistHeap<T>::swap(BinaryNode<T>*& a, BinaryNode<T>*& b) {
	BinaryNode<T> *temp = new BinaryNode<T>(a->key,a->rank,a->left,a->right);
	a = b;
	b = temp;
}

template<typename T>
BinaryNode<T>* MinLefistHeap<T>::merge(BinaryNode<T> *h1, BinaryNode<T> *h2) {
	if (h1 == NULL)
		return h2;
	else if (h2 == NULL)
		return h1;
	else if (h1->key > h2->key) {
		swap(h1, h2);
	}
	h1->right = merge(h1->right, h2);
	if (rank(h1->left, 0) < rank(h1->right, 0))
		swap(h1->left, h1->right);
	return h1;
}

template<typename T>
int MinLefistHeap<T>::rank(BinaryNode<T> *h, int count) {
	if (h == NULL)
		return 0;
	else {
		count++;
		return std::max(rank(h->right, count), rank(h->left, count));
	}
}

template<typename T>
void MinLefistHeap<T>::inorderTraversal(BinaryNode<T> *node) {
	if (node == NULL)
		return;

	inorderTraversal(node->left);
	std::cout << node->key << " ";
	inorderTraversal(node->right);
}

template<typename T>
void MinLefistHeap<T>::preorderTraversal(BinaryNode<T> *node) {
	if (node == NULL)
		return;

	std::cout << node->key << " ";
	preorderTraversal(node->left);
	preorderTraversal(node->right);
}

#endif /* MINLEFISTHEAP_H_ */
