
#include <cstdlib>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include "ros/console.h"
#include "turtlebot.hpp"
#include "line_follower_turtlebot/pos.h"

int main(int argc, char **argv) {
	// Node creation
	ros::init(argc, argv, "Velocity");
	ros::NodeHandle n;

	// Initializations
	turtlebot bot;
	geometry_msgs::Twist velocity;

	// Subscriber
	ros::Subscriber sub = n.subscribe("/direction", 
		1, &turtlebot::dir_sub, &bot);

	// Publisher
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>
        ("/cmd_vel_mux/input/teleop", 1000);

    ros::Rate rate(10);
	while (ros::ok()) {
			ros::spinOnce();
		bot.vel_cmd(velocity, pub, rate);
		rate.sleep();
	}
	return 0;
}