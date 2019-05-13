#!/bin/sh
echo ""
echo "ROS Sortation System Project Demo"
echo ""
xterm  -e  "roslaunch sortation_system gazebo.launch" &
sleep 10

xterm -e "roslaunch sortation_system spawn_conveyor.launch" &
sleep 4 &

xterm -e "roslaunch sortation_system spawn_portal_frame.launch" &
sleep 4 &

xterm -e "roslaunch sortation_system spawn_camera_link.launch" &
sleep 4 &

# Launches a box with AR tags on each side
xterm -e "roslaunch sortation_system spawn_box.launch" &
sleep 6 &

# start RVIZ with a preconfigured view
xterm -e "roslaunch sortation_system rviz.launch" &
sleep 4 &

# launch ar_track_alvar to detect AR markers and localize them in space
xterm -e "roslaunch sortation_system ar_track.launch" &

sleep 4 &
xterm -e "rosservice call /gazebo/unpause_physics '{}'"
