/*
Reads out the ID number from a marker detected by ar_track_alvar,
next publishes a position command based on the detected marker (for a robot arm to move to that position)
then executes a position command for another joint based on a fixed period of time

Author: Roberto Zegers R.
Date: 02 June 2019

Note: this code assumes that there is maximum of one marker in the camera's field of view at the same time
*/

#include <ros/ros.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <std_msgs/Float64.h>

// global var
int code_id = -1; // use -1 to indicate that no marker ID has been identified yet
std_msgs::Float64 j1_pos_msg;
std_msgs::Float64 j2_pos_msg;
std_msgs::Float64 j3_pos_msg;
// declare a pointer to the NodeHandle as global variable
ros::NodeHandle *nh = NULL;

void prepareJoint1(ros::Publisher &j1_position_pub, ros::Publisher &j2_position_pub) {
      // publish values to move joints
      j1_position_pub.publish(j1_pos_msg);
      j2_position_pub.publish(j2_pos_msg);
}

void id_callback(ar_track_alvar_msgs::AlvarMarkers msg) {
    if (!msg.markers.empty()) {
      code_id = msg.markers[0].id;
      ROS_INFO("AR Marker Id: %d", code_id);
    } // if
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "sortation_manager");
  nh = new ros::NodeHandle(); // Initialization of NodeHandle
  ROS_INFO("Sortation Manager started!");
  ros::Subscriber sub = nh->subscribe("ar_pose_marker", 1, id_callback);
  ros::Publisher j1_position_pub = nh->advertise<std_msgs::Float64>("/deflector/joint1_position_controller/command", 1);
  ros::Publisher j2_position_pub = nh->advertise<std_msgs::Float64>("/deflector/joint2_position_controller/command", 1);
  ros::Publisher j3_position_pub = nh->advertise<std_msgs::Float64>("/deflector/joint3_position_controller/command", 1);
  ros::Rate loop_rate(50); // in Hz
  int num_loops = 200; // Will publish a setpoint for num_loops/loopRate
  j2_pos_msg.data = -0.7; // on start, set joint 2 to an elevated position
  
  while (ros::ok())
  {
    j2_position_pub.publish(j2_pos_msg); // raise joint 2
    if (code_id == -1) {
    ROS_INFO("Waiting for AR Marker to trigger callback");
    } else if (code_id >= 0 && code_id <= 5) {
    // Case container bin 1
    j1_pos_msg.data = 0.16;
    j3_pos_msg.data = 0.78;
    // Move joint 1 in front of target container bin 1
    ROS_INFO("Target position of joint 1: %.2f", j1_pos_msg.data);
    prepareJoint1(j1_position_pub, j2_position_pub);
    // Wait a fixed period of time, then trigger the sliding pusher plate
    ROS_INFO("Now waiting 8.5 seconds");
    ros::Duration(8.5).sleep(); // sleep for 8.5 seconds, wait this long before pushing
    /// Actuate pusher
    // extend pusher (joint 3)
    for (int j = 0; j < num_loops; j++) // Publish data for num_loops/loopRate seconds
    {
      // publish joint values
      j1_position_pub.publish(j1_pos_msg);
      j2_position_pub.publish(j2_pos_msg);
      j3_position_pub.publish(j3_pos_msg);
      loop_rate.sleep();
    }
    // retract pusher (joint 3)
    j3_pos_msg.data = 0.0;
    for (int k = 0; k < num_loops; k++) // Publish data for num_loops/loopRate seconds
    {
      // publish joint values
      j1_position_pub.publish(j1_pos_msg);
      j2_position_pub.publish(j2_pos_msg);
      j3_position_pub.publish(j3_pos_msg);
      loop_rate.sleep();
    }
    code_id = -1; // reset to -1 to indicate that no marker ID is being processed
    } else if (code_id > 5 && code_id <= 11) {
    // Case container bin 2
    j1_pos_msg.data = 0.96;
    j3_pos_msg.data = 0.78;
    // Move joint 1 in front of target container bin 2
    ROS_INFO("Target position of joint 1: %.2f", j1_pos_msg.data);
    prepareJoint1(j1_position_pub, j2_position_pub);
    // Wait a fixed period of time, then trigger the sliding pusher plate
    ROS_INFO("Now waiting 13 seconds");
    ros::Duration(13.0).sleep(); // sleep for 13 seconds, wait this long before pushing

    /// Actuate pusher
    // extend pusher (joint 3)
    for (int j = 0; j < num_loops; j++) // Publish data for num_loops/loopRate seconds
    {
      // publish joint values
      j1_position_pub.publish(j1_pos_msg);
      j2_position_pub.publish(j2_pos_msg);
      j3_position_pub.publish(j3_pos_msg);
      loop_rate.sleep();
    }
    // retract pusher (joint 3)
    j3_pos_msg.data = 0.0;
    for (int k = 0; k < num_loops; k++) // Publish data for num_loops/loopRate seconds
    {
      // publish joint values
      j1_position_pub.publish(j1_pos_msg);
      j2_position_pub.publish(j2_pos_msg);
      j3_position_pub.publish(j3_pos_msg);
      loop_rate.sleep();
    }
    code_id = -1; // reset to -1 to indicate that no marker ID is being processed
    } else if (code_id > 11 && code_id <= 17) {
    // Case container bin 3
    j1_pos_msg.data = 1.76;
    j3_pos_msg.data = 0.78;
    // Move joint 1 in front of target container bin 3
    ROS_INFO("Target position of joint 1: %.2f", j1_pos_msg.data);
    prepareJoint1(j1_position_pub, j2_position_pub);
    // Wait a fixed period of time, then trigger the sliding pusher plate
    ROS_INFO("Now waiting 17 seconds");
    ros::Duration(17.0).sleep(); // sleep for 17 seconds, wait this long before pushing
    // Actuate pusher
    // extend pusher (joint 3)
    for (int j = 0; j < num_loops; j++) // Publish data for num_loops/loopRate seconds
    {
      // publish joint values
      j1_position_pub.publish(j1_pos_msg);
      j2_position_pub.publish(j2_pos_msg);
      j3_position_pub.publish(j3_pos_msg);
      loop_rate.sleep();
    }
    // retract pusher (joint 3)
    j3_pos_msg.data = 0.0;
    for (int k = 0; k < num_loops; k++) // Publish data for num_loops/loopRate seconds
    {
      // publish joint values
      j1_position_pub.publish(j1_pos_msg);
      j2_position_pub.publish(j2_pos_msg);
      j3_position_pub.publish(j3_pos_msg);
      loop_rate.sleep();
    }
    code_id = -1; // reset to -1 to indicate that no marker ID is being processed
    }
    else {
    j1_pos_msg.data = 0.0;
    j2_pos_msg.data = 0.0;
    j3_pos_msg.data = 0.0;
    ROS_INFO("Target position of joint 1: %.2f", j1_pos_msg.data);
    } // end of if .. else
    loop_rate.sleep();
    ros::spinOnce();
  }
  return 0;
}
