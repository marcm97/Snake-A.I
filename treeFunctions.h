#ifndef TREEFUNCTIONS_H
#define TREEFUNCTIONS_H

struct Node
{
   int data;
   Node *left;
   Node *right;
   Node(int d, Node *l=nullptr, Node *r=nullptr) : data(d), left(l), right(r){}
};

bool areIsomorphic(Node *, Node *);
bool areSame(Node *, Node *);

#endif
