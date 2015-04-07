/*
 * HashTable.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: bmitchel
 */

#include "HashTable.h"
#include <cmath>
#include <iostream>
#define NO_DATA -1

HashTable::HashTable(int size) :
		m(size) {
	table = new Bucket[m];
}

HashTable::~HashTable() {
	delete[] table;
}

int HashTable::mod(int num) {
	return num % m;
}

bool HashTable::contains(int num) {

	for (int i = 0; i < m; i++) {
		int hx = mod(num + pow(i,2));
		if (table[mod(hx)].data == num)
			return true;
	}
	return false;
}

void HashTable::insert(int num) {
	if (!contains(num)) {
		Bucket b(num);
		for (int i = 0; i < m; i++) {
		  int hx = mod(mod(num) + pow(i,1));
			if (table[hx].data == NO_DATA) {
				table[hx] = b;
				return;
			}
		}

	}
}

bool HashTable::remove(int num) {
	for (int i = 0; i < m; i++) {
			int hx = mod(mod(num) + pow(i,2));
			if (table[hx].data == num) {
				table[hx].data = NO_DATA;
				table[hx].flag = true;
				return true;
			}
		}
	return false;
}

void HashTable::print() {
	std::cout << std::endl;
	for (int i = 0; i < m; i++) {
		std::cout << i << ": " << table[i].data << " flag = " << (table[i].flag ? "true" : "false") << std::endl;
	}
}

bool HashTable::isFull() {
	for(int i = 0; i < m; i++) {
		if(table[i].data == NO_DATA)
			return false;
	}
	return true;
}
