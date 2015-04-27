/*
 * DisjointSet.h
 *
 *  Created on: Apr 27, 2015
 *      Author: bmitchel
 */

#ifndef DISJOINTSET_H_
#define DISJOINTSET_H_
#include "SetNode.h"

template<typename T>
class DisjointSet {
public:
	DisjointSet();
	virtual ~DisjointSet();
	SetNode<T> *find(SetNode<T> *x);
	void union(T x, T y);
};

template<typename T>
DisjointSet<T>::DisjointSet() {

}

template<typename T>
DisjointSet<T>::~DisjointSet() {

}

template<typename T>
SetNode<T> *DisjointSet<T>::find(SetNode<T> *x) {
	if(x->parent != x)
		x->parent = find(x->parent);
	return x->parent;
}

template<typename T>
void DisjointSet<T>::union(T x, T y) {

}

#endif /* DISJOINTSET_H_ */
