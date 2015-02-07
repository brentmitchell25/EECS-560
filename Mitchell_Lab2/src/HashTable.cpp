/*
 * HashTable.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: bmitchel
 */

#include "HashTable.h"

HashTable::HashTable(int size) :
		m(size) {
	// TODO Auto-generated constructor stub
	table = new List<int>[m];
	for(int i = 0; i < m; i++) {
		List<int> l;
		table[hash(i)] = l;
	}
}

HashTable::~HashTable() {
	delete[] table;
}

int HashTable::hash(int num) {
	return num % m;
}

bool HashTable::find(int num) {
	return table[hash(num)].find(num);
}

void HashTable::insert(int num) {
	if(!find(num))
		table[hash(num)].insert(num);
}

bool HashTable::remove(int num) {
	return table[hash(num)].erase(num);
}
void HashTable::print() {
	std::cout << std::endl;
	for(int i = 0; i < m; i++) {
		std::cout << i << ": ";
		table[i].print();
		std::cout << std::endl;
	}

}
