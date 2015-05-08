#ifndef NODE23_H_
#define NODE23_H_
#include <stddef.h>

template<typename T>
class Node23 {
 public:
  Node23(T k, Node23<T>* p);
  Node23(T ms, Node23<T>* f, Node23<T>* s, Node23<T>* p);
  Node23(T ms, T mt, Node23<T>* f, Node23<T>* s, Node23<T>* t, Node23* p);
  T key;
  T tag;
  Node23<T>* first;
  Node23<T>* second;
  Node23<T>* third;
  Node23<T>* parent;
  T minSecond;
  T minThird;
  bool isLeaf();
  bool isTwoNode();
};

template<typename T>
Node23<T>::Node23(T k, Node23<T>* p) :
key(k), tag(1), first(NULL), second(NULL),third(NULL), parent(p), minSecond(-1), minThird(-1) {
}

template<typename T>
Node23<T>::Node23(T ms, Node23<T>* f, Node23<T>* s, Node23<T>* p) :
key(-1), tag(0), first(f), second(s),third(NULL), parent(p), minSecond(ms), minThird(-1) {
}

template<typename T>
Node23<T>::Node23(T ms, T mt, Node23<T>* f, Node23<T>* s, Node23<T>* t, Node23<T>* p) :
key(-1), tag(0), first(f), second(s),third(t), parent(p), minSecond(ms), minThird(mt) {
}

template<typename T>
bool Node23<T>::isLeaf() {
	return (tag != 0) ? true : false;
}

template<typename T>
bool Node23<T>::isTwoNode() {
	return (third == NULL) ? true : false;
}


#endif /* NODE23_H_ */
