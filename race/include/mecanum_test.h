#ifndef _MECANUM_H_
#define _MECANUM_H_

#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <math.h>
#include <vector>

ros::Publisher vel_pub;
ros::Subscriber encoder_sub;

float vel[4]={0,0,0,0};
float max_vel;
float acceleration;


int r = 15;//frequence
// float a = 12;//cm
// float b = 9.65;//cm

void car_vel(float max_vel,float acceleration);
void pub_car_vel(float accel_x,float accel_y,float vx,float vy);

#endif