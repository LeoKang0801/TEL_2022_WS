#include "chassis_control.h"
#include "scara.h"

// 建構子
int main(int argc, char **argv)
{
    ros::init(argc, argv, "strategy");
 
    while (ros::ok())
    {
        // MoveTo(x,y,max_vel,acceleration);
        

        
        // MoveTo(10,10,0.5,0.02);
        // MoveTo(20,0,0.5,0.02);
        MoveTo(30,20,0.5,0.02);
        rotation(-90,0.5,0.02); 
        MoveTo(0,10,0.5,0.02);
        rotation(0,0.05,0.01);
        MoveTo(-10,10,0.5,0.02);
        break;
        // ScaraTake();
        // Scaracoords(x,y)
        // Scaracoords(0,0);
        // ScaraPut(x,y) put down the square int x,y
        // ScaraPut();
        // ROS_INFO("hello");
        // ros::Duration(1).sleep();
    }
}