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
	void merge();
};

template<typename T>
BinomialQueue<T>::BinomialQueue() {

}

template<typename T>
BinomialQueue<T>::~BinomialQueue() {

}

template<typename T>
void BinomialQueue<T>::insert(T x) {

}

template<typename T>
bool BinomialQueue<T>::deletemin() {

}

template<typename T>
void BinomialQueue<T>::levelorder() {

}

template<typename T>
void BinomialQueue<T>::merge() {

}


#endif /* BINOMIALQUEUE_H_ */
