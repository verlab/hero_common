cmake_minimum_required(VERSION 2.8.3)
project(hero_genesis)

find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
  geometry_msgs
  nav_msgs
  sensor_msgs
  tf
  hero_common
)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

install(PROGRAMS
  scripts/hero_genesis_node.py
  scripts/genesis_engine.py
  scripts/circle_line_demo.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
