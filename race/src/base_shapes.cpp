#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main(int argc, char**argv)
{
    ros::init(argc, argv,"basic_shapes");
    ros::NodeHandle nh;
    ros::Rate rate(1);
    ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("vis_marker",1);
    int arr[2]={50,-50};
    bool i = 0;

    uint32_t shape = visualization_msgs::Marker::CUBE;
    while(ros::ok())
    {
        visualization_msgs::Marker marker;
        marker.header.frame_id = "world_frame";
        marker.header.stamp = ros::Time::now();
        marker.ns = "basic_shapes";
        marker.id = 0;
        marker.type = shape;
        marker.action = visualization_msgs::Marker::ADD;

        marker.pose.position.x = 175;
        marker.pose.position.y = arr[i];
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;

        marker.scale.x = 350.0;
        marker.scale.y = 1.0;
        marker.scale.z = 1.0;

        marker.color.r = 0.0f;
        marker.color.g = 0.0f;
        marker.color.b = 1.0f;
        marker.color.a = 1.0;

        marker.lifetime = ros::Duration();
        marker_pub.publish(marker);
        i = -i;
    }
}