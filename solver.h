#ifndef SOLVER_H
#define SOLVER_H

#include "mouse.h"

Action solver(Mouse *mouse);
Action leftWallFollower(Mouse *mouse);
Action floodFill(Mouse *mouse);

//helper functions
void updateWall(Mouse* mouse);
struct Coord{
int x;
int y;
};

#endif
