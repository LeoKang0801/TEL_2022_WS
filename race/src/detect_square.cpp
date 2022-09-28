#include "detect_square.h"

struct Coords
{
    float x;
    float y;
};


int detect_square()
{
    // opencv main
    // count of square and coords
    int numberofsquare;
    // coords_array[0][0] = x;
    // coords_array[0][1] = y;
    // coords[i].x;
    // coords[i].y;
    // record_coords(numberofsquare);

    return numberofsquare;
}



// void record_coords(int n,struct Coords &coords)
// {
//     for(int i=0;i<n;i++)
//     {
//         coords_array[i][0] = *(coords+i).x;
//         coords_array[i][1] = *(coords+i).y;
//     }
// }

float square_coord(int n)
{
    return coords_array[n][0],coords_array[n][1];
}