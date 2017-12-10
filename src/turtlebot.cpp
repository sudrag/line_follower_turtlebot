	#include <geometry_msgs/Twist.h>
	#include <vector>
	#include "ros/ros.h"
	#include "ros/console.h"
	#include "turtlebot.hpp"
	#include "line_follower_turtlebot/pos.h"

void turtlebot::dir_sub(line_follower_turtlebot::pos msg) {
	turtlebot::dir = msg.direction;
}
void turtlebot::vel_cmd(geometry_msgs::Twist &velocity, ros::Publisher &pub, ros::Rate &rate){

	if(turtlebot::dir==0){
		velocity.linear.x = 0.1;
		velocity.angular.z = 0.15;
		pub.publish(velocity);
		rate.sleep();
	    ROS_INFO_STREAM("Turning Left");
	}
	if(turtlebot::dir==1){
		velocity.linear.x = 0.2;
		velocity.angular.z = 0;
		pub.publish(velocity);
		rate.sleep();
	  	ROS_INFO_STREAM("Straight");
	}
	if(turtlebot::dir==2){
		velocity.linear.x = 0.1;
		velocity.angular.z = -0.15;
		pub.publish(velocity);
		rate.sleep();
	    ROS_INFO_STREAM("Turning Right");
	}
	if(turtlebot::dir==3){
		velocity.linear.x=0;
		velocity.linear.y=0;
		pub.publish(velocity);
		rate.sleep();
		ROS_INFO_STREAM("Stopping");
	}
}
