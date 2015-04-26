/*
 * ClosedHashTable.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: brentmitchell
 */

#include "ClosedHashTable.h"
#include <cmath>
#include <iostream>
#define NO_DATA -1

ClosedHashTable::ClosedHashTable(long size) :
		m(size) {
	table = new Bucket[m];
}

ClosedHashTable::~ClosedHashTable() {
	delete[] table;
}

long ClosedHashTable::mod(long num) {
	return num % m;
}

bool ClosedHashTable::contains(long num) {

	for (long i = 0; i < m; i++) {
		long hx = mod(mod(num) + pow(i,2));
		if (table[hx].data == num)
			return true;
	}
	return false;
}

void ClosedHashTable::insert(long num) {

		Bucket b(num);
		for (long i = 0; i < m; i++) {
		  long hx = mod(mod(num) + pow(i,2));
		  if(table[hx].data == hx)
			  return;
		  else if (table[hx].data == NO_DATA) {
				table[hx] = b;
				return;
			}
		}


}

bool ClosedHashTable::remove(long num) {
	for (long i = 0; i < m; i++) {
			long hx = mod(mod(num) + pow(i,2));
			if (table[hx].data == num) {
				table[hx].data = NO_DATA;
				table[hx].flag = true;
				return true;
			}
		}
	return false;
}

void ClosedHashTable::print() {
	std::cout << std::endl;
	for (long i = 0; i < m; i++) {
		std::cout << i << ": " << table[i].data << " flag = " << (table[i].flag ? "true" : "false") << std::endl;
	}
}

bool ClosedHashTable::isFull() {
	for(long i = 0; i < m; i++) {
		if(table[i].data == NO_DATA)
			return false;
	}
	return true;
}
