#ifndef Tree23_H_
#define Tree23_H_
#include "Queue.h"
#include <cmath>
#include "Node23.h"

template<typename T>
class Tree23 {
private:
	Node23<T>* head;
	void insertHelper(T data, Node23<T>*& node);
	void deleteminHelper(Node23<T>*& node);
	Node23<T>* findMin(Node23<T>*& node);
	Node23<T>* findMax(Node23<T>*& node);
	void deletemaxHelper(Node23<T>*& node);
	bool removeHelper(T data, Node23<T>*& node);
	void splitNode(Node23<T>*& node, Node23<T>*& leftChild,
			Node23<T>*& rightChild);
	Node23<T>* makeTwoNode(T data1, T data2, Node23<T>* node);
	int getHeight(Node23<T>* node, Node23<T>* searchNode, int height);
	Node23<T>*& search(Node23<T>*& node, T data);
	Node23<T>*& nextSibling(Node23<T>*& node, Node23<T>* sibling);
	void destroy(Node23<T>*& node);
	void resetMinSecondAndMinThird(Node23<T>*& node);
	void redistribute(Node23<T>*& node);
	void fixNodes(Node23<T>*& firstNode, Node23<T>*& secondNode,
			Node23<T>*& improperNode, const int whichNode);
	void fixParent(Node23<T>*& node);

public:
	Tree23();
	virtual ~Tree23();
	void insert(T data);
	bool remove(T data);
	void deletemin();
	void deletemax();
	void levelorder();
};

template<typename T>
Tree23<T>::Tree23() :
		head(NULL) {
}

template<typename T>
Tree23<T>::~Tree23() {
	destroy(head);
}

template<typename T>
void Tree23<T>::insert(T data) {
	if (search(head, data) == NULL)
		insertHelper(data, head);
	return;
}

template<typename T>
bool Tree23<T>::remove(T data) {
	Node23<T>*& x = search(head, data);
	return x == NULL ?
			false :
			(x->parent == NULL ?
					removeHelper(data, x) : removeHelper(data, x->parent));
}

template<typename T>
void Tree23<T>::deletemin() {
	Node23<T>* min = findMin(head);
	if (min == NULL)
		return;
	min->parent == NULL ?
			removeHelper(min->key, min) : removeHelper(min->key, min->parent);
}

template<typename T>
void Tree23<T>::deletemax() {
	Node23<T>* max = findMax(head);
	if (max == NULL)
		return;
	max->parent == NULL ?
			removeHelper(max->key, max) : removeHelper(max->key, max->parent);
}

template<typename T>
void Tree23<T>::levelorder() {
	std::cout << "levelorder: " << std::endl;
	if (head == NULL)
		return;
	Queue<Node23<T>*>* q = new Queue<Node23<T>*>();
	Node23<T>* printNode = head;
	q->enqueue(printNode);
	int prevHeight = 0;

	do {
		printNode = q->dequeue();
		int curHeight = getHeight(head, printNode, 0);

		if (curHeight != prevHeight) {
			std::cout << std::endl;
			prevHeight = curHeight;
		}

		if (printNode->isLeaf())
			std::cout << printNode->key << " ";
		else
			std::cout << printNode->minSecond << " " << printNode->minThird
					<< " ";

		if (printNode->first != NULL)
			q->enqueue(printNode->first);
		if (printNode->second != NULL)
			q->enqueue(printNode->second);
		if (printNode->third != NULL)
			q->enqueue(printNode->third);
	} while (!q->isEmpty());

	delete q;

}

template<typename T>
void Tree23<T>::insertHelper(T data, Node23<T>*& node) {
	if (node == NULL)
		node = new Node23<T>(data, NULL);
	else if (node->parent == NULL && node->isLeaf()) {
		node->minSecond = std::max(node->key, data);
		node->first = new Node23<T>(std::min(node->key, data), node);
		node->second = new Node23<T>(std::max(node->key, data), node);
		node->key = -1;
		node->tag = 0;
	} else if (node->isLeaf()) {
		Node23<T>*& parent = node->parent;
		if (node->parent->isTwoNode()) {
			if (data >= parent->minSecond) {
				parent->minThird = data;
				parent->third = new Node23<T>(data, parent);
			} else if (data < parent->minSecond) {
				parent->third = parent->second;
				parent->minThird = findMin(parent->third)->key;
				if (data >= node->key) {
					parent->second = new Node23<T>(data, parent);
				} else {
					//parent->second = new Node23<T>(parent->first->key, parent);
					parent->second = parent->first;
					parent->first = new Node23<T>(data, parent);
				}
				parent->minSecond = findMin(parent->second)->key;
			}
		} else {
			Node23<T>* rightChild;
			Node23<T>* leftChild;
			Node23<T>* parentParent = parent->parent;
			if (data < parent->second->key) {
				leftChild = makeTwoNode(parent->first->key, data, parent);
				rightChild = makeTwoNode(parent->second->key,
						parent->third->key, parent);
			} else {
				leftChild = makeTwoNode(parent->first->key, parent->second->key,
						parent);
				rightChild = makeTwoNode(data, parent->third->key,
						parent);
			}

			delete parent;
			parent = NULL;

			splitNode(parentParent, leftChild, rightChild);
		}
	} else if (data < node->minSecond) {
		node->first->parent = node;
		insertHelper(data, node->first);
	} else if ((node->isTwoNode() && data >= node->minSecond)
			|| (data >= node->minSecond && data < node->minThird)) {
		node->second->parent = node;
		insertHelper(data, node->second);
	} else if (data >= node->minThird) {
		node->third->parent = node;
		insertHelper(data, node->third);
	}
}

template<typename T>
bool Tree23<T>::removeHelper(T data, Node23<T>*& node) {
	if (node == NULL)
		return false;
	else if (node->key == data && node->parent == NULL) {
		delete node;
		head = NULL;
		return true;
	} else if (!node->isTwoNode()) {
		Node23<T>* delNode;
		if (node->first->key == data) {
			delNode = node->first;
			node->first = node->second;
			node->second = node->third;
			node->third = NULL;
			node->minThird = -1;
			node->minSecond = node->second->key;
		} else if (node->second->key == data) {
			delNode = node->second;
			node->second = node->third;
			node->third = NULL;
			node->minThird = -1;
			node->minSecond = node->second->key;
		} else {
			delNode = node->third;
			node->third = NULL;
			node->minThird = -1;
		}
		delete delNode;
		delNode = NULL;
		resetMinSecondAndMinThird(node);

	} else {
		if (node->parent == NULL) {
			if (node->first->key == data) {
				node->key = node->second->key;
				node->tag = 1;
				delete node->first;
				node->first = NULL;
				delete node->second;
				node->second = NULL;
			} else {
				delete node->second;
				node->second = NULL;
				node->key = node->first->key;
				node->tag = 1;
				delete node->first;
				node->first = NULL;
			}
		} else if (node->first->key == data) {
			delete node->first;
			Node23<T>*& sibling = nextSibling(node->parent, node);
			if (!sibling->isTwoNode()) {
				if (node->minSecond >= sibling->minSecond) {
					node->first = sibling->third;
					node->first->parent = node;
					sibling->minThird = -1;
					sibling->third = NULL;
					resetMinSecondAndMinThird(node);
				} else {
					node->first = node->second;
					node->second = sibling->first;
					node->second->parent = node;
					node->minSecond = findMin(node->second)->key;
					sibling->first = sibling->second;
					sibling->second = sibling->third;
					sibling->third = NULL;
					sibling->minSecond = sibling->minThird;
					sibling->minThird = -1;
					resetMinSecondAndMinThird(node);
				}
			} else {
				Node23<T>* previousNode = node;
				insertHelper(node->second->key, sibling);
				if (sibling->parent->parent != NULL) {

					Node23<T>* delNode = sibling->parent;
					sibling->parent = sibling->parent->parent;
					if (sibling->parent->first == delNode)
						sibling->parent->first = sibling;
					else if (sibling->parent->second == delNode)
						sibling->parent->second = sibling;
					else
						sibling->parent->third = sibling;
					delete delNode;
					redistribute(sibling->parent);
				} else if (!sibling->parent->isTwoNode()) {
					Node23<T>* copySibling = sibling;
					if(sibling->parent->first == previousNode) {
					sibling->parent->first = sibling->parent->second;
					sibling->parent->second = sibling->parent->third;
					sibling->parent->minSecond = findMin(
							sibling->parent->second)->key;
					sibling->parent->minThird = -1;
					sibling->parent->third = NULL;
					} else if(sibling->parent->second == previousNode) {
						sibling->parent->second = sibling->parent->third;
						sibling->parent->minSecond = findMin(
							sibling->parent->second)->key;
						sibling->parent->minThird = -1;
						sibling->parent->third = NULL;
					} else {
						sibling->parent->minThird = -1;
						sibling->parent->third = NULL;
					}
					resetMinSecondAndMinThird(copySibling->parent);
				} else {
					Node23<T>* parent = sibling->parent;
					Node23<T>* oldSibling = sibling;
					sibling->parent->first = oldSibling->first;
					sibling->parent->first->parent = parent;
					sibling->parent->third = oldSibling->third;
					sibling->parent->third->parent = parent;
					sibling->parent->second = oldSibling->second;
					sibling->parent->second->parent = parent;
					resetMinSecondAndMinThird(parent);
				}
			}

		} else if (node->second->key == data) {
			delete node->second;
			Node23<T>*& sibling = nextSibling(node->parent, node);
			if (!sibling->isTwoNode()) {
				if (node->minSecond >= sibling->minSecond) {
					node->second = node->first;
					node->first = sibling->third;
					node->minSecond = findMin(node->second)->key;
					sibling->minThird = -1;
					sibling->third = NULL;
					resetMinSecondAndMinThird(node);
				} else {
					node->second = sibling->first;
					node->minSecond = findMin(node->second)->key;
					sibling->first = sibling->second;
					sibling->second = sibling->third;
					sibling->third = NULL;
					sibling->minSecond = sibling->minThird;
					sibling->minThird = -1;
					resetMinSecondAndMinThird(node);
				}
			} else {
				Node23<T>* newNode = new Node23<T>(node->first->key, node->parent);
				insertHelper(newNode->key, sibling);
				if (sibling->parent->parent != NULL) {
					Node23<T>* delNode = sibling->parent;
					sibling->parent = sibling->parent->parent;
					if (sibling->parent->first == delNode)
						sibling->parent->first = sibling;
					else if (sibling->parent->second == delNode)
						sibling->parent->second = sibling;
					else
						sibling->parent->third = sibling;
					delete delNode;
					redistribute(sibling->parent);
				} else if (!sibling->parent->isTwoNode()) {
					Node23<T>* sibParent = sibling->parent;
					if(findMin(sibling->parent->first)->key == newNode->key) {
					sibling->parent->first = sibling->parent->second;
					sibling->parent->second = sibling->parent->third;
					sibling->parent->minSecond = findMin(
							sibling->parent->second)->key;
					sibling->parent->minThird = -1;
					sibling->parent->third = NULL;
					} else if(findMin(sibling->parent->second)->key == newNode->key) {
						sibling->parent->second = sibling->parent->third;
						sibling->parent->minSecond = findMin(
							sibling->parent->second)->key;
						sibling->parent->minThird = -1;
						sibling->parent->third = NULL;
					} else {
						sibling->parent->third = NULL;
						sibling->parent->minThird = -1;

					}
					resetMinSecondAndMinThird(sibParent);

				} else {
					Node23<T>* parent = sibling->parent;
					Node23<T>* oldSibling = sibling;
					sibling->parent->first = oldSibling->first;
					sibling->parent->first->parent = parent;
					sibling->parent->third = oldSibling->third;
					sibling->parent->third->parent = parent;
					sibling->parent->second = oldSibling->second;
					sibling->parent->second->parent = parent;
					resetMinSecondAndMinThird(parent);

				}
			}

		}
	}

	return true;

}

template<typename T>
void Tree23<T>::splitNode(Node23<T>*& node, Node23<T>*& leftChild,
		Node23<T>*& rightChild) {
	if (node == NULL) {
		head = new Node23<T>(findMin(rightChild)->key, leftChild, rightChild,
		NULL);
		head->first->parent = head;
		head->second->parent = head;
		delete node;
	} else if (node->isTwoNode()) {
		if (node->minSecond > leftChild->minSecond) {
			if (node->first->minSecond == findMin(rightChild->first)->key || node->first->minSecond == findMin(leftChild->second)->key)
				node->third = node->second;
			else
				node->third = node->first;
			node->first = leftChild;
			node->first->parent = node;
			node->second = rightChild;
			node->second->parent = node;
			node->minThird = findMin(node->third)->key;
			node->minSecond = findMin(node->second)->key;
		} else {
			node->minThird = findMin(rightChild)->key;
			node->second = leftChild;
			node->second->parent = node;
			node->third = rightChild;
			node->third->parent = node;
		}
	} else {
		Node23<T>* newLeftChild;
		Node23<T>* newRightChild;
		Node23<T>* nodePtr = new Node23<T>(node->minSecond,node->minThird,node->first,node->second,node->third,node->parent);
		if (rightChild->minSecond < nodePtr->second->minSecond) {
			newLeftChild = new Node23<T>(findMin(rightChild)->key, leftChild,
					rightChild, nodePtr->parent);
			leftChild->parent = newLeftChild;
			rightChild->parent = newLeftChild;
			newRightChild = new Node23<T>(findMin(nodePtr->third)->key,
					nodePtr->second, nodePtr->third, nodePtr->parent);

			nodePtr->second->parent = newRightChild;
			nodePtr->third->parent = newRightChild;
			delete node;
		} else if (node->isTwoNode()
				|| rightChild->minSecond < node->third->minSecond) {
			newLeftChild = new Node23<T>(findMin(leftChild)->key, nodePtr->first,
					leftChild, node->parent);
			nodePtr->first->parent = newLeftChild;
			leftChild->parent = newLeftChild;
			newRightChild = new Node23<T>(findMin(node->third)->key, rightChild,
					nodePtr->third, nodePtr->parent);
			rightChild->parent = newRightChild;
			nodePtr->third->parent = newRightChild;
			delete node;
		} else {
			newLeftChild = new Node23<T>(findMin(nodePtr->second)->key,
					node->first, node->second, node->parent);
			nodePtr->first->parent = newLeftChild;
			nodePtr->second->parent = newLeftChild;
			newRightChild = new Node23<T>(findMin(rightChild)->key, leftChild,
					rightChild, nodePtr->parent);
			leftChild->parent = newRightChild;
			rightChild->parent = newRightChild;
			delete node;
		}
		splitNode(nodePtr->parent, newLeftChild, newRightChild);
	}

}

template<typename T>
Node23<T>* Tree23<T>::findMin(Node23<T>*& node) {
	if (node == NULL)
		return NULL;
	return (node->isLeaf()) ? node : findMin(node->first);
}

template<typename T>
Node23<T>* Tree23<T>::findMax(Node23<T>*& node) {
	if (node == NULL)
		return NULL;
	return (node->isLeaf()) ?
			node : findMax((node->isTwoNode()) ? node->second : node->third);
}

template<typename T>
Node23<T>* Tree23<T>::makeTwoNode(T data1, T data2, Node23<T>* node) {
	Node23<T>* returnNode = NULL;
	// The head was changing randomly here sometimes
	Node23<T>* headPtr = new Node23<T>(head->minSecond,head->minThird,head->first,head->second,head->third,NULL);
	Node23<T>* leaf1 = new Node23<T>(data1, returnNode);
	Node23<T>* leaf2 = new Node23<T>(data2, returnNode);
	if(headPtr->first != head->first) {
		head = headPtr;
	}
	if (data1 > data2) {
		returnNode = new Node23<T>(data1, leaf2, leaf1, node);
	} else {
		returnNode = new Node23<T>(data2, leaf1, leaf2, node);
	}
	returnNode->first->parent = returnNode;
	returnNode->second->parent = returnNode;
	return returnNode;
}

template<typename T>
int Tree23<T>::getHeight(Node23<T>* node, Node23<T>* searchNode, int height) {
	if (node == searchNode)
		return height;
	else if (searchNode == NULL && node->first != node) {
		return getHeight(node->first, searchNode, ++height);
	} else if (searchNode != node && searchNode != NULL) {
		if ((searchNode->isLeaf() && searchNode->key < node->minSecond)
				|| (!searchNode->isLeaf()
						&& searchNode->minSecond < node->minSecond))
			return getHeight(node->first, searchNode, ++height);
		else if (!node->isTwoNode()
				&& ((searchNode->isLeaf() && searchNode->key >= node->minThird)
						|| (!searchNode->isLeaf()
								&& searchNode->minSecond >= node->minThird)))
			return getHeight(node->third, searchNode, ++height);
		else
			return getHeight(node->second, searchNode, ++height);
	}
	return height;
}

template<typename T>
Node23<T>*& Tree23<T>::search(Node23<T>*& node, T data) {
	if (node == NULL)
		return node;
	else if (node->isLeaf())
		return node->key == data ? node : node->first;
	else if (data < node->minSecond) {
		node->first->parent = node;
		return search(node->first, data);
	}
	else if (!node->isTwoNode() && data >= node->minThird) {
		node->third->parent = node;
		return search(node->third, data);
	}
	else {
		node->second->parent = node;
		return search(node->second, data);
	}
}

template<typename T>
Node23<T>*& Tree23<T>::nextSibling(Node23<T>*& node, Node23<T>* sibling) {
	if (node->first == sibling) {
		return node->second;
	} else if (node->second == sibling) {
		return node->isTwoNode() ? node->first : node->third;
	} else {
		return node->second;
	}
}

template<typename T>
void Tree23<T>::destroy(Node23<T>*& node) {
	if (node == NULL)
		return;
	else if (node->isTwoNode()) {
		destroy(node->first);
		destroy(node->second);
		delete node;
	} else {
		destroy(node->first);
		destroy(node->second);
		destroy(node->third);
		delete node;
	}
}

template<typename T>
void Tree23<T>::resetMinSecondAndMinThird(Node23<T>*& node) {
	if (node == NULL)
		return;
	node->minSecond = findMin(node->second)->key;
	if (!node->isTwoNode())
		node->minThird = findMin(node->third)->key;
	resetMinSecondAndMinThird(node->parent);
}

template<typename T>
void Tree23<T>::redistribute(Node23<T>*& node) {
	int heightFirst = getHeight(node->first, NULL, 0);
	int heightSecond = getHeight(node->second, NULL, 0);
	if (node->isTwoNode()) {
		if (heightFirst > heightSecond) {
			Node23<T>* delNode = node->first;
			node->first = delNode->first;
			node->first->parent = delNode->parent;
			node->third = node->second;
			node->third->parent = delNode->parent;
			node->second = delNode->second;
			node->second->parent = delNode->parent;
			node->minSecond = findMin(node->second)->key;
			node->minThird = findMin(node->third)->key;
			delete delNode;
		} else {
			Node23<T>* delNode = node->second;
			node->second = delNode->first;
			node->second->parent = node;
			node->third = delNode->second;
			node->third->parent = node;
			node->minSecond = findMin(node->second)->key;
			node->minThird = findMin(node->third)->key;
			delete delNode;
		}
	} else {
		int heightThird = getHeight(node->third, NULL, 0);
		if (heightFirst
				== std::min(std::min(heightFirst, heightSecond), heightThird)) {
			fixNodes(node->second, node->third, node->first, 1);
		} else if (heightSecond
				== std::min(std::min(heightFirst, heightSecond), heightThird)) {
			fixNodes(node->first, node->third, node->second, 2);
		} else {
			fixNodes(node->first, node->second, node->third, 3);
		}
	}
}

template<typename T>
void Tree23<T>::fixNodes(Node23<T>*& firstNode, Node23<T>*& secondNode,
		Node23<T>*& improperNode, const int whichNode) {
	Node23<T>* newImproperNode = new Node23<T>(improperNode->minSecond,
			improperNode->minThird, improperNode->first, improperNode->second,
			improperNode->third, improperNode->parent);
	if (firstNode->isTwoNode() && secondNode->isTwoNode()) {
		if (whichNode == 1) {
			firstNode->third = firstNode->second;
			firstNode->second = firstNode->first;
			firstNode->first = newImproperNode;
			firstNode->first->parent = firstNode;
			firstNode->minThird = firstNode->minSecond;
			firstNode->minSecond = findMin(firstNode->second)->key;
		} else if (whichNode == 2) {
			firstNode->third = newImproperNode;
			firstNode->third->parent = firstNode;
			firstNode->minThird = findMin(newImproperNode)->key;
		} else {
			secondNode->third = newImproperNode;
			secondNode->third->parent = secondNode;
			secondNode->minThird = findMin(newImproperNode)->key;
		}
	} else if (firstNode->isTwoNode() && !secondNode->isTwoNode()) {
		if (whichNode == 1) {
			firstNode->third = firstNode->second;
			firstNode->second = firstNode->first;
			firstNode->first = newImproperNode;
			firstNode->first->parent = firstNode;
			firstNode->minThird = firstNode->minSecond;
			firstNode->minSecond = findMin(firstNode->second)->key;
		} else if (whichNode == 2) {
			Node23<T>* leftChild = new Node23<T>(
					findMin(secondNode->first)->key, newImproperNode,
					secondNode->first, secondNode->parent);
			Node23<T>* rightChild = new Node23<T>(
					findMin(secondNode->third)->key, secondNode->second,
					secondNode->third, secondNode->parent);
			splitNode(secondNode->parent, leftChild, rightChild);
		} else {
			Node23<T>* leftChild = new Node23<T>(findMin(secondNode->second)->key,
					secondNode->first, secondNode->second, secondNode->parent);
			Node23<T>* rightChild = new Node23<T>(findMin(newImproperNode)->key,
					secondNode->third, newImproperNode, secondNode->parent);
			splitNode(secondNode->parent, leftChild, rightChild);
		}
	} else if (!firstNode->isTwoNode() && secondNode->isTwoNode()) {
		if (whichNode == 1) {
			Node23<T>* leftChild = new Node23<T>(findMin(firstNode->first)->key,
					newImproperNode, firstNode->first, firstNode->parent);
			Node23<T>* rightChild = new Node23<T>(findMin(firstNode->third)->key,
					firstNode->second, firstNode->third, firstNode->parent);
			splitNode(secondNode->parent, leftChild, rightChild);
		} else if (whichNode == 2) {
			firstNode->third = newImproperNode;
			firstNode->third->parent = firstNode;
			firstNode->minThird = findMin(newImproperNode)->key;
		} else {
			secondNode->third = newImproperNode;
			secondNode->third->parent = secondNode;
			secondNode->minThird = findMin(newImproperNode)->key;
		}
	} else {
		if (whichNode == 1) {
			Node23<T>* leftChild = new Node23<T>(findMin(firstNode->first)->key,
					newImproperNode, firstNode->first, firstNode->parent);
			Node23<T>* rightChild = new Node23<T>(
					findMin(firstNode->third)->key, firstNode->second,
					firstNode->third, firstNode->parent);
			splitNode(secondNode->parent, leftChild, rightChild);
		} else if (whichNode == 2) {
			Node23<T>* leftChild = new Node23<T>(
					findMin(secondNode->first)->key, newImproperNode,
					secondNode->first, secondNode->parent);
			Node23<T>* rightChild = new Node23<T>(
					findMin(secondNode->third)->key, secondNode->second,
					secondNode->third, secondNode->parent);
			splitNode(secondNode->parent, leftChild, rightChild);
		} else {
			Node23<T>* leftChild = new Node23<T>(
					findMin(secondNode->second)->key, secondNode->first,
					secondNode->second, secondNode->parent);
			Node23<T>* rightChild = new Node23<T>(findMin(newImproperNode)->key,
					secondNode->third, newImproperNode, secondNode->parent);
			splitNode(secondNode->parent, leftChild, rightChild);
		}
	}
	delete improperNode;
	improperNode = NULL;
	fixParent(firstNode->parent);

}

template<typename T>
void Tree23<T>::fixParent(Node23<T>*& node) {
	if (node->first == NULL) {
		node->first = node->second;
		node->second = node->third;
		node->third = NULL;
		node->minSecond = node->minThird;
		node->minThird = -1;
	} else if (node->second == NULL) {
		node->second = node->third;
		node->third = NULL;
		node->minSecond = node->minThird;
		node->minThird = -1;
	} else {
		node->minThird = -1;
	}
}

#endif /* Tree23_H_ */
