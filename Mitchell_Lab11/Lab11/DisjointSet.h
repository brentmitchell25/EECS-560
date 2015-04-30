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
	void unionSets(T x, T y);

private:
	int *set;
};

template<typename T>
DisjointSet<T>::DisjointSet() {
	set = new int[10];
}

template<typename T>
DisjointSet<T>::~DisjointSet() {

}

template<typename T>
SetNode<T> *DisjointSet<T>::find(SetNode<T> *x) {
	if(x->parent->key != x->key)
		x->parent = find(x->parent);
	return x->parent;
}

template<typename T>
void DisjointSet<T>::unionSets(T x, T y) {
	if(set[y->key])
}

#endif /* DISJOINTSET_H_ */
