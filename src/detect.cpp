
#include <cstdlib>
#include <string>
// #include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include "ros/console.h"
#include "linedetect.hpp"
#include "line_follower_turtlebot/pos.h"



int main(int argc, char **argv) {
	// Node creation
	ros::init(argc, argv, "detection");
	ros::NodeHandle n;

	// Initializations
	LineDetect det;
	cv::Mat output;
	//int dir;

	// Image Subscriber
	ros::Subscriber sub = n.subscribe("/camera/rgb/image_raw", 
		1, &LineDetect::imageCallback, &det);

	ros::Publisher dirPub = n.advertise<line_follower_turtlebot::pos>("direction", 1);
		line_follower_turtlebot::pos msg;

	while (ros::ok()) {
		if (!det.img.empty()) {
			
			// Get the detections
			det.img_filt = det.Gauss(det.img);	
			output=det.colorthresh(det.img_filt,det.dir);
			msg.direction=det.dir;
			dirPub.publish(msg);
			//ROS_INFO_STREAM(det.dir);
			}
		ros::spinOnce();
	}
	cv::destroyWindow("view2");
	cv::destroyWindow("view3");


}
