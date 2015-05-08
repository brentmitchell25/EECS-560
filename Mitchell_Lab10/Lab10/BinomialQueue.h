#ifndef BINOMIALQUEUE_H_
#define BINOMIALQUEUE_H_
#include "BQNode.h"
#include "Queue.h"

template<typename T>
class BinomialQueue {
public:
	BinomialQueue();
	virtual ~BinomialQueue();
	void insert(T x);
	bool deletemin();
	void levelorder();

private:
	BQNode<T> **table;
	int orderLength;
	BQNode<T> *head;
	void increaseTable();
	void tableResetPointers();
	BQNode<T> *merge(BQNode<T> *bq1, BQNode<T> *bq2);
	void insert_(BQNode<T> *nextQ);
	void destroy(BQNode<T>* delNode);
};

template<typename T>
BinomialQueue<T>::BinomialQueue() :
		orderLength(10000), head(NULL) {
	table = new BQNode<T>*[orderLength];
	for(int i = 0; i < orderLength; i++) {
		table[i] = NULL;
	}
}

template<typename T>
BinomialQueue<T>::~BinomialQueue() {
	for(int i = 0;i < orderLength;i++) {
		if(table[i] != NULL)
				destroy(table[i]);
	}

}

template<typename T>
void BinomialQueue<T>::destroy(BQNode<T> *delNode) {
	if(delNode->right != NULL)
		destroy(delNode->right);
	if(delNode->first != NULL)
		destroy(delNode->first);
	delete delNode;
}

template<typename T>
void BinomialQueue<T>::tableResetPointers() {
	for(int i = 0;i< orderLength;i++) {
		if(table[i] != NULL) {
			head = table[i];
			return;
		}
	}
	head = NULL;
}

template<typename T>
void BinomialQueue<T>::increaseTable() {
	BQNode<T> *tempTable[orderLength*2];
	BQNode<T> **delTable = table;
		for (T i = 0; i < orderLength; i++) {
			tempTable[i] = table[i];
		}
		orderLength *= 2;
		table = tempTable;
		delete delTable;
}

template<typename T>
void BinomialQueue<T>::insert(T x) {
	BQNode<T> *newNode = new BQNode<T>(x);
	insert_(newNode);
	tableResetPointers();
}

template<typename T>
void BinomialQueue<T>::insert_(BQNode<T> *nextQ) {
	int o = nextQ->order;
	if(o + 2 > orderLength) {
		increaseTable();
	}
  if(table[o] == NULL) {
	  table[o] = nextQ;
  } else {
	  BQNode<T> *mergeNode = merge(nextQ,table[o]);
	  insert_(mergeNode);
	  table[o] = NULL;
  }
}

template<typename T>
bool BinomialQueue<T>::deletemin() {
	if(head == NULL)
		return false;

	BQNode<T> *delNode = head;
	for(int i = 0; i < orderLength; i++) {
		if(table[i] != NULL && delNode->key > table[i]->key)
			delNode = table[i];
	}
	T o = delNode->order;

	BQNode<T> **tempTable = new BQNode<T>*[orderLength];
	BQNode<T> *first = delNode->first;
	for(int i = 0;first != NULL;i++) {
		tempTable[i] = first;
		first = first->right;
	}
	delete delNode;
	table[o] = NULL;

	for(int i = 0;i < o;i++) {
		BQNode<T> *newNode = tempTable[i];
		newNode->left = newNode;
		newNode->right = NULL;
		insert_(newNode);
	}
	delete [] tempTable;

	tableResetPointers();
	return true;
}

template<typename T>
BQNode<T> * BinomialQueue<T>::merge(BQNode<T> *bq1, BQNode<T> *bq2) {
  if (bq1 -> key > bq2 -> key) {
     return merge(bq2, bq1);
  } else {
    if (bq1 -> first == NULL) {
      bq1 -> first = bq2;
      bq1 -> order = bq1 -> order + 1;
    } else {
      bq2 -> left = bq1->first->left;
      bq1 -> first -> left->right = bq2;
      bq1 -> first->left = bq2;
      bq1 -> order = bq1 -> order + 1;


    }
          return bq1;
  }
}


#endif /* BINOMIALQUEUE_H_ */
