#ifndef _CHASSIS_CONTROL_H_
#define _CHASSIS_CONTROL_H_

#define PI 3.1415926

#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <std_msgs/String.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include "sensor_msgs/Imu.h"
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <iostream>
#include <math.h>


ros::Subscriber wheel_odom_sub;
ros::Subscriber imu_sub;
ros::Publisher vel_pub;

float position_x,position_y,position_w;
float angular,delta_rotation;
float delta_x,delta_y,delta_distance;
float middle_point;
float stop_point = 20;//離目標點多遠時開始減速
float stop_angular = 20;
float min_vel = 0.2;
float min_angular_vel = 0.02;
int r = 20;//freqency

void MoveTo(float x,float y,float max_vel,float acceleration);
void MoveTo(float x,float y,float w,float max_vel,float acceleration);
void rotation(float w,float max_angular_vel,float angular_accel);

void odom_callback(const nav_msgs::Odometry::ConstPtr& odom_data);
void imu_callback(const sensor_msgs::Imu::ConstPtr& imu_data);

float check_distance(float x,float y,float position_x,float position_y);
float len(float x,float y);
void go(float target_x,float target_y,float middle_point,float max_vel,float acceleration);
void turn(float target_w,float middle_w,float max_angular_vel,float angular_accel);

#endif