#include "ros/ros.h"
#include "std_msgs/String.h"

#include "sstream"
#include<iostream>
using namespace std;

 int main(int argc, char **argv)
 {
     ros::init(argc,argv,"talker");
     ros::NodeHandle n;

     ros::Publisher topic_pub = n.advertise<std_msgs::String>("/team_abhiyaan", 1000);
     ros::Rate loop_rate(1);
     while(ros::ok())
     {
         std_msgs::String msg;
         std::stringstream ss;
         ss<<"Team Abhiyaan Rocks";
         msg.data = ss.str();
         //ROS_INFO("%s",msg.data.c_str());
         
         topic_pub.publish(msg);
         ros::spinOnce();

         loop_rate.sleep();
     }
     

 }