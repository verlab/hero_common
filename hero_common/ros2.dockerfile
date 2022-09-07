FROM ros:foxy-ros1-bridge

# install ros package
# RUN apt-get update && apt-get install -y \
#       ros-${ROS_DISTRO}-ros1-bridge && \
#     rm -rf /var/lib/apt/lists/*

# launch ros package
# CMD ["ros2", "launch", "demo_nodes_cpp", "talker_listener.launch.py"]