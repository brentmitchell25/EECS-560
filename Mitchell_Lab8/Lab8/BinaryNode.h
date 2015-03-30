#ifndef BINARYNODE_H_
#define BINARYNODE_H_
#include <stddef.h>

template<typename T>
class BinaryNode {
public:
	BinaryNode(T d);
	T key;
	int rank;
	BinaryNode* left;
	BinaryNode* right;
};

template<typename T>
BinaryNode<T>::BinaryNode(T k) :
		key(k), rank(0), left(NULL), right(NULL) {
}

#endif /* BINARYNODE_H_ */
