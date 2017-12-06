#pragma once

#include <geometry_msgs/Twist.h>
#include <vector>
#include "ros/ros.h"
#include "line_follower_turtlebot/pos.h"

class turtlebot {
private:
	int dir;
public:
	void dir_sub(line_follower_turtlebot::pos msg);
	void vel_cmd(geometry_msgs::Twist &velocity, ros::Publisher &pub, ros::Rate &loop_rate);
};