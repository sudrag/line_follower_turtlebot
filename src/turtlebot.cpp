#include <geometry_msgs/Twist.h>
#include <vector>
#include "ros/ros.h"
#include "ros/console.h"
#include "turtlebot.hpp"
#include "line_follower_turtlebot/pos.h"

void turtlebot::dir_sub(line_follower_turtlebot::pos msg) {
	dir = msg.direction;
}
void turtlebot::vel_cmd(geometry_msgs::Twist &velocity, ros::Publisher &pub, ros::Rate &rate){

			//ROS_INFO_STREAM("Moving towards centroid");
				if(dir==0){
				velocity.linear.x = 0.2;
        		velocity.angular.z = 0.2;
         		// std::cout << velocity.linear.x << std::endl;
        		pub.publish(velocity);
        		rate.sleep();
        		ROS_INFO_STREAM(velocity);
        	}
				if(dir==1){
				velocity.linear.x = 0.2;
        		velocity.angular.z = 0;
         		// std::cout << velocity.linear.x << std::endl;
        		pub.publish(velocity);
        		rate.sleep();
        		ROS_INFO_STREAM(velocity);
        		ROS_INFO_STREAM(dir);
        	}
				if(dir==2){
				velocity.linear.x = 0.2;
        		velocity.angular.z = -0.2;
         		// std::cout << velocity.linear.x << std::endl;
        		pub.publish(velocity);
        		rate.sleep();
        		ROS_INFO_STREAM(velocity);
        	}
        	ROS_INFO_STREAM(dir);
        	}
