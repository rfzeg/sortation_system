/*
Reads out the ID number from a marker detected by ar_track_alvar and prints it to the screen

Author: Roberto Zegers R.
Date: 20 May 2019

Note: this code assumes that there is maximum of one marker in the screen at the same time
*/

#include <ros/ros.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <std_msgs/Float64.h>

// global var
int code_id = -1; // use -1 to indicate that no marker ID has been identified yet

void id_callback(ar_track_alvar_msgs::AlvarMarkers msg) {
    if (!msg.markers.empty()) {
      code_id = msg.markers[0].id;
      ROS_INFO("Ar marker id: %d", code_id);
    } // if
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "sortation_manager");
  ros::NodeHandle nh;
  ROS_INFO("Sortation Manager started!");
  ros::Subscriber sub = nh.subscribe("ar_pose_marker", 1, id_callback);
  ros::Publisher position_pub = nh.advertise<std_msgs::Float64>("/deflector/joint1_position_controller/command", 1); // set topic name, amount of messages to buffer
  ros::Rate loop_rate(1); // in Hz

  while (ros::ok())
  {
    std_msgs::Float64 pos_msg;
    // exemplary control logic based on value of detected AR marker
    if (code_id == -1) {
    ROS_INFO("No new target joint position sent");
    } else if (code_id > 10) {
    pos_msg.data = 0.5;
    ROS_INFO("Target position of joint 1: %.2f", pos_msg.data);
    } else if (code_id < 10) {
    pos_msg.data = 1.5;
    ROS_INFO("Target position of joint 1: %.2f", pos_msg.data);
    } else /* code_id == 10 */ {
    pos_msg.data = 2.0;
    ROS_INFO("Target position of joint 1: %.2f", pos_msg.data);
    }
    position_pub.publish(pos_msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
