#pragma once

#include <geometry_msgs/Twist.h>
#include <vector>
#include "ros/ros.h"
#include "line_follower_turtlebot/pos.h"

class turtlebot {
public:
	void dir_sub(line_follower_turtlebot::pos msg);
	int dir;
	void vel_cmd(geometry_msgs::Twist &velocity, ros::Publisher &pub, ros::Rate &loop_rate);
};