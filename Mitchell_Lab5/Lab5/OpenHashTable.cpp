/*
 * OpenHashTable.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: brentmitchell
 */

#include "OpenHashTable.h"
#include "List.h"

OpenHashTable::OpenHashTable(long size) :
		m(size) {
	// TODO Auto-generated constructor stub
	table = new List<long>[m];
	for(long i = 0; i < m; i++) {
		List<long> l;
		table[hash(i)] = l;
	}
}

OpenHashTable::~OpenHashTable() {
	delete[] table;
}

long OpenHashTable::hash(long num) {
	return num % m;
}

bool OpenHashTable::find(long num) {
	return table[hash(num)].find(num);
}

void OpenHashTable::insert(long num) {
	if(!find(num))
		table[hash(num)].insert(num);
}

bool OpenHashTable::remove(long num) {
	return table[hash(num)].erase(num);
}
void OpenHashTable::print() {
	std::cout << std::endl;
	for(long i = 0; i < m; i++) {
		std::cout << i << ": ";
		table[i].print();
		std::cout << std::endl;
	}

}
