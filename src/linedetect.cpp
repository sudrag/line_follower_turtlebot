
#include <cstdlib>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "ros/ros.h"
#include "opencv2/opencv.hpp"
#include "ros/console.h"
#include "linedetect.hpp"

void LineDetect::imageCallback(const sensor_msgs::ImageConstPtr& msg) {
	cv_bridge::CvImagePtr cv_ptr;
	try {
    	cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    	img = cv_ptr->image;
    	// cv::imshow("view", imagen);
    	cv::waitKey(30);
  	}
  	catch (cv_bridge::Exception& e) {
    	ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  	}
}

cv::Mat LineDetect::Gauss(cv::Mat input) {
  	cv::Mat output;

  	cv::GaussianBlur(input, output, cv::Size(3, 3), 0, 0);

  	cv::namedWindow("view2");
			imshow("view2", output);


  	return output;


}

cv::Mat LineDetect::colorthresh(cv::Mat input){
	cv::cvtColor(input,LineDetect::img_hsv, CV_BGR2HSV);
    //LineDetect::LowerYellow = {{ 10, 10, 10}};
   // LineDetect::UpperYellow = {{255, 255, 250}};
    int low[3]={0,0,0};
    int up[3]={1,1,1};
    //img_mask = cv2.inRange(img_hsv, LowerYellow, UpperYellow);
    //LineDetect::img_mask = cv2.inRange(LineDetect::img_hsv, low,up);
    cv::inRange(LineDetect::img_hsv, cv::Scalar(20, 100, 100), cv::Scalar(30, 255, 255), LineDetect::img_mask);
    cv::namedWindow("view3");
			imshow("view3", LineDetect::img_mask);

                // h, w, d = image.shape
                // search_top = 3*h/4
                // search_bot = 3*h/4 + 20
                // mask[0:search_top, 0:w] = 0
                // mask[search_bot:h, 0:w] = 0

                // M = cv2.moments(mask)
}

