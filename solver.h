#ifndef SOLVER_H
#define SOLVER_H

#include "mouse.h"

Action solver(Mouse *mouse);
Action leftWallFollower(Mouse *mouse);
Action floodFill(Mouse *mouse);

//helper functions
void updateWalls(Mouse* mouse);
int leftAccessible(Heading heading, int xCoord, int yCoord);
int rightAccessible(Heading heading, int xCoord, int yCoord);
int frontAccessible(Heading heading, int xCoord, int yCoord);
int getFrontVal(Heading heading,  int xCoord, int yCoord);
int getLeftVal(Heading heading,  int xCoord, int yCoord);
int getRightVal(Heading heading,  int xCoord, int yCoord);
int getMinValOfNeighbors(Mouse*mouse );
int isInBounds(int x, int y);



struct Coord{
int x;
int y;
};

#endif
