/*
 * MinimumSpanningTree.h
 *
 *  Created on: Apr 26, 2015
 *      Author: brentmitchell
 */

#ifndef MINIMUMSPANNINGTREE_H_
#define MINIMUMSPANNINGTREE_H_
#include "MinLeftistHeap.h"
#include "Edge.h"
#include "DisjointSet.h"
#include "SetNode.h"
#include "Set.h"
#include <limits.h>

class MinimumSpanningTree {
public:
	MinimumSpanningTree();
	virtual ~MinimumSpanningTree();
	void kruskal(int adjMat[], int dim);
	void prim(int adjMat[], int dim);
private:
	int minKey(int key[], bool mstSet[], int dim);
	void printMST(int parent[], int n, int graph[],int dim);
};

MinimumSpanningTree::MinimumSpanningTree() {

}

MinimumSpanningTree::~MinimumSpanningTree() {

}

void MinimumSpanningTree::kruskal(int adjMat[], int dim) {
	MinLeftistHeap<Edge> mlh;
	DisjointSet<int> ds;
	Set s(dim);
	for(int i = 0; i < dim; i++) {
		for(int j = i * dim; j < (i + 1) * dim; j++) {
			ds.makeSet(i * dim + j);
			if(adjMat[j] > 0) {
			Edge e(i,j%dim,adjMat[j]);
			mlh.insert(e);

			}
		}
	}

	std::cout << "Kruskal: ";
	for(int i = 0; i < dim * dim; i++) {
		Edge *e = mlh.deletemin();
		if(e == NULL)
			break;
		SetNode<int> v(e->v);
		SetNode<int> w(e->w);
		if(ds.find(&v) != ds.find(&w)) {
			std:: cout << "(" << e->v << "," << e->w <<") ";
			ds.unionSets(&v,&w);
		}
	}
	std::cout << std::endl;

}

void MinimumSpanningTree::prim(int adjMat[], int dim) {
	int graph[dim][dim];
		for(int i = 0; i < dim; i++) {
		for(int j = i * dim; j < (i + 1) * dim; j++) {
			graph[i][j] = adjMat[j];
		}
		}
	int parent[dim]; // Array to store constructed MST
	     int key[dim];   // Key values used to pick minimum weight edge in cut
	     bool mstSet[dim];  // To represent set of vertices not yet included in MST

	     // Initialize all keys as INFINITE
	     for (int i = 0; i < dim; i++)
	        key[i] = INT_MAX, mstSet[i] = false;

	     // Always include first 1st vertex in MST.
	     key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
	     parent[0] = -1; // First node is always root of MST

	     // The MST will have V vertices
	     for (int count = 0; count < dim-1; count++)
	     {
	        // Pick thd minimum key vertex from the set of vertices
	        // not yet included in MST
	        int u = minKey(key, mstSet, dim);

	        // Add the picked vertex to the MST Set
	        mstSet[u] = true;

	        // Update key value and parent index of the adjacent vertices of
	        // the picked vertex. Consider only those vertices which are not yet
	        // included in MST
	        for (int v = 0; v < dim; v++)

	           // graph[u][v] is non zero only for adjacent vertices of m
	           // mstSet[v] is false for vertices not yet included in MST
	           // Update the key only if graph[u][v] is smaller than key[v]
	          if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
	             parent[v]  = u, key[v] = graph[u][v];
	     }
	     for(int i = 0; i < dim; i ++)
	    	 for(int j = i * dim; j < (i + 1) * dim; j++)
	    		 adjMat[j] = graph[i][j%dim];
	     printf("Prim:");
   for (int i = 1; i < dim; i++)
      std::cout << "(" << parent[i] << "," << i << ") ";
   std::cout << std::endl;


}

int MinimumSpanningTree::minKey(int key[], bool mstSet[], int dim)
{
   // Initialize min value
   int min = INT_MAX, min_index;

   for (int v = 0; v < dim; v++)
     if (mstSet[v] == false && key[v] < min)
         min = key[v], min_index = v;

   return min_index;
}

// A utility function to print the constructed MST stored in parent[]
void MinimumSpanningTree::printMST(int parent[], int n, int graph[],int dim)
{
	int adj[dim][dim];
	for(int i = 0; i < dim; i++) {
			for(int j = i * dim; j < (i + 1) * dim; j++) {
				adj[i][j] = graph[j];
			}
			}
   printf("Prim:\n");
   for (int i = 1; i < dim; i++)
      std::cout << "(" << parent[i] << "," << i << ") ";
}

#endif /* MINIMUMSPANNINGTREE_H_ */

