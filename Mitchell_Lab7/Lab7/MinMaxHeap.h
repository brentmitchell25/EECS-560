/*
 * MinMaxHeap.h
 *
 *  Created on: Mar 23, 2015
 *      Author: brentmitchell
 */

#ifndef MINMAXHEAP_H_
#define MINMAXHEAP_H_

#include <iostream>
#include <math.h>
template<typename T>
class MinMaxHeap {

private:
	long* table;
	long size;
	long length;
	void increaseTable();
	void TrickleDownMin(long index);
	void TrickleDownMax(long index);
	void BubbleUp(long index);
	void BubbleUpMin(long index);
	void BubbleUpMax(long index);
	bool isMinNode(long index);
	bool isMaxNode(long index);
	bool hasChildren(long index);
	void swap(long &a, long &b);
	long compare(const long indexA, const long indexB);
	long getLeftChild(long index);
	long getRightChild(long index);
	long getParent(long index);
	long smallestIndexOfChildAndGrandchild(long index);
	long largestIndexOfChildAndGrandchild(long index);
	void twoGrandchildrenSpecialCase(long index);


public:
	MinMaxHeap();
	virtual ~MinMaxHeap();
	void insert(T data);
	void deletemin();
	void deletemax();
	void print();
	void TrickleDown();
};

template<typename T>
MinMaxHeap<T>::MinMaxHeap() :
		size(1), length(1) {
	table = new long[2];
}

template<typename T>
MinMaxHeap<T>::~MinMaxHeap() {
	delete[] table;
}

template<typename T>
void MinMaxHeap<T>::insert(T data) {
	if (size > length)
		increaseTable();
	table[size++] = data;
	BubbleUp(size-1);
}

template<typename T>
void MinMaxHeap<T>::deletemin() {

}

template<typename T>
void MinMaxHeap<T>::deletemax() {
}

template<typename T>
void MinMaxHeap<T>::print() {
	int prevHeight = 1;
	for (long i = 1; i < size; i++) {
		int curHeight = log2(i);
		if(curHeight != prevHeight) {
			std::cout << std::endl;
			prevHeight = curHeight;
		}
		std::cout << table[i] << " ";
	}
}

template<typename T>
void MinMaxHeap<T>::increaseTable() {
	long *tempTable = new long[length * 2];
	long i;
	for (i = 1; i < size; i++) {
		tempTable[i] = table[i];
	}
	length *= 2;
	long *delTable = table;
	table = tempTable;
	delete delTable;
}

template<typename T>
void MinMaxHeap<T>::TrickleDown() {
	for(int i = getParent(size-1); i >= 1; i--) {
		print();
		std::cout  << std::endl;
	if(isMinNode(i)) {
		TrickleDownMin(i);
	} else {
		TrickleDownMax(i);
	}
	}
}

template<typename T>
void MinMaxHeap<T>::TrickleDownMin(long index) {
	if(hasChildren(index)) {

		long firstGrandchild = getLeftChild(getLeftChild(index));
		if(firstGrandchild < size && firstGrandchild + 2 >= size) {
			long leaf = getRightChild(index);
			long max = std::max(table[leaf],std::max(table[firstGrandchild],table[firstGrandchild+1]));
			if(max != table[leaf]) {
				if(table[max] == table[firstGrandchild])
				swap(table[firstGrandchild],table[leaf]);
				else
					swap(table[firstGrandchild+1],table[leaf]);
			}
		}

		long m = smallestIndexOfChildAndGrandchild(index);
		if((long)log2(m) == ((long)log2(index) + 2)) {
			if(table[m] < table[index]) {
				swap(table[index],table[m]);
				if(table[m] > table[getParent(m)])
					swap(table[m],table[getParent(m)]);
			}
			TrickleDownMin(m);
		} else {
			if(table[m] < table[index])
				swap(table[index],table[m]);
		}
	}
}

template<typename T>
void MinMaxHeap<T>::TrickleDownMax(long index) {
	if(hasChildren(index)) {
		long firstGrandchild = getLeftChild(getLeftChild(index));
		if(firstGrandchild < size && firstGrandchild + 2 >= size) {
			long leaf = getRightChild(index);
			long min = std::min(table[leaf],std::min(table[firstGrandchild],table[firstGrandchild+1]));
			if(min != table[leaf]) {
				if(table[min] == table[firstGrandchild])
				swap(table[firstGrandchild],table[leaf]);
				else
					swap(table[firstGrandchild+1],table[leaf]);
			}
		}

		long m = largestIndexOfChildAndGrandchild(index);
		if((long)log2(m) == ((long)log2(index) + 2)) {
			if(table[m] > table[index]) {
				swap(table[index],table[m]);
				if(table[m] < table[getParent(m)])
					swap(table[m],table[getParent(m)]);
			}
			TrickleDownMax(m);
		} else {
			if(table[m] > table[index])
				swap(table[index],table[m]);
		}
	}
}

template<typename T>
void MinMaxHeap<T>::BubbleUp(long index) {
	if(isMinNode(index)) {
		if(getParent(index) >= 1 && table[index] > table[getParent(index)]) {
			swap(table[index],table[getParent(index)]);
			BubbleUpMax(getParent(index));
		} else {
			BubbleUpMin(index);
		}
	} else {
		if(getParent(index) >= 1 && table[index] < table[getParent(index)]) {
			swap(table[index],table[getParent(index)]);
			BubbleUpMin(getParent(index));
		} else {
			BubbleUpMax(index);
		}
	}
}

template<typename T>
void MinMaxHeap<T>::BubbleUpMin(long index) {
	long grandparent = getParent(getParent(index));
	if(grandparent >= 1) {
		if(table[index] < table[grandparent]) {
			swap(table[index],table[grandparent]);
			BubbleUpMin(grandparent);
		}
	}
}

template<typename T>
void MinMaxHeap<T>::BubbleUpMax(long index) {
long grandparent = getParent(getParent(index));
	if(grandparent >= 1) {
		if(table[index] > table[grandparent]) {
			swap(table[index],table[grandparent]);
			BubbleUpMax(grandparent);
		}
	}
}

template<typename T>
bool MinMaxHeap<T>::isMinNode(long index) {
	return (long)log2(index) % 2 == 0;
}

template<typename T>
bool MinMaxHeap<T>::isMaxNode(long index) {
	return !isMinNode(index);
}

template<typename T>
bool MinMaxHeap<T>::hasChildren(long index) {
	return 2*index <= length;
}

template<typename T>
void MinMaxHeap<T>::swap(long &a, long &b) {
	T c(a);
	a = b;
	b = c;
}

template<typename T>
long MinMaxHeap<T>::compare(long indexA, long indexB) {
	return table[indexA] < table[indexB] ? indexA : indexB;
}

template<typename T>
long MinMaxHeap<T>::getLeftChild(long index) {
	return 2 * index;
}

template<typename T>
long MinMaxHeap<T>::getRightChild(long index) {
	return 2 * index + 1;
}

template<typename T>
long MinMaxHeap<T>::getParent(long index) {
	return index / 2;
}

template<typename T>
long MinMaxHeap<T>::smallestIndexOfChildAndGrandchild(long index) {
	long leftChild = getLeftChild(index);
	long leftGrandchild = getLeftChild(leftChild);
	long smallestIndex = leftChild;

	if(leftChild + 1 < size)
		smallestIndex = compare(leftChild,leftChild+1);

		for(long i = 0; i < 4 && leftGrandchild + i < size; i++) {
			smallestIndex = compare(smallestIndex,leftGrandchild + 1);
		}

	return smallestIndex;

}

template<typename T>
long MinMaxHeap<T>::largestIndexOfChildAndGrandchild(long index) {
	long leftChild = getLeftChild(index);
	long leftGrandchild = getLeftChild(leftChild);
	long largestIndex = leftChild;

	if(leftChild + 1 < size)
		largestIndex = compare(leftChild,leftChild+1);
		for(long i = 0; i < 4 && leftGrandchild + i < size; i++) {
			largestIndex = compare(leftGrandchild + 1, largestIndex);
		}

	return largestIndex;

}

template<typename T>
void MinMaxHeap<T>::twoGrandchildrenSpecialCase(long index) {
	long firstGrandchild = getLeftChild(getLeftChild(index));
		if(firstGrandchild < size && firstGrandchild + 2 >= size) {
			long leaf = getRightChild(index);
			long min = std::min(leaf,std::min(firstGrandchild,firstGrandchild+1));
			if(min != leaf)
				swap(table[min],table[leaf]);
		}
}
#endif /* MINMAXHEAP_H_ */
