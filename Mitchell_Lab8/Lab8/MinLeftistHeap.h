/*
 * SkewHeap.h
 *
 *  Created on: Mar 29, 2015
 *      Author: brentmitchell
 */

#ifndef MinLeftistHeap_H_
#define MinLeftistHeap_H_
#include "BinaryNode.h"
#include "Queue.h"

template<typename T>
class MinLeftistHeap {

private:
	void destroy(BinaryNode<T> *node);
	BinaryNode<T>* merge(BinaryNode<T> *h1, BinaryNode<T> *h2);
	int rank(BinaryNode<T> *h1, int count);
	void swap(BinaryNode<T>*& a, BinaryNode<T>*& b);
	BinaryNode<T>* head;
	void inorderTraversal(BinaryNode<T> *node);
	void preorderTraversal(BinaryNode<T> *node);
	int getHeight(BinaryNode<T>* node, BinaryNode<T>* searchNode, int height);
public:
	MinLeftistHeap();
	virtual ~MinLeftistHeap();
	void insert(T data);
	bool deletemin();
	void preorder();
	void inorder();
	void levelorder();
};

template<typename T>
MinLeftistHeap<T>::MinLeftistHeap() :
		head(NULL) {
}

template<typename T>
MinLeftistHeap<T>::~MinLeftistHeap() {
	destroy(head);
}

template<typename T>
void MinLeftistHeap<T>::destroy(BinaryNode<T> *node) {
	if (node == NULL)
		return;
	destroy(node->left);
	destroy(node->right);
	delete node;
}

template<typename T>
void MinLeftistHeap<T>::insert(T data) {
	BinaryNode<T> *newNode = new BinaryNode<T>(data);
	head = merge(newNode, head);
}

template<typename T>
bool MinLeftistHeap<T>::deletemin() {
	if (head == NULL)
		return false;
	BinaryNode<T> *delHead = head;
	head = merge(head->left, head->right);
	delete delHead;

	return true;
}

template<typename T>
void MinLeftistHeap<T>::preorder() {
	std::cout << "preorder: ";
	preorderTraversal(head);
}

template<typename T>
void MinLeftistHeap<T>::inorder() {
	std::cout << "inorder: ";
	inorderTraversal(head);
}

template<typename T>
void MinLeftistHeap<T>::levelorder() {
	std::cout << "levelorder: " << std::endl;
	if (head == NULL)
		return;
	Queue<BinaryNode<T>*>* q = new Queue<BinaryNode<T>*>();
	BinaryNode<T>* printNode = head;
	q->enqueue(printNode);
	int prevHeight = 0;

	do {
		printNode = q->dequeue();
		int curHeight = getHeight(head, printNode, 0);

		if (curHeight != prevHeight) {
			std::cout << std::endl;
			prevHeight = curHeight;
		}

		std::cout << printNode->key << " ";

		if (printNode->left != NULL)
			q->enqueue(printNode->left);
		if (printNode->right != NULL)
			q->enqueue(printNode->right);

	} while (!q->isEmpty());

	delete q;

}

template<typename T>
int MinLeftistHeap<T>::getHeight(BinaryNode<T>* node, BinaryNode<T>* searchNode,
		int height) {

	if (node == NULL)
		return 0;
	else if (node->key == searchNode->key)
		return height;
	int h1, h2;
	height++;
	h1 = getHeight(node->left, searchNode, height);
	h2 = getHeight(node->right, searchNode, height);
	if (h1 == 0 && h2 == 0)
		return 0;
	if (h1 == 0)
		return h2;
	else
		return h1;

}

template<typename T>
void MinLeftistHeap<T>::swap(BinaryNode<T>*& a, BinaryNode<T>*& b) {
	BinaryNode<T> *temp;
	if (a == NULL)
		temp = NULL;
	else
		temp = new BinaryNode<T>(a->key, a->rank, a->left, a->right);
	a = b;
	b = temp;
}

template<typename T>
BinaryNode<T>* MinLeftistHeap<T>::merge(BinaryNode<T> *h1, BinaryNode<T> *h2) {
	if (h1 == NULL)
		return h2;
	else if (h2 == NULL)
		return h1;
	else if (h1->key > h2->key) {
		swap(h1, h2);
	}
	h1->right = merge(h1->right, h2);

	if (h1->left == NULL)
		swap(h1->left, h1->right);
	else {
		if (h1->left->rank < h1->right->rank)
			swap(h1->left, h1->right);
		h1->rank = h1->right->rank + 1;
	}
	return h1;
}

template<typename T>
int MinLeftistHeap<T>::rank(BinaryNode<T> *h, int count) {
	if (h == NULL)
		return count;
	else {
		count++;
		return std::min(rank(h->right, count), rank(h->left, count));
	}
}

template<typename T>
void MinLeftistHeap<T>::inorderTraversal(BinaryNode<T> *node) {
	if (node == NULL)
		return;

	inorderTraversal(node->left);
	std::cout << node->key << " ";
	inorderTraversal(node->right);
}

template<typename T>
void MinLeftistHeap<T>::preorderTraversal(BinaryNode<T> *node) {
	if (node == NULL)
		return;

	std::cout << node->key << " ";
	preorderTraversal(node->left);
	preorderTraversal(node->right);
}

#endif /* MinLeftistHeap_H_ */
