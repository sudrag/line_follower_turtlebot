
#include <cstdlib>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "ros/ros.h"
#include "opencv2/opencv.hpp"
#include "ros/console.h"
#include "linedetect.hpp"
#include "line_follower_turtlebot/pos.h"

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

  	return output;


}

cv::Mat LineDetect::colorthresh(cv::Mat input,int dir){
  cv::Size s = input.size();
  float w = s.width;
  float h = s.height;
  float c_x;
  float c_y;
	cv::cvtColor(input,LineDetect::img_hsv, CV_BGR2HSV);
    LineDetect::LowerYellow = {20,100,100};
    LineDetect::UpperYellow = {30,255,255};
    cv::inRange(LineDetect::img_hsv, LowerYellow, UpperYellow, LineDetect::img_mask);
    img_mask(cv::Rect(0,0,w,0.9*h))=0;
		img_mask(cv::Rect(0,0,0.3*w,h))=0;
    cv::Moments M = cv::moments(LineDetect::img_mask);
        if (M.m00 > 0) {
        cv::Point p1(M.m10/M.m00, M.m01/M.m00);
    	cv::circle(LineDetect::img_mask, p1, 5, cv::Scalar(155,200,0), -1);
		}
      c_x=M.m10/M.m00;
      c_y=M.m01/M.m00;
      float tmp = h*0.7;
      int tol=20;
      int count=cv::countNonZero(img_mask);
      if(c_x<w/2-tol){
        LineDetect::dir=0;
      } else if(c_x>w/2+tol){
        LineDetect::dir=2;
      } else {
        LineDetect::dir=1;
      }
      if(count==0){
        LineDetect::dir=3;
      } 
      //ROS_INFO_STREAM(dir);
        cv::namedWindow("view3");
			imshow("view3", LineDetect::img_mask);
		return LineDetect::img_mask;
    
}
