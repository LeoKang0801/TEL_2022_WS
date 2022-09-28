#include "scara.h"

void ScaraTake()
{
    numberofsquare = detect_square();
    float x,y;
    bool feedback;
    for(int i=0;i<numberofsquare;i++)
    {
        feedback = 0;
        x, y = square_coord(i-1);
        feedback = Scara_move(x,y,0);
    }  
}

//缺feedback 
// take : state = 1
// put down : state = 0 
bool Scara_move(float x,float y,int init)
{
    ros::NodeHandle nh;
    scara_pub = nh.advertise<geometry_msgs::Point>("",1);
    bool feedback;
    
    // 可能用其他msgs才可以傳state
    geometry_msgs::Point point;
    point.x = x;
    point.y = y;
    point.z = init;
    scara_pub.publish(point);

    return feedback;
}

