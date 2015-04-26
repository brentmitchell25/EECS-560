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
	List *table;
	int hash(int num);
	bool find(int num);
public:
	HashTable(int size);
	virtual ~HashTable();
	void insert(int x);
	bool remove(int x);
	void print();
};

#endif /* HASHTABLE_H_ */
