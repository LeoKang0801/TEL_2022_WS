#include "first.h"

// 建構子
int main(int argc, char **argv)
{
    ros::init(argc, argv, "strategy");
 
    while (ros::ok())
    {
        first();
        // ScaraTake();
        // Scaracoords(x,y)
        // Scaracoords(0,0);
        // ScaraPut(x,y) put down the square int x,y
        // ScaraPut();
        // ROS_INFO("hello");
        // ros::Duration(1).sleep();
    }
}