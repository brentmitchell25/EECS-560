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
	BQNode<T> *merge(BQNode<T> *&t1, BQNode<T> *&t2);
	void destroy();
};

template<typename T>
BinomialQueue<T>::BinomialQueue() :
		head(NULL) {

}

template<typename T>
BinomialQueue<T>::~BinomialQueue() {
	destroy();
}

template<typename T>
void BinomialQueue<T>::destroy() {

}

template<typename T>
void BinomialQueue<T>::insert(T x) {
	BQNode<T> *newNode = new BQNode<T>(x);
	newNode->left = newNode;
	if (head == NULL)
		head = newNode;
	else
		merge(head, newNode);

}

template<typename T>
bool BinomialQueue<T>::deletemin() {
	BQNode<T> *t = head;
	BQNode<T> *delNode = head;
	int min;

	if (head == NULL) {
		return false;
	} else {
		min = head->key;
	}
	while (t != NULL) {
		if (t->key < min) {
			min = t->key;
			delNode = t;
		}
		t = t->right;
	}

	t = delNode->first;
	delNode->left->right = delNode->right;
	if (delNode->right != NULL)
		delNode->right->left = delNode->left;
	if (head == delNode)
		head = delNode->right;
	if (delNode->left->left == delNode)
		delNode->left->left = delNode->left;
	delete delNode;
	delNode = NULL;

	if (t == NULL)
		return true;

	BQNode<T> *iter = t->left;
	BQNode<T> *temp = iter;
	while (temp != t) {
		temp = iter->left;
		iter->left = iter;
		iter->right = NULL;

		merge(head, iter);
		iter = temp;
		if (temp == t)
			break;

	}
	iter->left = iter;
	iter->right = NULL;
	merge(head, iter);
	return true;
}

template<typename T>
void BinomialQueue<T>::levelorder() {
	std::cout << "level order:" << std::endl << std::endl;
	Queue<BQNode<T>*> q1;
	Queue<BQNode<T>*> q2;
	Queue<BQNode<T>*> q3;
	if(head != NULL)
		q1.enqueue(head);
	else
		std::cout << std::endl << "There is nothing in the queue!";
	while (!q1.isEmpty()) {
		BQNode<T> *temp = q1.dequeue();

		std::cout << temp->key;
		if (temp->right != NULL)
			q1.enqueue(temp->right);
		if (temp->first != NULL)
			q2.enqueue(temp->first);

		while (!q2.isEmpty() || !q3.isEmpty()) {
			std::cout << std::endl;
			while (!q2.isEmpty()) {
				BQNode<T>* s = q2.dequeue();
				std::cout << s->key << " ";
				if (s->right != NULL)
					q2.enqueue(s->right);
				if (s->first != NULL)
					q3.enqueue(s->first);
			}
			if(!q3.isEmpty())
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
		if(!q1.isEmpty())
		std::cout << std::endl << "---" << std::endl;
	}
}

template<typename T>
BQNode<T> * BinomialQueue<T>::merge(BQNode<T> *&t1, BQNode<T> *&t2) {

	BQNode<T> *iter = t1;
	if (t1 == NULL)
		t1 = t2;
	else
		while (iter != NULL) {
			if (iter->order > t2->order) {
				if (iter->left != t2)
					t2->left = iter->left;
				t2->right = iter;
				iter->left = t2;
				if (iter == head) {
					head = t2;

				}
				t2 = iter;

			} else if (iter->key <= t2->key) {
				if (t2->order == 0 && iter->order == t2->order && iter != t2) {
					iter->first = t2;
					if (t2->left != t2)
						iter->left = t2->left;
					iter->order = iter->order + 1;
					t2 = iter;
				} else if (iter->order == t2->order && iter != t2) {
					/*
					 if (t2->right != NULL) {
					 iter->left = t2->left;
					 if (t2->right != iter)
					 iter->right = t2->right;
					 else
					 iter->right = NULL;
					 }
					 */
					if (t2->left != t2)
						iter->left = t2->left;
					t2->left = iter->first->left;
					t2->left->right = t2;
					iter->first->left = t2;
					//iter->first->right = t2;

					iter->order = iter->order + 1;

					t2->right = NULL;
					if (t2 == head) {
						head = iter;

					}
					t2 = iter;
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
					iter->left = t2->first->left;
					iter->left->right = iter;
					t2->right = iter->right;
					iter->right = NULL;
					t2->first->left = iter;
					t2->order = t2->order + 1;
					if (iter == head) {
						head = t2;

					}
					t2 = iter;
				} else {
					t2->left = iter;
					t2->right = iter->right;

					if (iter->right == NULL)
						head->left = t2;

					if (iter->right != NULL)
						iter->right->left = t2;
					iter->right = t2;

				}

			}
			iter = iter->right;
		}

}
#endif /* BINOMIALQUEUE_H_ */
