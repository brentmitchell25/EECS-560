/*
 * SkewHeap.h
 *
 *  Created on: Mar 29, 2015
 *      Author: brentmitchell
 */

#ifndef MINLEFISTHEAP_H_
#define MINLEFISTHEAP_H_
#include "BinaryNode.h"

template<typename T>
class MinLefistHeap {

private:
	void merge(BinaryNode<T> *h1,BinaryNode<T> *h2);
	int getRank(BinaryNode<T> *h1);
	void swap(T& a, T& b);
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
MinLefistHeap<T>::MinLefistHeap() {

}

template<typename T>
MinLefistHeap<T>::~MinLefistHeap() {

}

template<typename T>
void MinLefistHeap<T>::insert(T data) {

}

template<typename T>
bool MinLefistHeap<T>::deletemin() {

}

template<typename T>
void MinLefistHeap<T>::preorder() {

}

template<typename T>
void MinLefistHeap<T>::inorder() {

}

template<typename T>
void MinLefistHeap<T>::levelorder() {

}

template<typename T>
void MinLefistHeap<T>::swap(T &a, T &b) {
	T c(a);
	a = b;
	b = c;
}

#endif /* MINLEFISTHEAP_H_ */
