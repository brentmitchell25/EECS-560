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
		std::string data;
		Node *next;
		Node(std::string d, Node *n) :
				data(d), next(n) {
		}
	};
	Node *head;

	void insertHelper(std::string data, Node* n);
	bool eraseHelper(std::string data, Node*& n);
	Node* findHelper(std::string data, Node* n);

public:
	List();
	virtual ~List();
	void insert(std::string data);
	bool isEmpty();
	bool erase(std::string data);
	void print();
	Node* find(std::string data);
};

#endif /* LIST_H_ */
