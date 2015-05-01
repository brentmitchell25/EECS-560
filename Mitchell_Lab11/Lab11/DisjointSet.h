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
	SetNode<T> * find(SetNode<T> * x);
	void unionSets(SetNode<T> * set1, SetNode<T> * set2);
	void makeSet(T x);

private:
	SetNode<T> **set;
	T size;
	T length;
};

template<typename T>
DisjointSet<T>::DisjointSet():size(1000),length(0) {
	set = new SetNode<T>*[size];
}

template<typename T>
DisjointSet<T>::~DisjointSet() {
	delete [] set;
}

template<typename T>
SetNode<T> *DisjointSet<T>::find(SetNode<T> * x) {
	T i;
	for(i = 0; i < length-1; i++) {
		if(set[i]->key == x->key) {
			if(set[i] != set[i]->parent) {
				set[i]->parent = find(set[i]->parent);
			}
			break;
		}
	}
	return set[i]->parent;
}

template<typename T>
void DisjointSet<T>::unionSets(SetNode<T> * set1, SetNode<T> * set2) {
	SetNode<T> *xRoot = find(set1);
	SetNode<T> *yRoot = find(set2);
	if(xRoot == yRoot)
		return;

	if(xRoot->rank <= yRoot->rank) {
		if(xRoot->rank == yRoot->rank)
			yRoot->rank++;
		xRoot->parent = yRoot;
	}
	else {
		yRoot->parent = xRoot;

	}
}

template<typename T>
void DisjointSet<T>::makeSet(T x) {
	set[length] = new SetNode<T>(x);
	length++;
}

#endif /* DISJOINTSET_H_ */
