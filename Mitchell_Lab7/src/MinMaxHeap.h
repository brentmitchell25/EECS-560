/*
 * MinMaxHeap.h
 *
 *  Created on: Mar 23, 2015
 *      Author: brentmitchell
 */

#ifndef MINMAXHEAP_H_
#define MINMAXHEAP_H_

#include <iostream>
#include <tgmath.h>
template<typename T>
class MinMaxHeap {

private:
	long* table;
	long lastElement;
	long maxLength;
	void increaseTable();
	void TrickleDownMin(T value);
	void TrickleDownMax(T value);
	void BubbleUp(T value);
	void BubbleUpMin(T value);
	void BubbleUpMax(T value);
	bool isMinNode(T index);
	bool isMaxNode(T index);
	bool hasChildren(T index);
	void swap(T &a, T &b);

public:
	MinMaxHeap();
	virtual ~MinMaxHeap();
	void insert(T data);
	void deletemin();
	void deletemax();
	void print();
	void TrickleDown(T value);
};

template<typename T>
MinMaxHeap<T>::MinMaxHeap() :
		lastElement(1), maxLength(1) {
	table = new long[2];
}

template<typename T>
MinMaxHeap<T>::~MinMaxHeap() {
	delete[] table;
}

template<typename T>
void MinMaxHeap<T>::insert(T value) {
	std::cout << lastElement << " " << maxLength << value << std::endl;
	if (lastElement > maxLength)
		increaseTable();
	table[lastElement++] = value;
}

template<typename T>
void MinMaxHeap<T>::deletemin() {

}

template<typename T>
void MinMaxHeap<T>::deletemax() {
}

template<typename T>
void MinMaxHeap<T>::print() {
	for (long i = 1; i < lastElement; i++) {
		std::cout << table[i] << " ";
	}
}

template<typename T>
void MinMaxHeap<T>::increaseTable() {
	long *tempTable = new long[maxLength * 2];
	long i;
	for (i = 1; i < lastElement; i++) {
		tempTable[i] = table[i];
	}
	for(; i <= maxLength;i++) {
		tempTable[i] = -1;
	}
	maxLength *= 2;
	long *delTable = table;
	table = tempTable;
	delete delTable;
}

template<typename T>
bool MinMaxHeap<T>::isMinNode(T index) {
	return log2(index) % 2 == 0;
}

template<typename T>
bool MinMaxHeap<T>::isMaxNode(T index) {
	return !isMinNode(index);
}

template<typename T>
bool MinMaxHeap<T>::hasChildren(T index) {
	return 2*index <= maxLength && 2*index != -1;
}

template<typename T>
void MinMaxHeap<T>::TrickleDown(T value) {
	if(isMinNode(lastElement)) {
		TrickleDownMin(lastElement);
	} else {
		TrickleDownMax(lastElement);
	}
}

template<typename T>
void MinMaxHeap<T>::TrickleDownMin(T value) {
	if(hasChildren(table[value])) {

	}
}

template<typename T>
void MinMaxHeap<T>::TrickleDownMax(T value) {

}


template<typename T>
void MinMaxHeap<T>::swap(T &a, T &b) {
	T c(a);
	a = b;
	b = a;
}

#endif /* MINMAXHEAP_H_ */
