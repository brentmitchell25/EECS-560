#ifndef QUEUE_H_
#define QUEUE_H_
#include <iostream>

template<typename T>
class Queue {

private:
	struct Node {
		T data;
		Node *next;
		Node(T d, Node *n) :
				data(d), next(n) {
		}
	};
	Node *head;

	void insertHelper(T data, Node*& n);
	bool findHelper(T data, Node* n);

public:
	Queue();
	virtual ~Queue();
	void enqueue(T data);
	bool isEmpty();
	T dequeue();
	void print();
	bool find(T data);
};

template<typename T>
Queue<T>::Queue() {

	head = NULL;
}

template<typename T>
Queue<T>::~Queue() {
	Node* iterator = head;
	while (iterator != NULL) {
		Node* oldNode = iterator;
		iterator = iterator->next;
		delete oldNode;
	}
	head = NULL;
}

template<typename T>
void Queue<T>::insertHelper(T data, Node*& n) {
	if (n == NULL) {
		n = new Node(data, NULL);
	} else if (n->next == NULL) { // Inserts if following node is empty
		n->next = new Node(data, NULL);
	} else {
		insertHelper(data, n->next);
	}
}

template<typename T>
bool Queue<T>::findHelper(T data, Node* n) {
	if (n == NULL) {
		return false;
	} else if (n->data == data) {
		return true;
	}

	return findHelper(data, n->next);
}

template<typename T>
void Queue<T>::enqueue(T data) {
	insertHelper(data, head);
}

template<typename T>
bool Queue<T>::isEmpty() {
	return head == NULL;
}

template<typename T>
T Queue<T>::dequeue() {
	if (isEmpty())
		return NULL;
	T returnPtr = head->data;
	Node* delNode = head;
	head = head->next;
	delete delNode;
	return returnPtr;
}

template<typename T>
void Queue<T>::print() {
	Node* iterator = head;
	while (iterator != NULL) {
		std::cout << iterator->data << " ";
		iterator = iterator->next;
	}
	delete iterator;
}

template<typename T>
bool Queue<T>::find(T data) {
	return findHelper(data, head);
}

#endif /* QUEUE_H_ */
