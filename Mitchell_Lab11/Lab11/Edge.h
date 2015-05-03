/*
 * Edge.h
 *
 *  Created on: May 2, 2015
 *      Author: brentmitchell
 */

#ifndef EDGE_H_
#define EDGE_H_

class Edge {
public:
	Edge();
	Edge(int v, int w, int cost);
	virtual ~Edge();
	bool operator==(const Edge& rhs);
	bool operator<(const Edge& rhs);
	bool operator>(const Edge& rhs);
	bool operator<=(const Edge& rhs);
	bool operator>=(const Edge& rhs);
	int v;
	int w;
	int cost;

};

Edge::Edge(): v(0), w(0), cost(0) {

}

Edge::Edge(int a, int b, int c): v(a), w(b), cost(c) {

}

Edge::~Edge(){

}

bool Edge::operator==(const Edge& rhs) {
	return this->cost == rhs.cost;
}

bool Edge::operator>(const Edge& rhs) {
	return this->cost > rhs.cost;
}
bool Edge::operator<(const Edge& rhs) {
	return this->cost < rhs.cost;
}

bool Edge::operator<=(const Edge& rhs) {
	return this->cost <= rhs.cost;
}

bool Edge::operator>=(const Edge& rhs) {
	return this->cost >= rhs.cost;
}

#endif /* EDGE_H_ */
