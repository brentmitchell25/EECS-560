
#ifndef BINARYNODE_H_
#define BINARYNODE_H_
#include <stddef.h>

template<typename T>
class BinaryNode {
public:
	BinaryNode(T k);
	BinaryNode(T k, int ra, BinaryNode<T> *l, BinaryNode<T> *r);
	T key;
	int rank;
	BinaryNode* left;
	BinaryNode* right;
};

template<typename T>
BinaryNode<T>::BinaryNode(T k) :
		key(k), rank(0), left(NULL), right(NULL) {
}

template<typename T>
BinaryNode<T>::BinaryNode(T k, int ra, BinaryNode<T> *l, BinaryNode<T> *r) :
		key(k), rank(ra), left(l), right(r) {
}

#endif /* BINARYNODE_H_ */
