cmake_minimum_required(VERSION 2.8.3)
project(hero_gazebo)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  urdf
  xacro
  roscpp
  gazebo_ros
)

# Depend on system install of Gazebo
find_package(gazebo REQUIRED)

find_package(Boost REQUIRED COMPONENTS thread)

link_directories(${Boost_LIBRARY_DIRS} ${GAZEBO_LIBRARY_DIRS})
include_directories(include ${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS})

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES hero_gazebo
  DEPENDS 
    roscpp 
    gazebo_ros 
)

add_library(gazebo_ros_hero_color src/gazebo_ros_hero_color.cpp)
target_link_libraries(gazebo_ros_hero_color ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES}  ${Boost_LIBRARIES})

