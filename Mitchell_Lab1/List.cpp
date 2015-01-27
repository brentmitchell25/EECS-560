/*
 * List.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: brentmitchell
 */

#include <List.h>

List::List() {
	head = new Node("", NULL);
}

List::~List() {
	delete head;
}

void List::insertHelper(std::string data, List::Node* n) {
	if (n == NULL) {
		n->data = data;
	} else if (n->next == NULL) {
		n->next = new Node(data, NULL);
	} else {
		n = n->next;
		insertHelper(data, n);
	}
}

List::Node* List::eraseHelper(std::string data, List::Node* n) {
	if (n == NULL) {
		return NULL;
	} else if (n->data == data) {
		Node* temp = n->next;
		delete n;
		return temp;
	}
	n->next = eraseHelper(data, n->next);

	return n;
}

List::Node* List::findHelper(std::string data, List::Node* n) {
	if (n == NULL) {
		return NULL;
	} else if (n->data == data) {
		return n;
	}

	return findHelper(data, n->next);
}

void List::insert(std::string data) {
	insertHelper(data, head);
}

bool List::isEmpty() {
	if (head == NULL) {
		return true;
	}
	return false;
}

void List::erase(std::string data) {
	head = eraseHelper(data, head);
}

void List::print() {
	Node* iterator = head;
	std::cout << "List: ";
	while (iterator != NULL) {
		std::cout << iterator->data << " ";
		iterator = iterator->next;
	}
	delete iterator;
}

List::Node* List::find(std::string data) {
	return findHelper(data, head);
}
