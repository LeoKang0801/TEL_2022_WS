 #include "chassis_control.h"

void MoveTo(float x,float y,float max_vel,float acceleration)
{
    ros::NodeHandle nh;
    wheel_odom_sub = nh.subscribe("wheel_odom", 1, odom_callback);
    vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);
    ros::spinOnce();

    delta_x,delta_y = check_distance(x,y,position_x,position_y);
    delta_distance = len(delta_x,delta_y);
    float middle_point = delta_distance/2;
    go(x,y,middle_point,max_vel,acceleration);
}
void MoveTo(float x,float y,float w,float max_vel,float acceleration)
{
    ros::NodeHandle nh;
    wheel_odom_sub = nh.subscribe("wheel_odom", 1, odom_callback);
    imu_sub = nh.subscribe("imu_angular", 1,imu_callback);
    vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);
    ros::spinOnce();

    delta_x,delta_y = check_distance(x,y,position_x,position_y);
    delta_distance = len(delta_x,delta_y);
    middle_point = delta_distance/2;
    go(x,y,middle_point,max_vel,acceleration);
}
void rotation(float w,float max_angular_vel,float angular_accel)
{
    ros::NodeHandle nh;
    imu_sub = nh.subscribe("imu_angular", 1,imu_callback);
    vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);
    ros::spinOnce();
    delta_rotation = w - position_w;
    turn(w,delta_rotation/2,max_angular_vel,angular_accel);
}

void odom_callback(const nav_msgs::Odometry::ConstPtr& odom_data) 
{
    position_x = odom_data->pose.pose.position.x;
    position_y = odom_data->pose.pose.position.y;
    geometry_msgs::Quaternion q;
    q.x = odom_data->pose.pose.orientation.x;
    q.y = odom_data->pose.pose.orientation.y;
    q.z = odom_data->pose.pose.orientation.z;
    q.w = odom_data->pose.pose.orientation.w;
    // std::cout<<"q: "<<q<<"\n";
    position_w = tf::getYaw(q);
}
void imu_callback(const sensor_msgs::Imu::ConstPtr& imu_data)
{
    angular = imu_data->angular_velocity.z;
}

float check_distance(float x,float y,float position_x,float position_y)
{
    delta_x = x-position_x;
    delta_y = y-position_y;
    return delta_x,delta_y;
}

float len(float x,float y)
{
    float re = sqrt(pow(x,2)+pow(y,2));
    return re;
}
    

void go(float target_x,float target_y,float middle_point,float max_vel,float acceleration)
{
    geometry_msgs::Twist vel_msg;
    vel_msg.linear.x = 0;
    vel_msg.linear.y = 0;
    vel_msg.angular.z = 0;
    if(delta_distance>0.05)
    {    
        int temp = 0;
        float accel_x,accel_y;
        float dir_x,dir_y;
        float now_vel = 0;
        ros::Rate rate(r);
        // accelerate
        while(temp!=1&&delta_distance >= middle_point&&ros::ok())
        {
            std::cout<<"1\n";
            ros::spinOnce();
            delta_x,delta_y = check_distance(target_x,target_y,position_x,position_y);
            dir_x = (delta_x*cos(position_w)+delta_y*sin(position_w));
            dir_y = (delta_y*cos(position_w)-delta_x*sin(position_w));
            std::cout<<"trans_x = "<<dir_x<<" trans_y = "<<dir_y<<"\n";
            delta_distance = len(dir_x,dir_y);
            dir_x = dir_x/delta_distance;
            dir_y = dir_y/delta_distance;
            
            std::cout<<delta_x<<" "<<delta_y<<"\n";
            std::cout<<dir_x<<" "<<dir_y<<"\n";
            accel_x = dir_x*acceleration;
            accel_y = dir_y*acceleration;
            vel_msg.linear.x += accel_x;
            vel_msg.linear.y += accel_y;    
        
            now_vel = len(vel_msg.linear.x,vel_msg.linear.y);
            if (now_vel>=max_vel)
            {   
                std::cout<<"2\n";
                vel_msg.linear.x = max_vel*dir_x;
                vel_msg.linear.y = max_vel*dir_y;
                temp = 1;
            }
            vel_pub.publish(vel_msg);
            rate.sleep();
        }
        // keep max_vel until arrive stop_point
        std::cout<<"3\n";
        while(temp==1&&ros::ok())
        {
            std::cout<<"4\n";

            ros::spinOnce();
            delta_x,delta_y = check_distance(target_x,target_y,position_x,position_y);
            dir_x = (delta_x*cos(position_w)+delta_y*sin(position_w));
            dir_y = (delta_y*cos(position_w)-delta_x*sin(position_w));
            delta_distance = len(dir_x,dir_y);
            dir_x = dir_x/delta_distance;
            dir_y = dir_y/delta_distance;

            vel_msg.linear.x = max_vel*dir_x;
            vel_msg.linear.y = max_vel*dir_y;
            vel_pub.publish(vel_msg);      
            
            std::cout<<"distance = "<<delta_distance<<"\n";
            std::cout<<position_x<<" "<<position_y<<"\n";
            std::cout<<dir_x<<" "<<dir_y<<"\n";
            
            if(delta_distance<=stop_point)
            {
                temp = 0;
                break;    
            }   
            rate.sleep();
        }
        temp = 0;
        std::cout<<"5\n";
        //reduce speed 
        while(temp==0&&ros::ok()&&delta_distance>2)
        {
            std::cout<<"6\n";
            ros::spinOnce();
            delta_x,delta_y = check_distance(target_x,target_y,position_x,position_y);
            dir_x = (delta_x*cos(position_w)+delta_y*sin(position_w));
            dir_y = (delta_y*cos(position_w)-delta_x*sin(position_w));
            delta_distance = len(dir_x,dir_y);
            dir_x = dir_x/delta_distance;
            dir_y = dir_y/delta_distance;
            accel_x = dir_x*acceleration;
            accel_y = dir_y*acceleration;
            vel_msg.linear.x -= accel_x;
            vel_msg.linear.y -= accel_y;
            
            now_vel = len(vel_msg.linear.x,vel_msg.linear.y);
            std::cout<<"now_vel = "<<now_vel<<" \n";
            std::cout<<dir_x<<" "<<dir_y<<"\n";
            std::cout<<"distance = "<<delta_distance<<"\n";

            if(now_vel<=min_vel)
            {
                vel_msg.linear.x = min_vel*dir_x;
                vel_msg.linear.y = min_vel*dir_y;
                temp = 1;
            }
            vel_pub.publish(vel_msg);
            rate.sleep();
        }
        std::cout<<"7\n";
        //slowly move to target point
        while(delta_distance>1&&ros::ok())
        {
            std::cout<<"8\n";
            vel_msg.linear.x = min_vel*dir_x;
            vel_msg.linear.y = min_vel*dir_y;
            vel_pub.publish(vel_msg);
            
            ros::spinOnce();
            delta_x,delta_y = check_distance(target_x,target_y,position_x,position_y);
            dir_x = (delta_x*cos(position_w)+delta_y*sin(position_w));
            dir_y = (delta_y*cos(position_w)-delta_x*sin(position_w));
            delta_distance = len(dir_x,dir_y);
            dir_x = dir_x/delta_distance;
            dir_y = dir_y/delta_distance;
            rate.sleep();
        }
        // stop
        std::cout<<"9\n";
        vel_msg.linear.x = 0;
        vel_msg.linear.y = 0;
        vel_pub.publish(vel_msg);
    }
    else
    {
        vel_msg.linear.x = 0;
        vel_msg.linear.y = 0;
        vel_pub.publish(vel_msg);
    }
}

void turn(float target_w,float middle_w,float max_angular_vel,float angular_accel)
{
    geometry_msgs::Twist vel_msg;
    vel_msg.linear.x = 0;
    vel_msg.linear.y = 0;
    vel_msg.angular.z = 0;
    ros::Rate rate(r);
    int temp,dir_w;
    temp = 0;
    dir_w = 0;
    ros::spinOnce();
    delta_rotation = target_w-position_w*180/PI;
    dir_w = delta_rotation/abs(delta_rotation);

    while(abs(delta_rotation)>abs(middle_w)&&temp==0&&ros::ok())
    {
        std::cout<<"rotation_accel\n";
        vel_msg.angular.z += dir_w*angular_accel;
        std::cout<<"dir_w = "<<dir_w<<"\n";
        if(abs(vel_msg.angular.z)>=max_angular_vel)
        {
            std::cout<<"\nrotation_maxvel\n";
            std::cout<<"vel_rotation"<<vel_msg.angular.z<<"\n";
            vel_msg.angular.z = dir_w*max_angular_vel;
            temp = 1;
        }
        ros::spinOnce();
        delta_rotation = target_w - position_w*180/PI; 
        vel_pub.publish(vel_msg);
        rate.sleep();
    }
    while(temp==1&&ros::ok())
    {
        std::cout<<"\nrotation_keep_maxvel\n";
        std::cout<<"omega: "<<position_w*180/PI<<"\n";
        std::cout<<"delta_rotation: "<<delta_rotation<<"\n";
        ros::spinOnce();
        delta_rotation = target_w-position_w*180/PI; 
        if(abs(delta_rotation) <= stop_angular)
            temp = 0;
        vel_pub.publish(vel_msg);
        rate.sleep();
    }
    temp = 0;
    while(abs(delta_rotation)>5&&ros::ok()&&temp==0)
    {
        std::cout<<"\nrotation_reduce_vel\n";
        vel_msg.angular.z -= dir_w*angular_accel;
        ros::spinOnce();
        delta_rotation = target_w-position_w*180/PI;
        if(abs(vel_msg.angular.z)<=min_angular_vel)
            temp = 1;
        vel_pub.publish(vel_msg);
        rate.sleep();
    }

    while(abs(delta_rotation)>1&&ros::ok())
    {
        std::cout<<"rotation_minvel\n";
        ros::spinOnce();
        vel_msg.angular.z = dir_w*min_angular_vel;
        delta_rotation = target_w-position_w*180/PI;
        vel_pub.publish(vel_msg);
        std::cout<<"omega: "<<position_w*180/PI<<"\n";
        std::cout<<"delta_rotation: "<<delta_rotation<<"\n";
        rate.sleep(); 
    }
    std::cout<<"rotation_stop\n";
    vel_msg.angular.z = 0;
    vel_pub.publish(vel_msg);
}
