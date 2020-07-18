#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "edge.h"

using namespace std;

typedef map<int, multiset<Edge>> map_t2;
/********************************************************************//**
 * @class WeightedGraph
 **********************************************************************/
class WeightedGraph
{
   int numVertices, numEdges;
   map_t2 edges;
   set<int> vertices;
public:
   WeightedGraph();
   WeightedGraph(istream &);
   WeightedGraph(const int *grid, int width, int height,int weightPower);
   void addEdge(Edge);
   multiset<Edge> adj(int);
   multiset<Edge> Edges();
   set<int> Vertices() const;
   int V() const;
   int E() const;
};
#endif
