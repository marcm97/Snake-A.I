#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <map>
#include <limits>
#include <list>
#include <queue>
#include <algorithm>
#include "weightedGraph.h"

typedef pair<int, int> hPair;

class DijkstraSP
{
   map<int, int> prev;
   map<int, double> dist;
   priority_queue<hPair, std::vector<hPair>, greater<hPair>> heap;
   int S;
public:
   DijkstraSP(WeightedGraph *, int);

   void relax(int, Edge);
   double distance(int);
   bool hasPath(int);
   vector<int> pathTo(int);
   vector<int> possibilities();

};

#endif
