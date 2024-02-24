#! /usr/bin/bash

xhost +

docker run --rm -it --privileged --net=host \
    --gpus all \
    --env=NVIDIA_VISIBLE_DEVICES=all \
    --env=NVIDIA_DRIVER_CAPABILITIES=all \
    --env=DISPLAY \
    --env=QT_X11_NO_MITSHM=1 \
    --volume=/tmp/.X11-unix:/tmp/.X11-unix:rw \
    --volume=$HOME/.Xauthority:/root/.Xauthority:rw \
    --volume=$PWD/../../hero_common:/catkin_ws/src/hero_common:rw \
    --runtime=nvidia hero_common:ros1-noetic