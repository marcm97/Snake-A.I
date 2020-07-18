#include "dijkstra.h"

//constructor
DijkstraSP::DijkstraSP(WeightedGraph *G, int s):S(s)
{
  int count=0;
  for (int i : G->Vertices())
  {
    dist[i]=std::numeric_limits<double>::infinity();
  }
  dist[S]=0.0;
  heap.push(make_pair(0,S));
  while(!heap.empty())
  {
    count+=1;
    hPair v = heap.top();
    heap.pop();
    for (Edge e: G->adj(v.second))
      relax(v.second,e);
  }

}

//function to relax edges
void DijkstraSP::relax(int v, Edge e)
{
  int w=e.other(v);
  if (e.Weight()<0)
  {
    cout<<"negative weight encountered";
    exit(0);
  }

  if (dist[w]>dist[v]+e.Weight())
  {
    dist[w]=dist[v]+e.Weight();
    prev[w]=v;
    heap.push(make_pair(dist[w],w));
  }

}

//function to check if there is a path to a vertex
bool DijkstraSP::hasPath(int v)
{
  if(dist.find(v)!=dist.end())
    return dist[v]!=std::numeric_limits<double>::infinity();
  return false;
}

//find vector path to a given vertex
vector <int> DijkstraSP::pathTo(int v)
{
  int temp;
  temp = v;
  vector<int> l1;
  l1.clear();
  while(temp!=S)
  {
    l1.push_back(temp);
    temp = prev[temp];
  }
  reverse(l1.begin(), l1.end());
  return l1;
}

//vertexes that can be reached from start
vector<int> DijkstraSP::possibilities()
{
  vector<int> v1;
  for(auto &u: dist)
  {
    if (u.second!=std::numeric_limits<double>::infinity())
    {
      v1.push_back(u.first);
    }
  }

  std::random_shuffle (v1.begin(), v1.end());
  return v1;
}

//return weighted distance
double DijkstraSP::distance(int v)
{
  return dist[v];
}
