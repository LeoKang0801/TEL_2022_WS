#include <vl53l0x_control.h>

void callbackfunc(const std_msgs::Float64MultiArray::ConstPtr &msg){

    vl53l0x[0] = msg->data[0];
    vl53l0x[1] = msg->data[1];
    vl53l0x[2] = msg->data[2];
    vl53l0x[3] = msg->data[3];

}

void calib_front(){

    ros::spinOnce();

    if(vl53l0x[0] > vl53l0x[1]){ //counterclockwise +

        rotate = 0;

    }else if(vl53l0x[0] < vl53l0x[1]){  // clockwise -

        rotate = 2;
        
    }

    do_calib(rotate);

}

void calib_left(){

    ros::spinOnce();

    if(vl53l0x[2] > vl53l0x[3]){
            
       rotate = 1;

    }else if(vl53l0x[2] < vl53l0x[3]){
            
        rotate = 3;

    }

    do_calib(rotate);

}

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "vl53l0x_control");
    ros::NodeHandle nh;
    vl53l0x_sub = nh.subscribe("tof_data", 1, callbackfunc);
    vl53l0x_pub = nh.advertise<geometry_msgs::Twist>("vl53l0x_vel",1);
    int first = 1;

    while(ros::ok()){

        if(first){

            while(vl53l0x[0] == 0 || vl53l0x[1] == 0 || vl53l0x[2] == 0 || vl53l0x[3] == 0){
                        
                ros::spinOnce();
                first = 0;
                    
            }
        }
        ros::spinOnce();

        //call function
        calib_front();
        calib_left();

        rate.sleep();

    }

}

void do_calib(int rotate){

    switch(rotate){

        case 0:

            while(vl53l0x[0]-vl53l0x[1] >= allow){

                ros::spinOnce();
                // p control
                if(vl53l0x[0]-vl53l0x[1] > 5)
                    vl53l0x_vel.angular.z = (vl53l0x[0]-vl53l0x[1]) * 0.05;
                if(vl53l0x[0]-vl53l0x[1] > 1 && vl53l0x[0]-vl53l0x[1] < 5)
                    vl53l0x_vel.angular.z = (vl53l0x[0]-vl53l0x[1]) * 0.1;
                if(vl53l0x[0]-vl53l0x[1] < 1)
                    vl53l0x_vel.angular.z = (vl53l0x[0]-vl53l0x[1]) * 0.2;
                //
                vl53l0x_pub.publish(vl53l0x_vel);

            }
            break;
        case 1:

            while(vl53l0x[2]-vl53l0x[3] >= allow){

                ros::spinOnce();
                // p control
                if(vl53l0x[2]-vl53l0x[3] > 5)
                    vl53l0x_vel.angular.z = (vl53l0x[2]-vl53l0x[3]) * 0.05;
                if(vl53l0x[2]-vl53l0x[3] > 1 && vl53l0x[2]-vl53l0x[3] < 5)
                    vl53l0x_vel.angular.z = (vl53l0x[2]-vl53l0x[3]) * 0.1;
                if(vl53l0x[2]-vl53l0x[3] < 1)
                    vl53l0x_vel.angular.z = (vl53l0x[2]-vl53l0x[3]) * 0.2;
                //
                vl53l0x_pub.publish(vl53l0x_vel);

            }
            break;
        case 2:

            while(vl53l0x[1]-vl53l0x[0] >= allow){

                ros::spinOnce();
                // p control
                if(vl53l0x[1]-vl53l0x[0] > 5)
                    vl53l0x_vel.angular.z = -(vl53l0x[1]-vl53l0x[0]) * 0.05;
                if(vl53l0x[1]-vl53l0x[0] > 1 && vl53l0x[1]-vl53l0x[0] < 5)
                    vl53l0x_vel.angular.z = -(vl53l0x[1]-vl53l0x[0]) * 0.1;
                if(vl53l0x[1]-vl53l0x[0] < 1)
                    vl53l0x_vel.angular.z = -(vl53l0x[1]-vl53l0x[0]) * 0.2;
                //
                vl53l0x_pub.publish(vl53l0x_vel);

            }
            break;
        case 3:

            while(vl53l0x[3]-vl53l0x[2] >= allow){

                ros::spinOnce();
                // p control
                if(vl53l0x[3]-vl53l0x[2] > 5)
                    vl53l0x_vel.angular.z = (vl53l0x[3]-vl53l0x[2]) * 0.05;
                if(vl53l0x[3]-vl53l0x[2] > 1 && vl53l0x[3]-vl53l0x[2] < 5)
                    vl53l0x_vel.angular.z = (vl53l0x[3]-vl53l0x[2]) * 0.1;
                if(vl53l0x[3]-vl53l0x[2] < 1)
                    vl53l0x_vel.angular.z = (vl53l0x[3]-vl53l0x[2]) * 0.2;
                //
                vl53l0x_pub.publish(vl53l0x_vel);

            }
            break;
        case 4:

            break;

    }

}