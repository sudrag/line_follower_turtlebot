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
*@file test_detect.cpp
*@author Sudarshan Raghunathan
*@brief  Unit Test for all the functions in the detection class
*/

#include <cv_bridge/cv_bridge.h>
#include <gtest/gtest.h>
#include <opencv2/highgui/highgui.hpp>
#include "ros/ros.h"
#include "opencv2/opencv.hpp"
#include "linedetect.hpp"
#include "line_follower_turtlebot/pos.h"

/**
*@brief Testing if detection works accurately and publishes left accurately
*@return int dir which is the direction to move in
*/
int turn_left() {
    ros::NodeHandle n;
    LineDetect det;
    cv::String im_path1 = "./test_images/left_turn.png";
    det.img = cv::imread(im_path1);

    if (!det.img.empty()) {
        det.img_filt = det.Gauss(det.img);
        det.dir = det.colorthresh(det.img_filt);
        return det.dir;
    }
}
/**
*@brief Testing if detection works accurately and publishes straight accurately
*@return int dir which is the direction to move in
*/
int drive_straight() {
    ros::NodeHandle n;
    LineDetect det;
    cv::String im_path = "./test_images/straight.png";
    det.img = cv::imread(im_path);
    if (!det.img.empty()) {
        det.img_filt = det.Gauss(det.img);
        det.dir = det.colorthresh(det.img_filt);
        return det.dir;
    }
}
/**
*@brief Testing if detection works accurately and publishes right accurately
*@return int dir which is the direction to move in
*/
int turn_right() {
    ros::NodeHandle n;
    LineDetect det;
    cv::String im_path2 = "./test_images/right_turn.png";
    det.img = cv::imread(im_path2);

    if (!det.img.empty()) {
        det.img_filt = det.Gauss(det.img);
        det.dir = det.colorthresh(det.img_filt);
        return det.dir;
    }
}

/**
*@brief Testing if detection works accurately and publishes stop accurately
*@return int dir which is the direction to move in
*/
int stop() {
    ros::NodeHandle n;
    LineDetect det;
    cv::String im_path3 = "./test_images/stop.png";
    det.img = cv::imread(im_path3);

    if (!det.img.empty()) {
        det.img_filt = det.Gauss(det.img);
        det.dir = det.colorthresh(det.img_filt);
        return det.dir;
    }
}
/**
*@brief Testing if gaussian filtering functions properly
*@return bool to test if function worked well
*/
bool gauss() {
    ros::NodeHandle n;
    LineDetect det;
    cv::String im_path3 = "./test_images/stop.png";
    det.img = cv::imread(im_path3);
    cv::Size im_size = det.img.size();
    det.img_filt = det.Gauss(det.img);
    cv::Size imfilt_size = det.img_filt.size();
    if (im_size == imfilt_size)
        return true;
}

/**
*@brief Testing if direction published is straight 
*/

TEST(TestDirections, Teststraight) {
    int direction = drive_straight();
    EXPECT_EQ(1, direction);
}

/**
*@brief Testing if direction published is left
*/

TEST(TestDirections, Testleft) {
    int direction = turn_left();
    EXPECT_EQ(0, direction);
}

/**
*@brief Testing if direction published is right 
*/

TEST(TestDirections, Testright ) {
    int direction = turn_right();
    EXPECT_EQ(2, direction);
}

/**
*@brief Testing if search command is published 
*/

TEST(TestDirections, Testsearch ) {
    int direction = stop();
    EXPECT_EQ(3, direction);
}

/**
*@brief Testing if Gaussian filter is applied to image properly 
*/

TEST(TestDetFunc , TestGauss) {
    EXPECT_EQ(true , gauss());
}
/**
 *@brief Function to run all the tests for the detection node
 *@param argc is the number of arguments of the main function
 *@param argv is the array of arugments
 *@return result of the tests
 */
int main(int argc, char **argv) {
    ros::init(argc, argv, "test_detection");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
