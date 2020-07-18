#include "weightedGraph.h"
#include <algorithm>
#include <time.h>
#include <math.h>
//Weighted Graph Constructor
WeightedGraph::WeightedGraph() : numVertices(0), numEdges(0){}

//Constructor that takes a stream object of edges as input
WeightedGraph::WeightedGraph(istream &fin)
{
  int v, w;

  double weight;
  //read in edges
  while(fin >> v >> w >> weight)
  {
    addEdge(Edge(v,w,weight));
    numEdges+=1;
  }
  numVertices=vertices.size();
}

//Construtor that takes a 2d matrix input of edges
WeightedGraph::WeightedGraph(const int *grid, int width, int height, int weightPower=3) : numVertices(0), numEdges(0)
{
  int row, col;

  for (int index=0;index<height*width;index++)
  {
    row = index / width;
    col = index % width;

    double weight =0;
    int upIndex = (row-1)*width + col;
    int downIndex = (row+1)*width +col;
    int leftIndex = row*width +col-1;
    int rightIndex = row*width +col+1;


    if(((row-1)>=0) && (grid[upIndex]!=1) && (grid[index]!=1))
    {
      weight = min(abs(width-col),abs(0-col));
      addEdge(Edge(index,upIndex,10*pow(weight,weightPower)));
      numEdges+=1;
    }

    if(((row+1)<height) && (grid[downIndex]!=1) && (grid[index]!=1))
    {
      weight = min(abs(width-col),abs(0-col));
      addEdge(Edge(index,downIndex,10*pow(weight,weightPower)));
      numEdges+=1;
    }

    if(((col+1)<width) && (grid[rightIndex]!=1) && (grid[index]!=1))
    {
      weight = min(abs(height-row),abs(0-row));
      addEdge(Edge(index,rightIndex,10*pow(weight,weightPower)));
      numEdges+=1;
    }

    if(((col-1)>=0) && (grid[leftIndex]!=1) && (grid[index]!=1))
    {
      weight = min(abs(height-row),abs(0-row));
      addEdge(Edge(index,leftIndex,10*pow(weight,weightPower)));
      numEdges+=1;
    }

  }

  numVertices = vertices.size();
}

//add edge to graph
void WeightedGraph::addEdge(Edge e)
{
  int v = e.either();
  int w = e.other(v);
  edges[v].insert(e);
  edges[w].insert(e);
  vertices.insert(v);
  vertices.insert(w);
  return;
}

//edge set
multiset<Edge> WeightedGraph::Edges()
{
  multiset<Edge> returnVal;
  for (auto &kv : edges)
  {
    for (Edge e: edges[kv.first])
      returnVal.insert(e);
  }
  return returnVal;
}

//return # of vertices in graph
int WeightedGraph::V() const
{
 return numVertices;
}

//return number of edges
int WeightedGraph::E() const
{
 return numEdges;
}

//return vertex set
set <int> WeightedGraph::Vertices()const
{
  return vertices;
}

//returns edges of a given vertex
multiset<Edge> WeightedGraph::adj(int v)
{
  return edges[v];
}
