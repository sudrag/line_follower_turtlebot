cmake_minimum_required(VERSION 2.8.3)
project(line_follower_turtlebot)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS cv_bridge roscpp rospy std_msgs genmsg geometry_msgs)
find_package(OpenCV REQUIRED)

catkin_package()

## Executables
include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(detect src/detect.cpp src/linedetect.cpp)
target_link_libraries(detect ${catkin_LIBRARIES} ${OpenCV_LIBS})