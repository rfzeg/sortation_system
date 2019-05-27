#!/usr/bin/env python

import os

M = "0.8" # mass in Kg
L = "0.15" # lenght in meters (min 0.1)
W = "0.1" # width in meters (min 0.1)
H = "0.09" # height in meters

# Place the AR Tag with a margin with respect to the border of the box if the box is big enough
margin = "0"
if (float(L)>= 0.12 and float(W)>= 0.12):
    margin = "0.02"

# Generate fixed size boxes with different AR Tag numbers
try:
    for ar_tag in range(18):
        output_file = "box_" + str(int(float(L) * 1000)) + "x" + str(int(float(W) * 1000)) + "x" + str(int(float(H) * 1000)) + "_" + M + "kg_T" + str(ar_tag) + ".urdf" # in filenme use mm instead of meters
        bashCommand = "rosrun xacro xacro --inorder mass:="+ M +" lenght:="+ L +" width:="+ W +" height:="+ H +" ar_tag:="+ str(ar_tag) +" tag_margin:="+ margin +" carboard_box_generator.urdf.xacro > " + output_file
        os.system(bashCommand)
        print bashCommand
    print "Success!"

except:
  print"An exception occurred!"
