#include "mecanum_test.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "wheel_test");
    ros::NodeHandle nh;
    // encoder_sub = nh.subscribe("encoder_data", 1, encoder_callback);
    vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);

    while (ros::ok())
    { 
        car_vel(max_vel = 0.4,acceleration = 0.02,max_angular_vel = 0.05,angular_accel = 0.005);
        // vel_x = 0.25*(-vel[0]+vel[1]-vel[2]+vel[3]);
        // vel_y = 0.25*(vel[0]+vel[1]+vel[2]+vel[3]);
        // vel_w = (1/(4*(a+b)))*(vel[0]-vel[1]-vel[2]+vel[3]);
    }
    ros::spinOnce();
}


void car_vel(float max_vel,float acceleration,float max_angular_vel,float angular_accel)
{
    float vx,vy,total_vel,vw;
    float accel_x,accel_y,accel_w;
    std::cout<<"vx vy vw:\n";
    std::cin>>vx>>vy>>vw;


    total_vel = sqrt(pow(vx,2)+pow(vy,2));
    if(total_vel > max_vel)
    {
        vx = vx*max_vel/total_vel;
        vy = vy*max_vel/total_vel;
        total_vel = max_vel;
    }
    if(vw > max_angular_vel)
        vw = max_angular_vel;

    accel_x = acceleration*vx/total_vel;
    accel_y = acceleration*vy/total_vel;
    accel_w = angular_accel;
    std::cout<<"accel_x = "<<accel_x<<"\naccel_y = "<<accel_y<<"\n";
    pub_car_vel(accel_x,accel_y,accel_w,vx,vy,vw);
}

void pub_car_vel(float accel_x,float accel_y,float accel_w,float vx,float vy,float vw)
{
    geometry_msgs::Twist vel_msg;
    vel_msg.linear.x = 0;
    vel_msg.linear.y = 0;
    vel_msg.angular.z = 0;
    ros::Rate rate(r);
    // 加速
    while (1)
    {
        
        vel_msg.linear.x += accel_x;
        vel_msg.linear.y += accel_y;
        if(vw!=0)
            vel_msg.angular.z +=accel_w;

        if (abs(vel_msg.linear.x) >= abs(vx) && abs(vel_msg.linear.y) >= abs(vy))
            temp1 = 1;

        if(abs(vel_msg.angular.z) >= abs(vw))
            temp2 = 1;

        if(temp1==1)
        {
            vel_msg.linear.x = vx;
            vel_msg.linear.y = vy;
        }

        if(temp2==1)
            vel_msg.angular.z = vw;

        std::cout<<"vx = "<<vel_msg.linear.x<<"\n";
        std::cout<<"vy = "<<vel_msg.linear.y<<"\n";
        std::cout<<"vw = "<<vel_msg.angular.z<<"\n";
        vel_pub.publish(vel_msg);
        if(temp1==1&&temp2==1)
            break;
        rate.sleep();
    }
    // 減速
    while (1)
    {
        vel_msg.linear.x -= accel_x;
        vel_msg.linear.y -= accel_y;
        if(vw!=0)
            vel_msg.angular.z -=accel_w;

        if (abs(vel_msg.linear.x) <= abs(accel_x) && abs(vel_msg.linear.y) <= abs(accel_y))
            temp1 = 0;

        if(abs(vel_msg.angular.z) <= abs(accel_w))
            temp2 = 0;

        if(temp1==0)
        {
            vel_msg.linear.x = 0;
            vel_msg.linear.y = 0;
        }

        if(temp2==0)
            vel_msg.angular.z = 0;

        std::cout<<"vx = "<<vel_msg.linear.x<<"\n";
        std::cout<<"vy = "<<vel_msg.linear.y<<"\n";
        std::cout<<"vw = "<<vel_msg.angular.z<<"\n";
        vel_pub.publish(vel_msg);
        if(temp1==0&&temp2==0)
            break;
        rate.sleep();
    }
}

// void encoder_callback(const std_msgs::Float64MultiArray::ConstPtr& vel_data)
// {
//     vel[0] = vel_data->data[0];
//     vel[1] = vel_data->data[1];
//     vel[2] = vel_data->data[2];
//     vel[3] = vel_data->data[3];
// }