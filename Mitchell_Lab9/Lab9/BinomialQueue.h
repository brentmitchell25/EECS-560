/*
 * BinomialQueue.h
 *
 *  Created on: Apr 12, 2015
 *      Author: brentmitchell
 */

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
	BQNode<T> **head;
	BQNode<T> *combineTrees(BQNode<T> *t1, BQNode<T> *t2);
	void merge(BQNode<T> *first, BQNode<T> *second);
};

template<typename T>
BinomialQueue<T>::BinomialQueue() :
		head(NULL) {

}

template<typename T>
BinomialQueue<T>::~BinomialQueue() {

}

template<typename T>
void BinomialQueue<T>::insert(T x) {
	BQNode<T> *newNode = new BQNode<T>(x);
	if(head == NULL)
		head = &newNode;
	else {
	BQNode<T> * iter = *head;
	bool add;
	while(iter != NULL) {
		if((iter)->order == newNode->order) {
			iter = combineTrees(iter,newNode);
			add = true;
		}
		iter = (iter)->right;
	}
	if(head != NULL && !add) {
		newNode->right = *head;
		(*head)->left = newNode;
		head = &newNode;
	}
	}
}

template<typename T>
bool BinomialQueue<T>::deletemin() {

}

template<typename T>
void BinomialQueue<T>::levelorder() {
	Queue<BQNode<T>*> q1;
	Queue<BQNode<T>*> q2;
	Queue<BQNode<T>*> q3;
	q1.enqueue(*head);
	while (!q1.isEmpty()) {
		BQNode<T> *temp = q1.dequeue();
		std::cout << temp->key;
		if (temp->right != NULL)
			q1.enqueue(temp->right);
		if (temp->first != NULL)
			q2.enqueue(temp->first);
		std::cout << std::endl;
		while (!q2.isEmpty() || !q3.isEmpty()) {
			while (!q2.isEmpty()) {
				BQNode<T>* s = q2.dequeue();
				std::cout << s->key << " ";
				if (s->right != NULL)
					q2.enqueue(s->right);
				if (s->first != NULL)
					q3.enqueue(s->first);
			}
			while (!q3.isEmpty()) {
				BQNode<T>* s = q3.dequeue();
				std::cout << s->key << " ";
				if (s->right != NULL)
					q3.enqueue(s->right);
				if (s->first != NULL)
					q2.enqueue(s->first);
			}
		}
		std::cout << std::endl << "---" << std::endl;
	}
}

template<typename T>
void BinomialQueue<T>::merge(BQNode<T> *first, BQNode<T> *second) {
	if (first == second)    // Avoid aliasing problems
		return;

	BQNode<T> *carry = NULL;
	BQNode<T> *iter = head;
	while (iter->right != NULL) {
		BQNode<T> *t1 = iter;
		BQNode<T> *t2 = second;

		int whichCase = t1 == NULL ? 0 : 1;
		whichCase += t2 == NULL ? 0 : 2;
		whichCase += carry == NULL ? 0 : 4;

		switch (whichCase) {
		case 0: /* No trees */
		case 1: /* Only this */
			break;
		case 2: /* Only rhs */
			iter = t2;
			second = NULL;
			break;
		case 4: /* Only carry */
			iter = carry;
			carry = NULL;
			break;
		case 3: /* this and rhs */
			carry = combineTrees(t1, t2);
			iter = second = NULL;
			break;
		case 5: /* this and carry */
			carry = combineTrees(t1, carry);
			iter = NULL;
			break;
		case 6: /* rhs and carry */
			carry = combineTrees(t2, carry);
			iter = NULL;
			break;
		case 7: /* All three */
			iter = carry;
			carry = combineTrees(t1, t2);
			iter = NULL;
			break;
		}
	}

	iter = iter->right;
}

template<typename T>
BQNode<T> * BinomialQueue<T>::combineTrees(BQNode<T> *t1, BQNode<T> *t2) {
	/*
	 if( t2->key < t1->key )
	 return combineTrees( t2, t1 );
	 t2->first = t1->left;
	 t1->left = t2;
	 return t1;
	 */
	if(t1 == NULL) {
		t1 = t2;
	} else if (t1->key <= t2->key) {
		if (t2->order == 0 && t1->order == t2->order) {
			t1->first = t2;
			t1->order = t1->order + 1;
		} else {
			t2->left = t1->first;
			t2->left->right = t2;
			t1->first->left = t2;
			t1->order = t1->order + 1;
		}
	} else {
		combineTrees(t2, t1);
	}
	return t1;

}
#endif /* BINOMIALQUEUE_H_ */
