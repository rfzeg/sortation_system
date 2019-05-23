#!/bin/sh
echo ""
echo "ROS Sortation System Project Demo"
echo ""
# The -e option to xterm is useful for running a single command before exiting

# Fire up Gazebo world with conveyor belt model & plugin
xterm -e "roslaunch sortation_system conveyor.launch" &
sleep 10

# Activate the conveyor belt:
xterm -e "rosservice call /conveyor/control 'state:
  power: 20.0'" &
sleep 4

xterm -e "roslaunch sortation_system spawn_portal_frame.launch" &
sleep 4

xterm -e "roslaunch sortation_system spawn_camera_link.launch" &
sleep 4

# Start RVIZ with a preconfigured view
xterm -e "roslaunch sortation_system rviz.launch" &
sleep 4

# Launch object_spawner node
xterm -e "roslaunch sortation_system object_spawner.launch" &
sleep 6

# Launch ar_track_alvar to detect AR markers and localize them in space
xterm -e "roslaunch sortation_system ar_track.launch" &
sleep 6

# Spawn deflector robot
xterm -e "roslaunch deflector_robot spawn_robot.launch" &
sleep 6

# Execute the robot controllers:
xterm -e "roslaunch deflector_robot ctrl_manager.launch" &
sleep 4

# Kick off sortation_manager node
xterm -e "rosrun sortation_system sortation_manager" &
sleep 4

xterm -e "rosservice call /gazebo/unpause_physics '{}'"

