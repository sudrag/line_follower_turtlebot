
#include <cstdlib>
#include <string>
#include <ros/package.h>
#include <sstream>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <gtest/gtest.h>
#include <boost/thread.hpp>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include "ros/console.h"
#include "turtlebot.hpp"
#include "line_follower_turtlebot/pos.h"

double ang_vel(int direction) {
    ros::NodeHandle n;
    turtlebot bot;
    geometry_msgs::Twist velocity;
    // Publisher
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>
    ("/cmd_vel_mux/input/teleop", 1000);

    bot.dir=direction;
    ros::Rate rate(10);
    ros::spinOnce();
    bot.vel_cmd(velocity, pub, rate);
    rate.sleep();
    return velocity.angular.z ;
}
double linear_vel(int direction){
    ros::NodeHandle n;
    turtlebot bot;
    geometry_msgs::Twist velocity;
    // Publisher
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>
    ("/cmd_vel_mux/input/teleop", 1000);

    bot.dir=direction;
    ros::Rate rate(100);
    ros::spinOnce();
    bot.vel_cmd(velocity, pub, rate);
    rate.sleep();
    return velocity.linear.x ;
}

void processThread(void) {
    ros::Rate rate(10);
    while (ros::ok()) {
        ros::spinOnce();
        rate.sleep();
    }
}



TEST(TestROS, TestPubSub)
{
  ros::NodeHandle nh;
  geometry_msgs::Twist velocity;
  ros::Rate rate(10);
  turtlebot bot;
  ros::Publisher pub = nh.advertise<line_follower_turtlebot::pos>
   ("direction",1000);
  ros::Subscriber sub = nh.subscribe("/direction", 
        1, &turtlebot::dir_sub, &bot);

    line_follower_turtlebot::pos msg;
    msg.direction = 0;
    pub.publish(msg);

    ros::spinOnce();
    rate.sleep();

    EXPECT_EQ(1, sub.getNumPublishers());
    EXPECT_EQ(1, pub.getNumSubscribers());
    EXPECT_EQ(msg.direction,bot.dir);
}


TEST(TestVelocity, Teststraight_vel) {
    double rot = ang_vel(1);
    double trans = linear_vel(1);
    EXPECT_EQ(0,rot);
    EXPECT_EQ(0.2,trans);
}

TEST(TestDirections, Testleft_vel) {
    double rot = ang_vel(0);
    double trans = linear_vel(0);
    EXPECT_EQ(0.15,rot);
    EXPECT_EQ(0.1,trans);
}

TEST(TestDirections, Testright_vel) {
    double rot = ang_vel(2);
    double trans = linear_vel(2);
    EXPECT_EQ(-0.15,rot);
    EXPECT_EQ(0.1,trans);
}

TEST(TestDirections, Teststop_vel) {
    double rot = ang_vel(3);
    double trans = linear_vel(3);
    EXPECT_EQ(0,rot);
    EXPECT_EQ(0,trans);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "test_velocity");
    testing::InitGoogleTest(&argc, argv);  
    ros::NodeHandle nh;
    boost::thread th(processThread);
    int test_flag =RUN_ALL_TESTS();
    ros::shutdown();
    th.join();
    return test_flag;
}