#ifndef MINMAXHEAP_H_
#define MINMAXHEAP_H_
#include <iostream>

template<typename T>
class MinMaxHeap {

private:
  long* table;
  long lastElement;
  long maxLength;
  void TrickleDown(T value);
  void TrickleDownMin(T value);
  void TrickleDownMax(T value);
  void BubbleUp(T value);
  void BubbleUpMin(T value);
    void BubbleUpMax(T value);

public:
	MinMaxHeap(long l);
	virtual ~MinMaxHeap();
	void insert(T data);
	void deletemin();
	void deletemax();
	void print();
};

template<typename T>
MinMaxHeap<T>::MinMaxHeap(long l):lastElement(1) {
  table = new long[++l];
  maxLength = l;
}

template<typename T>
MinMaxHeap<T>::~MinMaxHeap() {
  delete [] table;
}

template<typename T>
void MinMaxHeap<T>::insert(T value) {
  if(lastElement <= maxLength) {
    table[lastElement++] = value;
  } else {

  }
}

template<typename T>
void MinMaxHeap<T>::deletemin() {
}

template<typename T>
void MinMaxHeap<T>::deletemax() {
}

template<typename T>
void MinMaxHeap<T>::print() {
  for(long i = 1; i <= maxLength; i++) {
    std::cout << table[i] << " ";
  }
}

#endif
