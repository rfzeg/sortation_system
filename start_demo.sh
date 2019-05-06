#!/bin/sh
echo "Sortation System Simulation"
echo ""
echo "Make sure you have sourced devel/setup.bash"
echo ""
xterm  -e  "roslaunch sortation_system gazebo.launch" &
sleep 8s

xterm -e "roslaunch sortation_system spawn_conveyor.launch" &
sleep 4s &

xterm -e "roslaunch sortation_system spawn_portal_frame.launch" &
sleep 4s &

xterm -e "roslaunch sortation_system spawn_camera.launch"
