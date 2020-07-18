#ifndef __PLAYER_H
#define __PLAYER_H
#include <list>
#include <queue>
#include <map>
#include <limits>

#include "playfield.h"
//typedef map<int, multiset<Edge>> map_t;
class Player
{
int turns =0;
public:
   Player ();
   ValidMove makeMove(const Playfield *);
private:
};


#endif
