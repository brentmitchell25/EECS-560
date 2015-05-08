/*
 * BQNode.h
 *
 *  Created on: Apr 12, 2015
 *      Author: brentmitchell
 */

#ifndef BQNODE_H_
#define BQNODE_H_

template<typename T>
class BQNode {
public:
	BQNode(T k);
	BQNode(T k, BQNode *l, BQNode *f, BQNode *r);
	T key;
	int order;
	BQNode *left;
	BQNode *first;
	BQNode *right;

};

template<typename T>
BQNode<T>::BQNode(T k):key(k),order(0),left(NULL), first(NULL), right(NULL) {

}

template<typename T>
BQNode<T>::BQNode(T k, BQNode *l, BQNode *f, BQNode *r):key(k), order(0), left(l),first(f),right(r) {

}

#endif /* BQNODE_H_ */
