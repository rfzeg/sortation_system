#!/bin/sh
echo ""
echo "ROS Sortation System Project Demo"
echo ""
# Fire up Gazebo world with conveyor belt model & plugin
xterm -e "roslaunch conveyor_gazebo conveyor.launch" &
sleep 12 &

xterm -e "rosservice call /conveyor/control 'state:
  power: 30.0'" &
sleep 4 &

xterm -e "roslaunch sortation_system spawn_portal_frame.launch" &
sleep 4 &

xterm -e "roslaunch sortation_system spawn_camera_link.launch" &
sleep 4 &

# Launches a box with AR tags on each side
# xterm -e "roslaunch sortation_system spawn_box.launch" &

# Launch object_spawner node
xterm -e "roslaunch sortation_system object_spawner.launch" &
sleep 6 &

# Start RVIZ with a preconfigured view
xterm -e "roslaunch sortation_system rviz.launch" &
sleep 4 &

# Launch ar_track_alvar to detect AR markers and localize them in space
xterm -e "roslaunch sortation_system ar_track.launch" # &

# sleep 4 &
# xterm -e "rosservice call /gazebo/unpause_physics '{}'"
