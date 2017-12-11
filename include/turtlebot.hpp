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
*@file turtlebot.hpp
*@author Sudarshan Raghunathan
*@brief  Class definition for turtlebot
*/

#pragma once
#include <geometry_msgs/Twist.h>
#include <vector>
#include "ros/ros.h"
#include "line_follower_turtlebot/pos.h"

/**
*@brief Class turtlebot subscribes to the directions published and publishes velocity commands
*/
class turtlebot {
 public:
    int dir;  /// Direction message to read published directions
/**
*@brief Callback used to subscribe to the direction message published by the Line detection node
*@param msg is the custom message pos which publishes a direction int between 0 and 3
*@return none
*/
    void dir_sub(line_follower_turtlebot::pos msg);
/**
*@brief Function to publish velocity commands based on direction
*@param velocity is the twist 
*@param pub is used to publish the velocity commands to the turtlebot
*@param rate is the ros loop rate for publishing the commands
*@return none
*/
    void vel_cmd(geometry_msgs::Twist &velocity,
     ros::Publisher &pub, ros::Rate &rate);
};
