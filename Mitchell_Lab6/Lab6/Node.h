#ifndef NODE_H_
#define NODE_H_
#include <stddef.h>

template<typename T>
class Node {
 public:
  Node(T k, Node<T>* p);
  Node(T ms, Node<T>* f, Node<T>* s, Node<T>* p);
  Node(T ms, T mt, Node<T>* f, Node<T>* s, Node<T>* t, Node* p);
  T key;
  T tag;
  Node<T>* first;
  Node<T>* second;
  Node<T>* third;
  Node<T>* parent;
  T minSecond;
  T minThird;
  bool isLeaf();
  bool isTwoNode();
};

template<typename T>
Node<T>::Node(T k, Node<T>* p) :
key(k), tag(1), first(NULL), second(NULL),third(NULL), parent(p), minSecond(-1), minThird(-1) {
}

template<typename T>
Node<T>::Node(T ms, Node<T>* f, Node<T>* s, Node<T>* p) :
key(-1), tag(0), first(f), second(s),third(NULL), parent(p), minSecond(ms), minThird(-1) {
}

template<typename T>
Node<T>::Node(T ms, T mt, Node<T>* f, Node<T>* s, Node<T>* t, Node<T>* p) :
key(-1), tag(0), first(f), second(s),third(t), parent(p), minSecond(ms), minThird(mt) {
}

template<typename T>
bool Node<T>::isLeaf() {
	return (tag == 1) ? true : false;
}

template<typename T>
bool Node<T>::isTwoNode() {
	return (third == NULL) ? true : false;
}


#endif /* NODE_H_ */
