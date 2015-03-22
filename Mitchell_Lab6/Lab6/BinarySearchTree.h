/*
 * BinarySearchTree.h
 *
 *  Created on: Feb 22, 2015
 *      Author: brentmitchell
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_
#include "BinaryNode.h"
#include "Queue.h"

template<typename T>
class BinarySearchTree {
private:
	BinaryNode<T>* head;
	BinaryNode<T>* searchHelper(T data, BinaryNode<T>* node);
	void insertHelper(T data, BinaryNode<T>*& node);
	void deleteminHelper(BinaryNode<T>*& node);
	BinaryNode<T>* findMin(BinaryNode<T>*& node);
	BinaryNode<T>* findMax(BinaryNode<T>*& node);
	void deletemaxHelper(BinaryNode<T>*& node);
	bool removeHelper(T data, BinaryNode<T>*& node);
	void preorderTraversal(BinaryNode<T>* node);
	void inorderTraversal(BinaryNode<T>* node);
	bool isLeaf(BinaryNode<T>* node);
	void postorderDestructor(BinaryNode<T>* node);
public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void insert(T data);
	bool remove(T data);
	BinaryNode<T>* search(T data);
	void deletemin();
	void deletemax();
	void preorder();
	void inorder();
	void levelorder();
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree() :
		head(NULL) {
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
	postorderDestructor(head);
}

template<typename T>
void BinarySearchTree<T>::postorderDestructor(BinaryNode<T>* node) {
	if (node == NULL)
		return;
	postorderDestructor(node->left);
	postorderDestructor(node->right);
	delete node;
}

template<typename T>
void BinarySearchTree<T>::insert(T data) {
	insertHelper(data, head);
}

template<typename T>
bool BinarySearchTree<T>::remove(T data) {
	return removeHelper(data, head);
}

template<typename T>
BinaryNode<T>* BinarySearchTree<T>::search(T data) {
	return searchHelper(data, head);
}

template<typename T>
void BinarySearchTree<T>::deletemin() {
	return deleteminHelper(head);
}

template<typename T>
void BinarySearchTree<T>::deletemax() {
	return deletemaxHelper(head);
}

template<typename T>
void BinarySearchTree<T>::preorder() {
	std::cout << "preorder: ";
	preorderTraversal(head);
}

template<typename T>
void BinarySearchTree<T>::inorder() {
	std::cout << "inorder: ";
	inorderTraversal(head);
}

template<typename T>
void BinarySearchTree<T>::levelorder() {
	std::cout << "levelorder: ";
	if (head == NULL)
		return;
	Queue<BinaryNode<T>*>* q = new Queue<BinaryNode<T>*>();
	BinaryNode<T>* printNode = head;
	q->enqueue(printNode);

	do {
		printNode = q->dequeue();
		std::cout << printNode->data << " ";
		if (printNode->left != NULL)
			q->enqueue(printNode->left);
		if (printNode->right != NULL)
			q->enqueue(printNode->right);
	} while (!q->isEmpty());

	delete q;

}

template<typename T>
BinaryNode<T>* BinarySearchTree<T>::searchHelper(T data, BinaryNode<T>* node) {
	if (node == NULL)
		return NULL;
	else if (node->data == data)
		return node;
	if (data < node->data)
		return searchHelper(data, node->left);
	else
		return searchHelper(data, node->right);
}

template<typename T>
void BinarySearchTree<T>::insertHelper(T data, BinaryNode<T>*& node) {
	if (node == NULL)
		node = new BinaryNode<T>(data);
	else if (data < node->data)
		insertHelper(data, node->left);
	else
		insertHelper(data, node->right);
}

template<typename T>
void BinarySearchTree<T>::deleteminHelper(BinaryNode<T>*& node) {
	if (node == NULL)
		return;
	else if (isLeaf(node)) {
		delete node;
		node = NULL;
	} else if (node->left == NULL && node->right != NULL) {
		node->data = findMin(node->right)->data;
		removeHelper(node->data, node->right);
	} else if (node->left->left == NULL) {
		delete node->left;
		node->left = NULL;
	} else
		deleteminHelper(node->left);
}

template<typename T>
void BinarySearchTree<T>::deletemaxHelper(BinaryNode<T>*& node) {
	if (node == NULL)
		return;
	else if (isLeaf(node)) {
		delete node;
		node = NULL;
	} else if (node->right == NULL && node->left != NULL) {
		node->data = findMax(node->left)->data;
		removeHelper(node->data, node->left);
	} else if (node->right->right == NULL) {
		delete node->right;
		node->right = NULL;
	} else
		deletemaxHelper(node->right);

}

template<typename T>
BinaryNode<T>* BinarySearchTree<T>::findMin(BinaryNode<T>*& node) {
	if (node == NULL)
		return NULL;
	return node->left == NULL ? node : findMin(node->left);
}

template<typename T>
BinaryNode<T>* BinarySearchTree<T>::findMax(BinaryNode<T>*& node) {
	if (node == NULL)
		return NULL;
	return node->right == NULL ? node : findMin(node->right);
}

template<typename T>
bool BinarySearchTree<T>::removeHelper(T data, BinaryNode<T>*& node) {
	if (node == NULL)
		return false;
	else if (data < node->data)
		return removeHelper(data, node->left);
	else if (data > node->data)
		return removeHelper(data, node->right);
	else if (node->left != NULL && node->right != NULL) {
		node->data = findMin(node->right)->data;
		return removeHelper(node->data, node->right);
	} else {
		BinaryNode<T>* delNode = node;
		node = node->left == NULL ? node->right : node->left;
		delete delNode;
		return true;
	}
}

template<typename T>
void BinarySearchTree<T>::preorderTraversal(BinaryNode<T>* node) {
	if (node == NULL)
		return;

	std::cout << node->data << " ";
	preorderTraversal(node->left);
	preorderTraversal(node->right);
}

template<typename T>
void BinarySearchTree<T>::inorderTraversal(BinaryNode<T>* node) {
	if (node == NULL)
		return;

	inorderTraversal(node->left);
	std::cout << node->data << " ";
	inorderTraversal(node->right);
}

template<typename T>
bool BinarySearchTree<T>::isLeaf(BinaryNode<T>* node) {
	return node->left == NULL && node->right == NULL ? true : false;
}

#endif /* BINARYSEARCHTREE_H_ */
