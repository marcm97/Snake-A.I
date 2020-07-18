/** ***************************************************************************
* @file
 *****************************************************************************/

/** ***************************************************************************
  * @mainpage Program 3 Snake
  *
  * @section CSC 315 (MWThF)
  *
  * @author Marc Mascarenhas
  *
  * @date : 02/05/2020
  *
  * @par Professor:
  *         Paul Hinker
  *
  * @par Course:
  *         CSC 315
  *
  *
  * @section program_section Program Information
  *
  * @details
  * This program attempts to solve th snake game
  *
  * @section compile_section Compiling and Usage
  *
  * @par Compiling Instructions:
  *       Use make
  *

  * @section todo_bugs_modification_section Todo, Bugs, and Modifications
  *
  * @bug
  *
  * @todo
  *
  * @par Modifications and Development Timeline:
    @verbatim
    <a href = "https://gitlab.mcs.sdsmt.edu/7353228/cscs315_spring2020_project3/
    -/commits/master"></a>
    @endverbatim
  *
  *****************************************************************************/

#include "player.h"
#include "edge.h"
#include "dijkstra.h"
#include <vector>
#include <iostream>

Player::Player() {}

// Searches the playfield grid for a specific value
std::pair<int, int> getLocation(const int *grid, int value)
{
  for (int y = 0 ; y < PLAYFIELD_HEIGHT ; y++)
     for (int x = 0 ; x < PLAYFIELD_WIDTH ; x++)
        if (grid[y * PLAYFIELD_WIDTH + x] == value)
           return std::pair<int, int>(x,y);

   return std::pair<int, int>(0,0);
}

/** ***************************************************************************
 * @author Marc Mascarenhas
 *
 * @par Description:
 * This function moves snake through path to food and creates a new temp grid
 *
 * @param[in]     grid - current grid
 * @param[in]     snake - current snake array
 * @param[in]     path - current path to take
 * @param[in]     loc_food - food loc
 * return new grid
 *****************************************************************************/
int* getTempGrid(const int*grid,vector<int>snake,vector<int>path,int loc_food)
{
  //create a temporary array
  int *temp = NULL;
  temp = new int[PLAYFIELD_WIDTH*PLAYFIELD_HEIGHT];

  //copy the array
  for (int y = 0 ; y < PLAYFIELD_HEIGHT ; y++)
     for (int x = 0 ; x < PLAYFIELD_WIDTH ; x++)
        temp[y * PLAYFIELD_WIDTH + x] = grid[y * PLAYFIELD_WIDTH + x];

  //moving snake to new position on temp grid
  //Case 1: Snake size >path size
  if (path.size()<snake.size())
  {
    for (int i=0;i<(int)path.size()-1;i++)
      temp[path[i]]=1;
    for (int i=(int)snake.size()-1;i>(int)(snake.size()-path.size());i--)
      temp[snake[i]]=0;
    temp[snake[0]]=1;
  }
  //Case 2: if path size and snake size are equal
  else if (path.size()==snake.size())
  {
    for (int i=0;i<(int)path.size();i++)
    {
      temp[path[i]]=1;
      temp[snake[i]]=0;
    }
    temp[snake[0]]=1;
  }
  //Case 3: if snake size<path size
  else
  {
    for (int i=0;i<(int)snake.size();i++)
    {
      temp[snake[i]]=0;
      temp[path[path.size()-2-i]]=1;
    }
  }
  //make the food the new head
  temp[loc_food]=2;

  return temp;

}

/** ***************************************************************************
 * @author Marc Mascarenhas
 *
 * @par Description:
 * //Creates a temporary grid for forward checks by moving the snake to desired loc
 *
 * @param[in]     grid - current grid
 * @param[in]     snake - current snake array
 * @param[in]     path - current path to take
 * @param[in]     loc_food - desired loc
 * return new grid
 *****************************************************************************/
int* getTempGridNoFood(const int*grid,vector<int>snake,vector<int>path,int loc_food)
{
  //create a temporary array
  int *temp = NULL;
  temp = new int[PLAYFIELD_WIDTH*PLAYFIELD_HEIGHT];

  //copy the array
  for (int y = 0 ; y < PLAYFIELD_HEIGHT ; y++)
     for (int x = 0 ; x < PLAYFIELD_WIDTH ; x++)
        temp[y * PLAYFIELD_WIDTH + x] = grid[y * PLAYFIELD_WIDTH + x];

  //moving snake to new position on temp grid
  //Case 1: Snake size >path size
  if (path.size()<snake.size())
  {
    for (int i=0;i<(int)path.size()-1;i++)
      temp[path[i]]=1;
    for (int i=(int)snake.size()-1;i>(int)(snake.size()-path.size()-1);i--)
      temp[snake[i]]=0;
    temp[snake[0]]=1;
  }
  //Case 2: if path size and snake size are equal
  else if (path.size()==snake.size())
  {
    for (int i=0;i<(int)path.size();i++)
    {
      temp[path[i]]=1;
      temp[snake[i]]=0;
    }
    temp[snake[0]]=1;
  }
  //Case 3: if snake size<path size
  else
  {
    for (int i=0;i<(int)snake.size();i++)
    {
      temp[snake[i]]=0;
      temp[path[path.size()-2-i]]=1;
    }
  }
  //make the food the new head
  temp[loc_food]=2;

  return temp;

}


/** ***************************************************************************
 * @author Marc Mascarenhas
 *
 * @par Description:
 * returns tail location  of snake that has taken a specified path to the food
 *
 * @param[in]     snake - current snake array
 * @param[in]     path - current path to take
 * return tail loc
 *****************************************************************************/
int tailLoc(vector<int>snake,vector<int>path)
{
  //C1: path size <snake size
  if (path.size()<snake.size())
  {
    return snake[snake.size()-path.size()];
  }
  //C2: path size ==snake size
  else if (path.size()==snake.size())
  {
    return snake[0];
  }
  //C3: path size>snake size
  else
  {
    return path[path.size()-snake.size()];
  }

}

/** ***************************************************************************
 * @author Marc Mascarenhas
 *
 * @par Description:
 * //returns tail location  of snake that has taken a specified path
 *
 * @param[in]     snake - current snake array
 * @param[in]     path - current path to take
 * return tail loc
 *****************************************************************************/
int tailLocNoFood(vector<int>snake,vector<int>path)
{
  //C1: path size <snake size
  if (path.size()<snake.size())
  {
    return snake[snake.size()-path.size()-2];
  }
  //C2: path size ==snake size
  else if (path.size()==snake.size())
    return snake[0];
  //C3: path size>snake size
  else
  {
      return path[path.size()-snake.size()-2];
  }

}


/** ***************************************************************************
 * @author Marc Mascarenhas
 *
 * @par Description:
 * //Calculate move based on pos on graph
 *
 * @param[in]     end: array pos of move
 * @param[in]     grid: plafield grid
 * return move
 *****************************************************************************/
ValidMove move(int end,const int*grid)
{
  int x =end/PLAYFIELD_WIDTH;
  int y = end%PLAYFIELD_WIDTH;
  std::pair<int, int> head = getLocation(grid, HEAD_VALUE);
  std::pair<int, int> nextMove = std::pair<int,int>(y,x);

  if (nextMove.first == head.first)
  {
    if (nextMove.second>head.second)
       return UP; //flipped axis glut
    return DOWN;
  }

  else if (nextMove.second ==head.second)
  {
    if (nextMove.first>head.first)
      return RIGHT;
   return LEFT;
  }

  return NONE;
}


/** ***************************************************************************
 * @author Marc Mascarenhas
 *
 * @par Description:
 * //Calcultes if a valid move is possible to all 4 adj positions, returns  1st step
 * it should
 * a) have a path to one of the 4 adj position
 * b) check boundary conditions
 * c) it shouldn't be the HEAD_VALUE
 * d) it shouldn't be the food
 *
 * @param[in]     D - class instance of dijkstra
 * @param[in]     dest - final destination
 * @param[in]     loc_head - head of snake loc
 * @param[in]     loc_food - desired loc
 * @param[in]     grid - playfield grid
 * return move
 *****************************************************************************/
ValidMove moveToAdj(DijkstraSP D, int dest, int loc_food, int loc_head, const int *grid)
{

  if (D.hasPath(dest-1)  && dest%PLAYFIELD_WIDTH!=0  && loc_food!=dest-1 && loc_head!=dest-1)
  {
    return move(D.pathTo(dest-1)[0],grid);
  }
  if (D.hasPath(dest+1)  && (dest+1)%PLAYFIELD_WIDTH!=0 && loc_food!=dest+1 && loc_head!=dest+1)
  {
    return move(D.pathTo(dest+1)[0],grid);
  }
  if (D.hasPath(dest+PLAYFIELD_WIDTH)  && loc_food!= dest+PLAYFIELD_WIDTH   && loc_head!= dest+PLAYFIELD_WIDTH)
  {
    return move(D.pathTo(dest+PLAYFIELD_WIDTH)[0],grid);
  }
  if (D.hasPath(dest-PLAYFIELD_WIDTH) && loc_food!= dest-PLAYFIELD_WIDTH && loc_head!= dest-PLAYFIELD_WIDTH)
  {
    return move(D.pathTo(dest-PLAYFIELD_WIDTH)[0],grid);
  }

  for(int m: D.possibilities())
  {
    if (D.pathTo(m).size()>3)
    {
      return move(D.pathTo(m)[0],grid);
    }
  }
  return NONE;
}

/** ***************************************************************************
 * @author Marc Mascarenhas
 *
 * @par Description:
 * //Calcultes if a valid move is possible to all 4 adj positions
 * it should
 * a) have a path to one of the 4 adj position
 * b) check boundary conditions
 * c) it shouldn't be the HEAD_VALUE
 * d) it shouldn't be the food
 *
 * @param[in]     D - class instance of dijkstra
 * @param[in]     dest - final destination
 * @param[in]     loc_head - head of snake loc
 * @param[in]     loc_food - desired loc
 * @param[in]     grid - playfield grid
 * return entire path
 *****************************************************************************/
vector<int> pathToAdj(DijkstraSP D, int dest, int loc_food, int loc_head, const int *grid)
{
  if (D.hasPath(dest-1)  && dest%PLAYFIELD_WIDTH!=0  && loc_food!=dest-1 && loc_head!=dest-1)
  {
    return D.pathTo(dest-1);
  }
  if (D.hasPath(dest+1)  && (dest+1)%PLAYFIELD_WIDTH!=0 && loc_food!=dest+1 && loc_head!=dest+1)
  {
    return D.pathTo(dest+1);
  }
  if (D.hasPath(dest+PLAYFIELD_WIDTH)  && loc_food!= dest+PLAYFIELD_WIDTH   && loc_head!= dest+PLAYFIELD_WIDTH)
  {
    return D.pathTo(dest+PLAYFIELD_WIDTH);
  }
  if (D.hasPath(dest-PLAYFIELD_WIDTH) && loc_food!= dest-PLAYFIELD_WIDTH && loc_head!= dest-PLAYFIELD_WIDTH)
  {
    return D.pathTo(dest-PLAYFIELD_WIDTH);
  }

  return {};
}

/** ***************************************************************************
 * @author Marc Mascarenhas
 *
 * @par Description:
 * main control flow of the algorithm
 * finds path to food, if possible, checks to make sure there will be path to tail
 * if not finds path to tail and takes it (while trying to increase dist to tail)
 *
 * @param[in]  pf - current playfield
 * return ValidMove
 *****************************************************************************/
ValidMove Player::makeMove(const Playfield *pf)
{
   const int *grid = pf->getGrid();
   static vector <int> v1; //snake (head, tail tail.....)
   static vector<int> current_path; //djikstra's path to take (next move,move,....destination)
   static int score = 0;

   static int loop; //counter that keeps track of number of moves since last food
   turns+=1;//counter that keeps track of total number of moves

   std::pair<int, int> head = getLocation(grid, HEAD_VALUE);
   std::pair<int, int> food = getLocation(grid, FOOD_VALUE);
   //.first->col; .second->row
   int loc_head= head.second * PLAYFIELD_WIDTH + head.first;
   int loc_food = food.second * PLAYFIELD_WIDTH + food.first;

   //exit program if >25000 moves have been taken
   if(turns>25000)
   {
     return NONE;
   }

   //keep track of snake position
   v1.insert(v1.begin(),loc_head);
   if (pf->getScore()>score)
     score = pf->getScore();
   else
     v1.pop_back();

   //if optimum path found, follow path (that was stored in in current_path)
   if(current_path.size()!=0)
   {
     int toMove = current_path[0];
     current_path.erase(current_path.begin());
     loop=0;
     return move(toMove,grid);
   }

   WeightedGraph *G = new WeightedGraph(grid,PLAYFIELD_WIDTH,PLAYFIELD_HEIGHT,3);
   DijkstraSP D(G,loc_head);

   //find path to food and forward check to see if there is a path to tail
   //if path found, store path in array and move
   for (int i=int(v1.size()/40);i>=0;i--)
   {
     WeightedGraph *G = new WeightedGraph(grid,PLAYFIELD_WIDTH,PLAYFIELD_HEIGHT,i);
     DijkstraSP D(G,loc_head);

     int j=2;
     if (v1.size()<10)
      j=1;
     if (D.hasPath(loc_food))
     {
       int *temp;
       temp= getTempGrid(grid,v1,D.pathTo(loc_food),loc_food);
       int tail = tailLoc(v1,D.pathTo(loc_food));

       WeightedGraph *G3 = new WeightedGraph((const int*)temp,PLAYFIELD_WIDTH,PLAYFIELD_HEIGHT,i);
       DijkstraSP D2(G3, loc_food);

       delete [] temp;
       temp=NULL;

       if ( (D2.hasPath(tail-1))  && ((tail)%PLAYFIELD_WIDTH!=0) && ((tail-1)!=loc_food) && (int)D2.pathTo(tail-1).size()>=(int)j)
       {
         for(int i:D.pathTo(loc_food) )
         {
           current_path.push_back(i);
         }
         loop=0;
         current_path.erase(current_path.begin());
         return move(D.pathTo(loc_food)[0],grid);
       }

       if ((D2.hasPath(tail+1)) && ((tail+1)%PLAYFIELD_WIDTH!=0) && ((tail+1)!=loc_food) && (int)(D2.pathTo(tail+1)).size()>=(int)j)
       {
         for(int i:D.pathTo(loc_food) )
         {
           current_path.push_back(i);
         }
         loop=0;
         current_path.erase(current_path.begin());
         return move(D.pathTo(loc_food)[0],grid);
       }

       if ((D2.hasPath(tail+PLAYFIELD_WIDTH)) && ((tail+PLAYFIELD_WIDTH)!=loc_food)&& (int)(D2.pathTo(tail+PLAYFIELD_WIDTH)).size()>=(int)j)
       {
         for(int i:D.pathTo(loc_food))
         {
           current_path.push_back(i);
         }
         loop=0;
         current_path.erase(current_path.begin());
         return move(D.pathTo(loc_food)[0],grid);
       }

       if ((D2.hasPath(tail-PLAYFIELD_WIDTH)) && ((tail-PLAYFIELD_WIDTH)!=loc_food)&& (int)(D2.pathTo(tail-PLAYFIELD_WIDTH)).size()>=(int)j)
       {
         for(int i:D.pathTo(loc_food) )
         {
           current_path.push_back(i);
         }
         current_path.erase(current_path.begin());
         return move(D.pathTo(loc_food)[0],grid);
       }

     }
   }

   //#of moves since food last eaten
   loop+=1;

   //if above a certain threshold, just go fo fr food and inc score by 1
   if(loop>(int)(555+v1.size()*10) && D.hasPath(loc_food))
   {

     for(int i:D.pathTo(loc_food))
     {
       current_path.push_back(i);
     }
     current_path.erase(current_path.begin());
     return move(D.pathTo(loc_food)[0],grid);
   }

   //try and icrease dist to tail
   //find paths longer than 3, forward check to see that tail will be still reachable
   if (loop>(int)(v1.size()) && D.possibilities().size()>3)
   {
     for(int m: D.possibilities())
     {
       if (D.pathTo(m).size()>2)
       {
         int *temp2;
         temp2= getTempGridNoFood(grid,v1,D.pathTo(m),m);
         WeightedGraph *G3 = new WeightedGraph((const int*)temp2,PLAYFIELD_WIDTH,PLAYFIELD_HEIGHT,1);
         DijkstraSP D2(G3,m);
         // //can I find new tail?
         int newTail = tailLocNoFood(v1,D.pathTo(m));

         if (pathToAdj(D2,newTail,loc_food,m,temp2).size()>2)
         {
           for(int i: D.pathTo(m))
           {
             current_path.push_back(i);
           }
           current_path.erase(current_path.begin());
           return move(D.pathTo(m)[0],grid);
         }
       }
     }
   }

   //else move towards tail
   int curr_tail = v1[v1.size()-1];
   return moveToAdj(D, curr_tail, loc_food, loc_head,grid);
}
