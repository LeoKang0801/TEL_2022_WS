#ifndef _DETECT_SQUARE_H_
#define _DETECT_SQUARE_H_

#include "ros/ros.h"
#include <geometry_msgs/Point.h>

float coords_array[3][2];

int detect_square();
// void record_coords(int n,struct Coords &coords);
float square_coord(int n);

#endif