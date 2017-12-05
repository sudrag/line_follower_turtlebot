
#include <cstdlib>
#include <string>
// #include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include "ros/console.h"
#include "linedetect.hpp"



int main(int argc, char **argv) {
	// Node creation
	ros::init(argc, argv, "detection");
	ros::NodeHandle n;

	// Initializations
	LineDetect det;
	cv::Mat output;

	// Image Subscriber
	ros::Subscriber sub = n.subscribe("/camera/rgb/image_raw", 
		1, &LineDetect::imageCallback, &det);

	while (ros::ok()) {
		if (!det.img.empty()) {
			
			// Get the detections
			det.img_filt = det.Gauss(det.img);	
			output=det.colorthresh(det.img_filt);
			}
		ros::spinOnce();
	}
	cv::destroyWindow("view2");
	cv::destroyWindow("view3");


}
