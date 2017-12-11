
#include <cv_bridge/cv_bridge.h>
#include <gtest/gtest.h>
#include <opencv2/highgui/highgui.hpp>
#include "ros/ros.h"
#include "opencv2/opencv.hpp"
#include "linedetect.hpp"
#include "line_follower_turtlebot/pos.h"

int turn_left() {
    ros::NodeHandle n;
    LineDetect det;
    
    cv::String im_path1 = "./test_images/left_turn.png";
    det.img = cv::imread(im_path1);

    if (!det.img.empty()) {
        det.img_filt = det.Gauss(det.img);  
        det.dir=det.colorthresh(det.img_filt);
        return det.dir;
    }
}
int drive_straight() {
    ros::NodeHandle n;
    LineDetect det;
    
    cv::String im_path = "./test_images/straight.png";
    det.img = cv::imread(im_path);

    if (!det.img.empty()) {
        det.img_filt = det.Gauss(det.img);  
        det.dir=det.colorthresh(det.img_filt);
        return det.dir;
    }
}
int turn_right() {
    ros::NodeHandle n;
    LineDetect det;
    
    cv::String im_path2 = "./test_images/right_turn.png";
    det.img = cv::imread(im_path2);

    if (!det.img.empty()) {
        det.img_filt = det.Gauss(det.img);  
        det.dir=det.colorthresh(det.img_filt);
        return det.dir;
    }
}
int stop() {
    ros::NodeHandle n;
    LineDetect det;
    
    cv::String im_path3 = "./test_images/stop.png";
    det.img = cv::imread(im_path3);

    if (!det.img.empty()) {
        det.img_filt = det.Gauss(det.img);  
        det.dir=det.colorthresh(det.img_filt);
        return det.dir;
    }
}

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

TEST(TestDirections, Teststraight) {
    int direction = drive_straight();
    EXPECT_EQ(1, direction);
}

TEST(TestDirections, Testleft) {
    int direction = turn_left();
    EXPECT_EQ(0, direction);
}

TEST(TestDirections, Testright ) {
    int direction = turn_right();
    EXPECT_EQ(2, direction);
}

TEST(TestDirections, Teststop ) {
    int direction = stop();
    EXPECT_EQ(3, direction);
}

TEST (TestDetFunc , TestGauss) {
    EXPECT_EQ (true , gauss());
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "test_detection");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}