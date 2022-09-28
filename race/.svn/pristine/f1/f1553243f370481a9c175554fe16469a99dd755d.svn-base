#ifndef _WHEEL_ODOM_H_
#define _WHEEL_ODOM_H_

#include "ros/ros.h"
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <iostream>
#include <math.h>
#include <vector>


#define PI 3.1415926


ros::Publisher path_pub;
ros::Publisher odom_pub;
ros::Subscriber encoder_sub;

int r = 100;//frequence
float a = 12;//cm
float b = 9.65;//cm
float radius = 5;//cm
float rpstocms = 2*PI*radius;

float vx = 0,vy = 0,vw = 0;
float dt = 0;
float delta_x = 0,delta_y = 0,delta_w = 0;
float position_x = 0,position_y = 0,position_w = 0;


// float vel_linear_x,vel_linear_y,vel_linear_w;
// float vel_linear_delta_x,vel_linear_delta_y,vel_linear_delta_w;

void encoder_callback(const geometry_msgs::Twist::ConstPtr& vel_data);

#endif