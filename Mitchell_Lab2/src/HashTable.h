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
	List<int> *table;
	int hash(int num);
	bool find(int num);
public:
	HashTable(int size);
	virtual ~HashTable();
	void insert(int num);
	bool remove(int num);
	void print();
};

#endif /* HASHTABLE_H_ */
