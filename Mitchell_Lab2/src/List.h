/*
 * List.h
 *
 *  Created on: Jan 26, 2015
 *      Author: brentmitchell
 */

#ifndef LIST_H_
#define LIST_H_
#include <iostream>

class List {

private:
	struct Node {
		int data;
		Node *next;
		Node(int d, Node *n) :
				data(d), next(n) {
		}
	};
	Node *head;

	void insertHelper(int data, Node* n);
	bool eraseHelper(int data, Node*& n);
	bool findHelper(int data, Node* n);

public:
	List();
	virtual ~List();
	void insert(int data);
	bool isEmpty();
	bool erase(int data);
	void print();
	bool find(int data);
};

#endif /* LIST_H_ */
