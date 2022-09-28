#include <wheel_odom.h>

// 正在改成nav_msgs格式


// ros::Time current_time, last_time;
// current_time = ros::Time::now();
// last_time = ros::Time::now();

int main(int argc, char **argv)
{
    ros::init(argc, argv, "wheel_odom");
    ros::NodeHandle nh;
    encoder_sub = nh.subscribe("encoder_data", 1, encoder_callback);
    // test
    // encoder_sub = nh.subscribe("cmd_vel", 1, encoder_callback);
    path_pub = nh.advertise<nav_msgs::Path>("wheel_path",1);
    odom_pub = nh.advertise<nav_msgs::Odometry>("wheel_odom",1);
    tf::TransformBroadcaster odom_broadcaster;

    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    last_time = ros::Time::now();

    nav_msgs::Path path;
    path.header.stamp=current_time;
    path.header.frame_id="odom_frame";

    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom_frame";

    ros::Rate rate(r);

    while (ros::ok())
    {
        current_time = ros::Time::now();
        dt = (current_time - last_time).toSec();
        delta_x = (vx*cos(position_w)-vy*sin(position_w))*dt;
        delta_y = (vy*cos(position_w)+vx*sin(position_w))*dt;
        delta_w = vw*dt;

        // vel_linear_x = 0.25*(-vel[0]+vel[1]-vel[2]+vel[3]);
        // vel_linear_y = 0.25*(vel[0]+vel[1]+vel[2]+vel[3]);
        // vel_linear_w = (1/(4*(a+b)))*(vel[0]-vel[1]-vel[2]+vel[3]);
        // 0132
        // 1243
        // 2321
        // 3410
        position_x = position_x + delta_x;
        position_y = position_y + delta_y;
        position_w = position_w + delta_w;

        //path
        geometry_msgs::PoseStamped this_pose_stamped;
        this_pose_stamped.pose.position.x = position_x;
        this_pose_stamped.pose.position.y = position_y;
        this_pose_stamped.pose.position.z = 0;
        //path
        geometry_msgs::Quaternion goal_quat = tf::createQuaternionMsgFromYaw(position_w);
        this_pose_stamped.pose.orientation.x = goal_quat.x;
        this_pose_stamped.pose.orientation.y = goal_quat.y;
        this_pose_stamped.pose.orientation.z = goal_quat.z;
        this_pose_stamped.pose.orientation.w = goal_quat.w;
        //path
        this_pose_stamped.header.stamp=current_time;
        this_pose_stamped.header.frame_id="odom_frame";

        path.poses.push_back(this_pose_stamped);

        //odom
        geometry_msgs::TransformStamped odom_trans;
        odom_trans.header.stamp = current_time;
        odom_trans.header.frame_id = "odom_frame";
        odom_trans.child_frame_id = "base_link";
        //odom        
        odom_trans.transform.translation.x = position_x;
        odom_trans.transform.translation.y = position_y;
        odom_trans.transform.translation.z = 0.0;
        odom_trans.transform.rotation = goal_quat;
        odom_broadcaster.sendTransform(odom_trans);

        odom.pose.pose.position.x = position_x;
        odom.pose.pose.position.y = position_y;
        odom.pose.pose.position.z = 0;
        //angular_z = position.z;
        odom.pose.pose.orientation = goal_quat;

        odom.child_frame_id = "base_link";
        odom.twist.twist.linear.x = vx;
        odom.twist.twist.linear.y = vy;
        odom.twist.twist.angular.z = vw;

        path_pub.publish(path);
        odom_pub.publish(odom);

        ros::spinOnce();

        ROS_INFO("%f %f %f",position_x,position_y,position_w*180/PI);
        
        last_time = current_time;
        rate.sleep();
    }
    return 0;
}


void encoder_callback(const geometry_msgs::Twist::ConstPtr& vel_data)
{
    vx = vel_data->linear.x*rpstocms;
    vy = vel_data->linear.y*rpstocms;
    vw = vel_data->angular.z;
}