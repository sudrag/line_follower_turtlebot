/** MIT License
Copyright (c) 2017 Sudarshan Raghunathan
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*
*@copyright Copyright 2017 Sudarshan Raghunathan
*@file linedetect.cpp
*@author Sudarshan Raghunathan
*@brief  Class linedetect's function definitions
*/
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
   cv::waitKey(30);
 }
 catch (cv_bridge::Exception& e) {
   ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
 }
}

cv::Mat LineDetect::Gauss(cv::Mat input) {
 cv::Mat output;
    //Applying Gaussian Filter
 cv::GaussianBlur(input, output, cv::Size(3, 3), 0.1, 0.1);
 return output;
}

int LineDetect::colorthresh(cv::Mat input){
  //Initializaing variables
  cv::Size s = input.size();
  float w = s.width;
  float h = s.height;
  float c_x;
  float c_y;
  //Detect all objects within the HSV range
  cv::cvtColor(input,LineDetect::img_hsv, CV_BGR2HSV);
  LineDetect::LowerYellow = {20,100,100};
  LineDetect::UpperYellow = {30,255,255};
  cv::inRange(LineDetect::img_hsv, LowerYellow, UpperYellow, LineDetect::img_mask);
  //Mask image to limit the future turns affecting the output
  img_mask(cv::Rect(0,0,w,0.9*h))=0;
  img_mask(cv::Rect(0.7*w,0,0.3*w,h))=0;
  img_mask(cv::Rect(0,0,0.3*w,h))=0;
  //Perform centroid detection of line
  cv::Moments M = cv::moments(LineDetect::img_mask);
  if (M.m00 > 0) {
    cv::Point p1(M.m10/M.m00, M.m01/M.m00);
    cv::circle(LineDetect::img_mask, p1, 5, cv::Scalar(155,200,0), -1);
  }
  c_x=M.m10/M.m00;
  c_y=M.m01/M.m00;
  //Tolerance to chooise directions
  int tol=20;
  int count=cv::countNonZero(img_mask);
  //Turn left if centroid is to the left of the image center minus tolerance
  //Turn right if centroid is to the right of the image center plus tolerance
  //Go straight if centroid is near image center
  if(c_x<w/2-tol){
    LineDetect::dir=0;
  } else if(c_x>w/2+tol){
    LineDetect::dir=2;
  } else {
    LineDetect::dir=1;
  }
  //Stop if no line detected
  if(count==0){
    LineDetect::dir=3;
  } 
  //Output images viewed by the turtlebot
  cv::namedWindow("view2");
  imshow("view2", input);
  cv::namedWindow("view3");
  imshow("view3", LineDetect::img_mask);
  return LineDetect::dir;

}
