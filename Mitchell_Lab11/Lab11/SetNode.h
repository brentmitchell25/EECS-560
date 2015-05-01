/*
 * SetNode.h
 *
 *  Created on: Apr 27, 2015
 *      Author: bmitchel
 */

#ifndef SETNODE_H_
#define SETNODE_H_

template<typename T>
class SetNode {
public:
	SetNode();
	SetNode(T k);
	SetNode(T k, int ra, SetNode<T> *p);
	T key;
	int rank;
	SetNode* parent;
};

template<typename T>
SetNode<T>::SetNode() :
		key(-1), rank(0), parent(NULL) {
}

template<typename T>
SetNode<T>::SetNode(T k) :
		key(k), rank(0), parent(this) {
}

template<typename T>
SetNode<T>::SetNode(T k, int ra, SetNode<T> *p) :
		key(k), rank(ra), parent(p) {
}

#endif /* SETNODE_H_ */
