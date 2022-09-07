#! /usr/bin/bash

xhost +

docker run --rm -it --privileged --net=host --gpus all -e NVIDIA_VISIBLE_DEVICES=0 --env=DISPLAY --env=NVIDIA_DRIVER_CAPABILITIES=all --env=QT_X11_NO_MITSHM=1 --volume=$HOME/.Xauthority:/root/.Xauthority:rw --volume=/tmp/.X11-unix:/tmp/.X11-unix:rw --runtime=nvidia ros:foxy-ros1-bridge