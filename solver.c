#include "solver.h"
#include "mouse.h"

    int vertArray [16][17]= { 
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
    };
    int horizArray [17][16] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

    };
    int manhattan [16][16]={
        {14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14},
        {13,12,11,10,9,8,7,6,6,7,8,9,10,11,12,13},
        {12,11,10,9,8,7,6,5,5,6,7,8,9,10,11,12},
        {11,10,9,8,7,6,5,4,4,5,6,7,8,9,10,11},
        {10,9,8,7,6,5,4,3,3,4,5,6,7,8,9,10},
        {9,8,7,6,5,4,3,2,2,3,4,5,6,7,8,9},
        {8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8},
        {7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7},
        {7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7},
        {8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8},
        {9,8,7,6,5,4,3,2,2,3,4,5,6,7,8,9},
        {10,9,8,7,6,5,4,3,3,4,5,6,7,8,9,10},
        {11,10,9,8,7,6,5,4,4,5,6,7,8,9,10,11},
        {12,11,10,9,8,7,6,5,5,6,7,8,9,10,11,12},
        {13,12,11,10,9,8,7,6,6,7,8,9,10,11,12,13},
        {14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14}
    };
// This function redirects function calls from mouse.c to the desired maze solving algorithm
Action solver(Mouse *mouse)
{
    // This can be changed to call other maze solving algorithms
    //return leftWallFollower(mouse);
    return floodFill(mouse);
}

// Simple algorithm; mouse goes straight until encountering a wall, then preferentially turns left
Action obstacleAvoider(Mouse *mouse)
{
    if(getFrontReading(mouse) == 0) return FORWARD;
    else if(getLeftReading(mouse) == 0) return LEFT;
    else if(getRightReading(mouse) == 0) return RIGHT;
    else return LEFT;
}

// Left wall following algorithm
int turnedLeft = 0;
Action leftWallFollower(Mouse *mouse)
{
    if(turnedLeft)
    {
        turnedLeft = 0;
        return FORWARD;
    }
    else if(getLeftReading(mouse) == 0)
    {
        turnedLeft = 1;
        return LEFT;
    }
    else if(getFrontReading(mouse) == 0) return FORWARD;
    else return RIGHT;
}

Action floodFill(Mouse *mouse)
{
    // TODO: Implement this function!


   
    printf("hello");
    return IDLE;
}

void updateWall(Mouse* mouse){
    int xCoord = mouse->x;
    int yCoord = mouse->y;

    if (getFrontReading(mouse)==1){
        if(mouse->heading == NORTH){
            horizArray[xCoord][yCoord] = 1;
        }
        else if(mouse->heading == EAST){
            vertArray[xCoord][yCoord+1] = 1;
        }
        else if(mouse->heading == WEST){
            vertArray[xCoord][yCoord]=1;
        }
        else if(mouse->heading ==SOUTH){
            horizArray[xCoord+1][yCoord]=1;
        }
    }
    if (getLeftReading(mouse)==1){
        if(mouse->heading == NORTH){
            vertArray[xCoord][yCoord] = 1;
        }
        else if(mouse->heading == EAST){
            horizArray[xCoord][yCoord] = 1;
        }
        else if(mouse->heading == WEST){
            horizArray[xCoord+1][yCoord]=1;
        }
        else if(mouse->heading == SOUTH){
            vertArray[xCoord][yCoord+1] = 1;
        }
    }
    if (getRightReading(mouse)==1){
        if(mouse->heading == NORTH){
            vertArray[xCoord][yCoord+1] = 1;
        }
        else if(mouse->heading == EAST){
            horizArray[xCoord+1][yCoord] = 1;
        }
        else if(mouse->heading == WEST){
            horizArray[xCoord][yCoord]=1;
        }
        else if(mouse->heading == SOUTH){
            vertArray[xCoord][yCoord] = 1;
        }
    }


}
