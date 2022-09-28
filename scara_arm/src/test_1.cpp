#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/Int64.h>

int main(int argc, char** argv){

    ros::init(argc, argv, "test_1");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<geometry_msgs::Point>("Destination", 1);
    ros::Publisher pub_init = nh.advertise<std_msgs::Int64>("test/init", 1);
    
    geometry_msgs::Point goal;
    std_msgs::Int64 init;
    
    
    //char quit;
    init.data = 1;
    int count = 0;

    while(ros::ok()){
        // ..............................................
        if(count == 0){
            
            std::cout << "Waiting ... " << std::endl;
            for(int i=0;i<15;i++){
                pub_init.publish(init);
                ros::Duration(0.5).sleep();
            }
            count++;
            
        }

       
        
        std::cout << "Enter a point (x, y)" << std::endl;
        init.data = 0;
        std::cin >> goal.x >> goal.y;
        pub_init.publish(init);
        pub.publish(goal);
        // std::cin >> goal.y;



        // std::cout << "Press any key to continue, or press 'q' to quit" << std::endl;

        // std::cin >> quit;
        // if(quit == 'q'){
        //     break;
        // }

    }
    

}

