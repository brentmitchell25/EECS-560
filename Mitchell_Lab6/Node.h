#ifndef NODE_H_
#define NODE_H_
#include <stddef.h>

template<typename T>
class Node {
public:
	Node(T d);
	T data;
	Node* left;
	Node* right;
};

template<typename T>
Node<T>::Node(T d) :
		data(d), left(NULL), right(NULL) {
}

#endif /* NODE_H_ */
