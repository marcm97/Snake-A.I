#include "edge.h"

//Edge Constructor
Edge::Edge(int s, int e, double w) : v(s), w(e), weight(w){}

//function that returns the left vertex of the edge
int Edge::either() const
{
  return v;
}

//function that returns other vertex of edge
int Edge::other(int vertex) const
{
  if (vertex==v)
    return w;
  else
    return v;
}

//compare weights of a given edge with current edge
bool Edge::operator < (const Edge& rhs) const
{
  if (weight>rhs.weight)
    return true;
  return false;
}

//print out statemnet for a given edge
std::ostream &operator <<(std::ostream &os, const Edge&e)
{
  int v = e.either();
  int w = e.other(v);
  os<<v<<"-"<<w<<": "<<e.weight;
  return os;
}

//return weight of a given edge
double Edge::Weight() const
{
  return weight;
}
