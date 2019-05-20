/*
Reads out the ID number from a marker detected by ar_track_alvar and prints it to the screen

Author: Roberto Zegers R.
Date: 20 May 2019

Note: this code assumes that there is maximum of one marker in the screen at the same time
*/

#include <ros/ros.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>

void id_callback(ar_track_alvar_msgs::AlvarMarkers msg) {
    if (!msg.markers.empty()) {
      int code_id = msg.markers[0].id;
      ROS_INFO("Ar marker id: %d", code_id);
    } // if
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "sortation_manager");
  ros::NodeHandle nh;
  ROS_INFO("Sortation Manager started!");
  ros::Subscriber sub = nh.subscribe("ar_pose_marker", 1, id_callback);
  ros::spin();
  return 0;
}
