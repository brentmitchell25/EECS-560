/*
 * Node.h
 *
 *  Created on: Feb 27, 2015
 *      Author: brentmitchell
 */

#ifndef BINARYNODE_H_
#define BINARYNODE_H_
#include <stddef.h>

template<typename T>
class BinaryNode {
public:
	BinaryNode(T d);
	T data;
	BinaryNode* left;
	BinaryNode* right;
};

template<typename T>
BinaryNode<T>::BinaryNode(T d) :
		data(d), left(NULL), right(NULL) {
}

#endif /* BINARYNODE_H_ */
