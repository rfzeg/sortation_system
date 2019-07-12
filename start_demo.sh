#!/bin/bash

echo ""
echo "ROS Sortation System Project Demo"
echo ""
# The -e option to xterm is useful for running a single command before exiting

# Fire up Gazebo world with conveyor belt model & plugin
xterm -e "roslaunch sortation_system conveyor.launch" &
sleep 8

# Prompt for a key press to continue after Gazebo has loaded
read -n 1 -r -s -p "Press any key to continue once Gazebo has loaded or Ctrl+C to abort..."
echo ""

# Activate the conveyor belt:
xterm -e "rosservice call /conveyor/control 'state:
  power: 20.0'" &
sleep 4

# Spawn Workcell
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

# Prompt for a key press to continue..
echo "Press any key to return to the shell prompt or"
read -n 1 -r -s -p "Ctrl+C to close all X-Term processes..."
echo ""
