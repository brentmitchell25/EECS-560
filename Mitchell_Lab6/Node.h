#ifndef NODE_H_
#define NODE_H_
#include <stddef.h>

template<typename T>
class Node {
 public:
  Node(T k);
  T minSecond;
  T minThird;
  T key;
  T tag;
  Node* first;
  Node* second;
  Node* third;
  Node* parent;
};

template<typename T>
Node<T>::Node(T k) :
key(k), tag(1), first(NULL), second(NULL),third(NULL), parent(NULL), minSecond(-1), minThird(-1) {
}

template<typename T>
Node<T>::Node(T k, Node* p) :
key(k), tag(1), first(NULL), second(NULL),third(NULL), parent(p), minSecond(-1), minThird(-1) {
}

template<typename T>
Node<T>::Node(T ms, T f, T s, Node* p) :
key(-1), tag(-1), first(f), second(s),third(NULL), parent(p), minSecond(ms), minThird(-1) {
}

template<typename T>
Node<T>::Node(T ms, T mt, T f, T s, T t, Node* p) :
key(-1), tag(-1), first(f), second(s),third(t), parent(p), minSecond(ms), minThird(mt) {
}


#endif /* NODE_H_ */
