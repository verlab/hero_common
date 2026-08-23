#!/bin/bash
set -e
source /opt/ros/noetic/setup.bash
if [ -f /catkin_ws/devel/setup.bash ]; then
  source /catkin_ws/devel/setup.bash
fi
exec "$@"
