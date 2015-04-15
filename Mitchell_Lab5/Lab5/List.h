/*
 * List.h
 *
 *  Created on: Mar 4, 2015
 *      Author: brentmitchell
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>

template <typename T>
class List {

private:
	struct Node {
		T data;
		Node *next;
		Node(T d, Node *n) :
				data(d), next(n) {
		}
	};
	Node *head;

	void insertHelper(T data, Node* n);
	bool eraseHelper(T data, Node*& n);
	bool findHelper(T data, Node* n);

public:
	List();
	virtual ~List();
	void insert(T data);
	bool isEmpty();
	bool erase(T data);
	void print();
	bool find(T data);
};

template <typename T>
List<T>::List() {

	head = NULL;
}

template <typename T>
List<T>::~List() {
	Node* iterator = head;
	while (iterator != NULL) {
		Node* oldNode = iterator;
		iterator = iterator->next;
		delete oldNode;
	}
	head = NULL;
}

template <typename T>
void List<T>::insertHelper(T data, List<T>::Node* n) {
	if (n == NULL) {
		n = new Node(data, NULL);
	} else if (n->next == NULL) { // Inserts if following node is empty
		n->next = new Node(data, NULL);
	} else {
		n = n->next;
		insertHelper(data, n);
	}
}

template <typename T>
bool List<T>::eraseHelper(T data, List<T>::Node*& n) {
	if (n == NULL) { // If list is empty
		return false;
	} else if (n->data == data) { // If item is at head of list
		Node* delNode = n;
		n = delNode->next;
		delete delNode;
		return true;
	} else if (n->next != NULL && n->next->data == data) { // Rearrange nodes and delete node
		Node* delNode = n->next;
		n->next = delNode->next;

		delete delNode;
		return true;
	}
	return eraseHelper(data, n->next); // Recurse
}

template <typename T>
bool List<T>::findHelper(T data, List<T>::Node* n) {
	if (n == NULL) {
		return false;
	} else if (n->data == data) {
		return true;
	}

	return findHelper(data, n->next);
}

template <typename T>
void List<T>::insert(T data) {
	if (head == NULL) // Add to head if list is empty
		head = new Node(data, NULL);
	else
		insertHelper(data, head);

}

template <typename T>
bool List<T>::isEmpty() {
	return head == NULL;
}

template <typename T>
bool List<T>::erase(T data) {
	return eraseHelper(data, head);
}

template <typename T>
void List<T>::print() {
	Node* iterator = head;
	while (iterator != NULL) {
		std::cout << iterator->data << " ";
		iterator = iterator->next;
	}
	delete iterator;
}

template <typename T>
bool List<T>::find(T data) {
	return findHelper(data, head);
}

#endif /* LIST_H_ */
