/*
 * OpenHashTable.h
 *
 *  Created on: Mar 4, 2015
 *      Author: brentmitchell
 */

#ifndef OPENHASHTABLE_H_
#define OPENHASHTABLE_H_
#include "List.h"

class OpenHashTable {
private:
	long m;
	List<long> *table;
	long hash(long num);
	bool find(long num);
public:
	OpenHashTable(long size);
	virtual ~OpenHashTable();
	void insert(long num);
	bool remove(long num);
	void print();
};

#endif /* OPENHASHTABLE_H_ */
