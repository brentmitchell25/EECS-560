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
	int rank(BinaryNode<T> *h1, int count);
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

template<typename T>
void MinLefistHeap<T>::merge(BinaryNode<T> *h1,BinaryNode<T> *h2) {

}

template<typename T>
int MinLefistHeap<T>::rank(BinaryNode<T> *h,int count) {
	if(h == NULL)
		return 0;
	else {
		count++;
		return std::max(rank(h->right,count),rank(h->left,count));
	}
}



#endif /* MINLEFISTHEAP_H_ */
