#include "solver.h"
#include "mouse.h"

#define TRUE 1;
#define FALSE 0;

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

    

   
   
    updateWalls(mouse);
    for (int i = 0; i < 16; i++ ){
        for ( int j = 0; j < 17; j++)
            printf("%d", vertArray[i][j]);
        printf("\n");
    }

    printf ("\n");

    //check all three neighboring cells for min value
    int min = getMinValOfNeighbors(mouse);
    Heading heading = mouse->heading;
    int xCoord = mouse->x;
    int yCoord = mouse->y;

    int man = manhattan[xCoord][yCoord];
    int front = getFrontVal(heading, xCoord,yCoord);
    int left = getLeftVal(heading, xCoord, yCoord);
    int right = getRightVal(heading, xCoord, yCoord);

    printf("Front is : %d \n Man is :  %d \n Min is : %d \n FrontAccess: %d", front, man, min ,  frontAccessible(heading,xCoord,yCoord));

    if (front !=999 && front == min && front < man && frontAccessible(heading,xCoord,yCoord) )
        return FORWARD;
    else if(left !=999 && left == min && left < man && leftAccessible(heading,xCoord,yCoord))
        return LEFT;
    else if (right !=999 && right == min && left < man && rightAccessible(heading,xCoord,yCoord))
        return RIGHT;
    else
        return IDLE;
}

int frontAccessible(Heading heading, int xCoord, int yCoord){
    switch(heading){
        case SOUTH:
        {
                if(horizArray[xCoord+1][yCoord]!= 1 )
                    return TRUE;
                break;
         }
        case EAST:
        {
                if(vertArray[xCoord][yCoord]!= 1 )
                    return TRUE;
                break;
        }
        case WEST:
        {
                if(vertArray[xCoord][yCoord+1]!= 1 )
                    return TRUE;
                break;
        }
          case NORTH:
        {
                if(horizArray[xCoord][yCoord]!= 1 )
                    return TRUE;
                break;
        }

    }
    return FALSE;
}

int leftAccessible(Heading heading, int xCoord, int yCoord){
    switch(heading){
        case NORTH:
        {
                if(vertArray[xCoord][yCoord+1]!= 1 )
                    return TRUE;
                break;
         }
        case EAST:
        {
                if(horizArray[xCoord+1][yCoord]!= 1 )
                    return TRUE;
                break;
        }
        case WEST:
        {
                if(horizArray[xCoord][yCoord]!= 1 )
                    return TRUE;
                break;
        }
          case SOUTH:
        {
                if(vertArray[xCoord][yCoord]!= 1 )
                    return TRUE;
                break;
        }

    }
    return FALSE;
}

int rightAccessible(Heading heading, int xCoord, int yCoord){
    switch(heading){
        case NORTH:
        {
                if(vertArray[xCoord][yCoord]!= 1 )
                    return TRUE;
                break;
         }
        case EAST:
        {
                if(horizArray[xCoord][yCoord]!= 1 )
                    return TRUE;
                break;
        }
        case WEST:
        {
                if(horizArray[xCoord+1][yCoord]!= 1 )
                    return TRUE;
                break;
        }
          case SOUTH:
        {
                if(vertArray[xCoord][yCoord+1]!= 1 )
                    return TRUE;
                break;
        }

    }
    return FALSE;
}

int getFrontVal(Heading heading,  int xCoord, int yCoord){
     switch (heading){
        case NORTH:
            {   
                //front
                if(isInBounds (xCoord+1,yCoord))
                    return manhattan[xCoord+1][yCoord];
                break;

            }
         case EAST:
            {   
                //front
                if(isInBounds (xCoord,yCoord-1))
                    return manhattan[xCoord][yCoord-1];
                break;
            }
         case WEST:
            {   
                //front
                if(isInBounds (xCoord,yCoord+1))
                    return manhattan[xCoord][yCoord+1];
                break;
              
            }
         case SOUTH:
            {   
                //front
                if(isInBounds (xCoord-1,yCoord))
                    return manhattan[xCoord-1][yCoord];
                break;
            }

           

    }
 return 999;
}

int getLeftVal(Heading heading,  int xCoord, int yCoord){
     switch (heading){
        case SOUTH:
            {  
                if(isInBounds (xCoord,yCoord+1))
                    return manhattan[xCoord][yCoord+1];
                break;

            }
         case EAST:
            {  
                if(isInBounds (xCoord+1,yCoord))
                    return manhattan[xCoord+1][yCoord];
                break;
            }
         case WEST:
            {   
                if(isInBounds (xCoord-1,yCoord))
                    return manhattan[xCoord-1][yCoord];
                break;
              
            }
         case NORTH:
            {   
                if(isInBounds (xCoord,yCoord-1))
                    return manhattan[xCoord][yCoord-1];
                break;
            }


    }
    
            return 999;
}

int getRightVal(Heading heading, int xCoord, int yCoord ){

     switch (heading){
        case SOUTH:
            {  
                if(isInBounds (xCoord,yCoord-1))
                    return manhattan[xCoord][yCoord-1];
                break;

            }
         case EAST:
            {  
                if(isInBounds (xCoord-1,yCoord))
                    return manhattan[xCoord-1][yCoord];
                break;
            }
         case WEST:
            {   
                if(isInBounds (xCoord+1,yCoord))
                    return manhattan[xCoord+1][yCoord];
                break;
              
            }
         case NORTH:
            {   
                if(isInBounds (xCoord,yCoord+1))
                    return manhattan[xCoord][yCoord+1];
                break;
            }

           

    }
     return 999;
}


int getMinValOfNeighbors(Mouse*mouse ){
    int min = 1000;
    int xCoord = mouse->x;
    int yCoord = mouse->y;
    Heading heading = mouse->heading;

    int front = getFrontVal(heading, xCoord,yCoord);
    int left = getLeftVal(heading, xCoord, yCoord);
    int right = getRightVal(heading, xCoord, yCoord);

    printf ("front: %d \n left: %d \n right: %d \n", front, left, right);
    if(front!= 999 && front < min )
        min = front;
    if (left !=999 && left < min)
        min = left;
    if(right != 999 && right < min)
        min = right;
   
    return min;
}


// int getMinValOfNeighbors(Mouse*mouse ){
//     int min = 1000;
//     int xCoord = mouse->x;
//     int yCoord = mouse->y;

//     Heading heading = mouse->heading;
//     switch (heading){
//         case NORTH:
//             {   
//                 //front
//                 if(isInBounds (xCoord+1,yCoord)){
//                     if (manhattan[xCoord+1,yCoord] < min)
//                         min = manhattan[xCoord+1,yCoord];
//                 }
//                 //right
//                 if(isInBounds (xCoord,yCoord-1)){
//                     if (manhattan[xCoord][yCoord-1] < min)
//                     min = (manhattan[xCoord][yCoord-1];
//                 }
//                 //left
//                 if(isInBounds (xCoord,yCoord+1)){
//                     if (manhattan[xCoord][yCoord+1] < min)
//                     min = (manhattan[xCoord][yCoord+1];
//                 }
//                 break;
//             }
//          case EAST:
//             {   
//                 //front
//                 if(isInBounds (xCoord,yCoord-1)){
//                     if (manhattan[xCoord,yCoord-1] < min)
//                         min = manhattan[xCoord,yCoord-1];
//                 }
//                 //right
//                 if(isInBounds (xCoord-1,yCoord)){
//                     if (manhattan[xCoord-1][yCoord] < min)
//                     min = (manhattan[xCoord-1][yCoord];
//                 }
//                 //left
//                 if(isInBounds (xCoord+1,yCoord)){
//                     if (manhattan[xCoord+1][yCoord] < min)
//                     min = (manhattan[xCoord+1][yCoord];
//                 }
//                 break;
//             }
//          case WEST:
//             {   
//                 //front
//                 if(isInBounds (xCoord,yCoord+1)){
//                     if (manhattan[xCoord,yCoord+1] < min)
//                         min = manhattan[xCoord,yCoord+1];
//                 }
//                 //right
//                 if(isInBounds (xCoord+1,yCoord)){
//                     if (manhattan[xCoord+1][yCoord] < min)
//                     min = (manhattan[xCoord+1][yCoord];
//                 }
//                 //left
//                 if(isInBounds (xCoord-1,yCoord)){
//                     if (manhattan[xCoord-1][yCoord] < min)
//                     min = (manhattan[xCoord-1][yCoord];
//                 }
//                 break;
//             }
//          case SOUTH:
//             {   
//                 //front
//                 if(isInBounds (xCoord-1,yCoord)){
//                     if (manhattan[xCoord-1,yCoord] < min)
//                         min = manhattan[xCoord-1,yCoord];
//                 }
//                 //left
//                 if(isInBounds (xCoord,yCoord-1)){
//                     if (manhattan[xCoord][yCoord-1] < min)
//                     min = (manhattan[xCoord][yCoord-1];
//                 }
//                 //right
//                 if(isInBounds (xCoord,yCoord+1)){
//                     if (manhattan[xCoord][yCoord+1] < min)
//                     min = (manhattan[xCoord][yCoord+1];
//                 }
//                 break;
//             }

//     }
//     return min;
// }

int isInBounds(int x, int y){
    if(x < 0 || y < 0 || y > 15 || x > 15)
        return 0;
    return 1;

}

void updateWalls(Mouse* mouse){
    int xCoord = mouse->x;
    int yCoord = mouse->y;

     printf("X coord is %d\n", xCoord);
     printf("Y coord is %d\n", yCoord);
    

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
