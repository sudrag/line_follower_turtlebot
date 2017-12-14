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
*@file test_navig.cpp
*@author Sudarshan Raghunathan
*@brief  Unit Test for all the functions in the turtlebot navigation class
*/
#include <cv_bridge/cv_bridge.h>
#include <gtest/gtest.h>
#include <ros/package.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <opencv2/highgui/highgui.hpp>
#include <boost/thread.hpp>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include "ros/console.h"
#include "turtlebot.hpp"
#include "line_follower_turtlebot/pos.h"

/**
*@brief Testing if detection works accurately and publishes straight accurately
*@return int dir which is the direction to move in
*/
double ang_vel(int direction) {
    ros::NodeHandle n;
    turtlebot bot;
    geometry_msgs::Twist velocity;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>
    ("/cmd_vel_mux/input/teleop", 10);
    bot.dir = direction;
    ros::Rate rate(10);
    ros::spinOnce();
    bot.vel_cmd(velocity, pub, rate);
    rate.sleep();
    return velocity.angular.z;
}
/**
*@brief Testing if detection works accurately and publishes straight accurately
*@return int dir which is the direction to move in
*/
double linear_vel(int direction) {
    ros::NodeHandle n;
    turtlebot bot;
    geometry_msgs::Twist velocity;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>
    ("/cmd_vel_mux/input/teleop", 10);

    bot.dir = direction;
    ros::Rate rate(100);
    ros::spinOnce();
    bot.vel_cmd(velocity, pub, rate);
    rate.sleep();
    return velocity.linear.x;
}
/**
*@brief Function to spin the callbacks at a specific rate
*/
void processThread(void) {
    ros::Rate rate(10);
    while (ros::ok()) {
        ros::spinOnce();
        rate.sleep();
    }
}
/**
*@brief Testing if message subscriber is working properly 
*/
TEST(TestROS, TestPubSub) {
  ros::NodeHandle nh;
  geometry_msgs::Twist velocity;
  ros::Rate rate(10);
  turtlebot bot;
  ros::Publisher pub = nh.advertise<line_follower_turtlebot::pos>
    ("direction", 1000);
  ros::Subscriber sub = nh.subscribe("/direction",
        1, &turtlebot::dir_sub, &bot);

    line_follower_turtlebot::pos msg;
    msg.direction = 0;
    pub.publish(msg);

    ros::spinOnce();
    rate.sleep();
    EXPECT_EQ(1, sub.getNumPublishers());
    EXPECT_EQ(1, pub.getNumSubscribers());
    EXPECT_EQ(msg.direction, bot.dir);
}
/**
*@brief Testing if velocity published is for moving straight 
*/
TEST(TestVelocity, Teststraight_vel) {
    double rot = ang_vel(1);
    double trans = linear_vel(1);
    EXPECT_EQ(0, rot);
    EXPECT_EQ(0.15, trans);
}
/**
*@brief Testing if velocity published is for turning left 
*/
TEST(TestDirections, Testleft_vel) {
    double rot = ang_vel(0);
    double trans = linear_vel(0);
    EXPECT_EQ(0.15, rot);
    EXPECT_EQ(0.1, trans);
}
/**
*@brief Testing if velocity published is for turning right 
*/
TEST(TestDirections, Testright_vel) {
    double rot = ang_vel(2);
    double trans = linear_vel(2);
    EXPECT_EQ(-0.15, rot);
    EXPECT_EQ(0.1, trans);
}
/**
*@brief Testing if velocity published is for searching 
*/
TEST(TestDirections, Testsearch_vel) {
    double rot = ang_vel(3);
    double trans = linear_vel(3);
    EXPECT_EQ(0.25, rot);
    EXPECT_EQ(0, trans);
}
/**
 *@brief Function to run all the tests for the navigation node
 *@param argc is the number of arguments of the main function
 *@param argv is the array of arugments
 *@return result of the tests
 */
int main(int argc, char **argv) {
    ros::init(argc, argv, "test_velocity");
    testing::InitGoogleTest(&argc, argv);
    ros::NodeHandle nh;
    boost::thread th(processThread);
    int test_flag = RUN_ALL_TESTS();
    ros::shutdown();
    th.join();
    return test_flag;
}
