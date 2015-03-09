#ifndef 23Tree_H_
#define 23Tree_H_
#include "Queue.h"
#include "Node.h"

template<typename T>
class BinarySearchTree {
private:
	Node<T>* head;
	Node<T>* searchHelper(T data, Node<T>* node);
	void insertHelper(T data, Node<T>*& node);
	void deleteminHelper(Node<T>*& node);
	Node<T>* findMin(Node<T>*& node);
	Node<T>* findMax(Node<T>*& node);
	void deletemaxHelper(Node<T>*& node);
	bool removeHelper(T data, Node<T>*& node);
	void preorderTraversal(Node<T>* node);
	void inorderTraversal(Node<T>* node);
	bool isLeaf(Node<T>* node);
	void postorderDestructor(Node<T>* node);
public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void insert(T data);
	bool remove(T data);
	Node<T>* search(T data);
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
void BinarySearchTree<T>::postorderDestructor(Node<T>* node) {
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
Node<T>* BinarySearchTree<T>::search(T data) {
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
	Queue<Node<T>*>* q = new Queue<Node<T>*>();
	Node<T>* printNode = head;
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
Node<T>* BinarySearchTree<T>::searchHelper(T data, Node<T>* node) {
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
void BinarySearchTree<T>::insertHelper(T data, Node<T>*& node) {
	if (node == NULL)
		node = new Node<T>(data);
	else if (data < node->data)
		insertHelper(data, node->left);
	else
		insertHelper(data, node->right);
}

template<typename T>
void BinarySearchTree<T>::deleteminHelper(Node<T>*& node) {
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
void BinarySearchTree<T>::deletemaxHelper(Node<T>*& node) {
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
Node<T>* BinarySearchTree<T>::findMin(Node<T>*& node) {
	if (node == NULL)
		return NULL;
	return node->left == NULL ? node : findMin(node->left);
}

template<typename T>
Node<T>* BinarySearchTree<T>::findMax(Node<T>*& node) {
	if (node == NULL)
		return NULL;
	return node->right == NULL ? node : findMin(node->right);
}

template<typename T>
bool BinarySearchTree<T>::removeHelper(T data, Node<T>*& node) {
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
		Node<T>* delNode = node;
		node = node->left == NULL ? node->right : node->left;
		delete delNode;
		return true;
	}
}

template<typename T>
void BinarySearchTree<T>::preorderTraversal(Node<T>* node) {
	if (node == NULL)
		return;

	std::cout << node->data << " ";
	preorderTraversal(node->left);
	preorderTraversal(node->right);
}

template<typename T>
void BinarySearchTree<T>::inorderTraversal(Node<T>* node) {
	if (node == NULL)
		return;

	inorderTraversal(node->left);
	std::cout << node->data << " ";
	inorderTraversal(node->right);
}

template<typename T>
bool BinarySearchTree<T>::isLeaf(Node<T>* node) {
	return node->left == NULL && node->right == NULL ? true : false;
}

#endif /* 23TREE_H_ */
