/*
 * List.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: brentmitchell
 */

#include "List.h"
#include <string>

List::List() {

	head = NULL;
}

List::~List() {
	Node* iterator = head;
	while (iterator != NULL) {
		Node* oldNode = iterator;
		iterator = iterator->next;
		delete oldNode;
	}
	delete head;
}

void List::insertHelper(std::string data, List::Node* n) {
	if (n == NULL) {
		n = new Node(data, NULL);
	} else if (n->next == NULL) { // Inserts if following node is empty
		n->next = new Node(data, NULL);
	} else {
		n = n->next;
		insertHelper(data, n);
	}
}

bool List::eraseHelper(std::string data, List::Node*& n) {
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

List::Node* List::findHelper(std::string data, List::Node* n) {
	if (n == NULL) {
		return NULL;
	} else if (n->data == data) {
		return n;
	}

	return findHelper(data, n->next);
}

void List::insert(std::string data) {
	if (head == NULL) // Add to head if list is empty
		head = new Node(data, NULL);
	else
		insertHelper(data, head);

}

bool List::isEmpty() {
	return head == NULL;
}

bool List::erase(std::string data) {
	return eraseHelper(data, head);
}

void List::print() {
	Node* iterator = head;
	std::cout << "\nList: ";
	while (iterator != NULL) {
		std::cout << iterator->data << " ";
		iterator = iterator->next;
	}
	delete iterator;
}

List::Node* List::find(std::string data) {
	return findHelper(data, head);
}
