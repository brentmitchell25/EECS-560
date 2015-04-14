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
	BQNode<T> *head;
	BQNode<T> *combineTrees(BQNode<T> *&t1, BQNode<T> *&t2);
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
	newNode->left = newNode;
	if (head == NULL)
		head = newNode;
	else

		combineTrees(head, newNode);

}

template<typename T>
bool BinomialQueue<T>::deletemin() {

}

template<typename T>
void BinomialQueue<T>::levelorder() {
	Queue<BQNode<T>*> q1;
	Queue<BQNode<T>*> q2;
	Queue<BQNode<T>*> q3;
	q1.enqueue(head);
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
			std::cout << std::endl;
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
		BQNode<T> *iter = iter;
		BQNode<T> *t2 = second;

		int whichCase = iter == NULL ? 0 : 1;
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
			carry = combineTrees(iter, t2);
			iter = second = NULL;
			break;
		case 5: /* this and carry */
			carry = combineTrees(iter, carry);
			iter = NULL;
			break;
		case 6: /* rhs and carry */
			carry = combineTrees(t2, carry);
			iter = NULL;
			break;
		case 7: /* All three */
			iter = carry;
			carry = combineTrees(iter, t2);
			iter = NULL;
			break;
		}
	}

	iter = iter->right;
}

template<typename T>
BQNode<T> * BinomialQueue<T>::combineTrees(BQNode<T> *&t1, BQNode<T> *&t2) {
	/*
	 if( t2->key < iter->key )
	 return combineTrees( t2, iter );
	 t2->first = iter->left;
	 iter->left = t2;
	 return iter;
	 */

	BQNode<T> *iter = t1;
	while (iter != NULL) {
		if (iter->order > t2->order) {
			t2->left = iter->left;
			t2->right = iter;
			iter->left = t2;
			if (iter == head) {
				head = t2;

			}
		t2 = iter;

		} else if (iter->key <= t2->key) {
			if (t2->order == 0 && iter->order == t2->order) {
				iter->first = t2;
				iter->order = iter->order + 1;
				iter = t2;
			} else if (iter->order == t2->order) {
				if (t2->right != NULL) {
					iter->left = t2->left;
					if (t2->right != iter)
						iter->right = t2->right;
					else
						iter->right = NULL;
				}
				t2->left = iter->first;
				t2->left->right = t2;
				iter->first->left = t2;
				iter->first->right = t2;
				iter->order = iter->order + 1;

				t2->left = t2;
				t2->right = NULL;
				if (t2 == head)
					head = iter;
			}

		} else {
			if (t2->order == 0 && iter->order == t2->order) {
				t2->first = iter;
				t2->right = iter->right;
				t2->left = iter->left;
				t2->order = t2->order + 1;

				if (iter == head)
					head = t2;
				if (iter->right != NULL)
					iter->right->left = t2;

				iter->left = iter;
				iter->right = NULL;
				iter = t2;
			} else if (iter->order == t2->order) {
				iter->left = t2->first;
				iter->left->right = iter;
				iter->left = iter;
				iter->right = NULL;
				t2->first->left = iter;
				t2->order = t2->order + 1;
				if (iter == head)
					head = t2;
			}

		}
		iter = iter->right;
	}

}
#endif /* BINOMIALQUEUE_H_ */
