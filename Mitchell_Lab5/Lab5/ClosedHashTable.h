/*
 * ClosedHashTable.h
 *
 *  Created on: Mar 4, 2015
 *      Author: brentmitchell
 */

#ifndef CLOSEDHASHTABLE_H_
#define CLOSEDHASHTABLE_H_

#define NO_DATA -1

class ClosedHashTable {
private:
	int m;
	struct Bucket {
		long data;
		bool flag;
		Bucket():data(NO_DATA),flag(false) {}
		Bucket(long d):data(d),flag(false) {}
	};
	Bucket *table;
	long mod(long num);
	bool contains(long num);
public:
	ClosedHashTable(long size);
	virtual ~ClosedHashTable();
	void insert(long num);
	bool remove(long num);
	void print();
	bool isFull();
};

#endif /* CLOSEDHASHTABLE_H_ */
