
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

  	cv::namedWindow("view2");
			imshow("view2", output);


  	return output;


}

cv::Mat LineDetect::colorthresh(cv::Mat input,int dir){
  float w;
  float h;
  float c_x;
	cv::cvtColor(input,LineDetect::img_hsv, CV_BGR2HSV);
    LineDetect::LowerYellow = {20,100,100};
    LineDetect::UpperYellow = {30,255,255};
    cv::inRange(LineDetect::img_hsv, LowerYellow, UpperYellow, LineDetect::img_mask);
		cv::Moments M = cv::moments(LineDetect::img_mask);
        if (M.m00 > 0) {
        cv::Point p1(M.m10/M.m00, M.m01/M.m00);
    	cv::circle(LineDetect::img_mask, p1, 5, cv::Scalar(155,200,0), -1);
		}
      cv::Size s = input.size();
      h = s.height;
      w = s.width;
      c_x=M.m10/M.m00;
      if(c_x-5<w)
        dir=0;
      else if(c_x+5>w>c_x-5)
        dir=1;
      else if(w>c_x+5)
        dir=2;

        cv::namedWindow("view3");
			imshow("view3", LineDetect::img_mask);
		return LineDetect::img_mask;
}
