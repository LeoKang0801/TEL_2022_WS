#include "scara.h"
#include "detect_square.h"


void ScaraTake()
{
    numberofsquare = detect_square();
    float x,y;
    bool feedback;
    for(int i=0;i<numberofsquare;i++)
    {
        feedback = 0;
        x, y = square_coord(i-1);
        feedback = Scara_move(x,y,1);
    }  
}

//缺feedback 
// take : state = 1
// put down : state = 0 
bool Scara_move(float x,float y,int state)
{
    ros::NodeHandle nh;
    scara_pub = nh.advertise<geometry_msgs::Point>("",1);
    bool feedback;
    
    // 可能用其他msgs才可以傳state
    geometry_msgs::Point point;
    point.x = x;
    point.y = y;
    point.z = state;
    scara_pub.publish(point);

    return feedback;
}

void Scaracoords(float x,float y)
{
    ros::NodeHandle nh;
    scara_pub = nh.advertise<geometry_msgs::Point>("",1);
    
    geometry_msgs::Point point;
    point.x = x;
    point.y = y;
    scara_pub.publish(point);
}
