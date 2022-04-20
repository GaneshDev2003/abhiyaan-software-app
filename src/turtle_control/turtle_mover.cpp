#include<iostream>
#include "ros/ros.h"
#include<geometry_msgs/Twist.h>
#include<string.h>
#include<math.h>
#include<turtlesim/Pose.h>
#include<std_msgs/Header.h>

using namespace std;

//The publisher is gloabally declared, and is later initialized in main() function
turtlesim::Pose pos1,pos2;
geometry_msgs::Twist cur_vel1,cur_vel2;
ros::Publisher pub1,pub2;

//signum function implemented
int sgn(double x, double y)
{
    if(x>=y)
    return 1;
    else
    return -1;
}
//This function is used as a callback for subscriber that subscribes to the pose of turtle2 
void pos2CallBack(const turtlesim::Pose& pos_msg)
{
    pos2 = pos_msg;
}
//int time_interval = 0.16;

//This function is used as a callback for subscriber that subscribes to the pos of turtle1
//The same function calculates velocities of both the turtles and publishes them

// Here we assume masses to be 1, i.e m1 = 1 and m2 = 1 and we assume G = 0.1
//So Force = 0.1*1*1/squared distance

void posCallBack(const turtlesim::Pose& pos_msg)
{

    pos1 = pos_msg;
    geometry_msgs::Twist vel1,vel2;
    double sq_dist = pow(pos1.x -pos2.x , 2) + pow(pos1.y - pos2.y , 2);
    double force = 0.1/sq_dist;
    vel1.linear.x = cur_vel1.linear.x - sgn(pos1.x,pos2.x)*force*0.16;
    vel1.linear.y = cur_vel1.linear.y -  sgn(pos1.y,pos2.y)*force*0.16;
    vel1.linear.z = 0;
    vel1.angular.x = 0;
    vel1.angular.y = 0;
    vel1.angular.z = 0;
    vel2.linear.x = cur_vel2.linear.x + sgn(pos1.x,pos2.x)*force*0.16;
    vel2.linear.y = cur_vel2.linear.y +  sgn(pos1.y,pos2.y)*force*0.16;
    vel2.linear.z = 0;
    vel2.angular.x = 0;
    vel2.angular.y = 0;
    vel2.angular.z = 0;
    cur_vel1 = vel1;
    cur_vel2 = vel2;
    ROS_INFO("Velocity is %f %f" , vel1.linear.x,vel1.linear.y);
    pub1.publish(vel1);
    pub2.publish(vel2);
}
//main function initializes the turtles' y-component velocities to 0.5 and -0.5
int main(int argc, char** argv)
{
    ros::init(argc,argv,"mover");
    ros::NodeHandle n;
    cur_vel1.linear.y = 0.5;
    cur_vel2.linear.y = -0.5;
    pub1 = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1000);
    pub2 = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",1000);
    ros::Subscriber sub1 = n.subscribe("/turtle2/pose",1000,&pos2CallBack);
    ros::Subscriber sub2 = n.subscribe("/turtle1/pose",1000,&posCallBack);
    ros::spin();
    return 0;
}
