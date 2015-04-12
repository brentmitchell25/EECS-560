/*
 * BinomialQueue.h
 *
 *  Created on: Apr 12, 2015
 *      Author: brentmitchell
 */

#ifndef BINOMIALQUEUE_H_
#define BINOMIALQUEUE_H_
#include "BQNode.h"

template<typename T>
class BinomialQueue {
public:
	BinomialQueue();
	virtual ~BinomialQueue();
	void insert(T x);
	bool deletemin();
	void levelorder();

private:
	BQNode<T> *head;
	void merge(BQNode<T> *first, BQNode<T> *second);
};

template<typename T>
BinomialQueue<T>::BinomialQueue(): head(NULL){

}

template<typename T>
BinomialQueue<T>::~BinomialQueue() {

}

template<typename T>
void BinomialQueue<T>::insert(T x) {
	BQNode<T> *newNode = new BQNode<T>(x);
	merge(head,newNode);
}

template<typename T>
bool BinomialQueue<T>::deletemin() {

}

template<typename T>
void BinomialQueue<T>::levelorder() {

}

template<typename T>
void BinomialQueue<T>::merge(BQNode<T> *first, BQNode<T> *second) {

}


#endif /* BINOMIALQUEUE_H_ */
