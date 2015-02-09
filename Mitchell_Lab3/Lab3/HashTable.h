/*
 * HashTable.h
 *
 *  Created on: Feb 2, 2015
 *      Author: bmitchel
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include "List.h"

class HashTable {
private:
	int m;
	struct Bucket {
		int data;
		bool flag;
		Bucket():data(-1),flag(false) {}
		Bucket(int d):data(d),flag(false) {}
	};
	Bucket *table;
	int hash(int num);
	bool contains(int num);
public:
	HashTable(int size);
	virtual ~HashTable();
	void insert(int num);
	bool remove(int num);
	void print();
	bool isFull();
};

#endif /* HASHTABLE_H_ */
