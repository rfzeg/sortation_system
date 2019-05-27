#!/usr/bin/env python

import os

# Nested dictionary that contains box dimentions with same keys 
boxes = {'Box1': {'mass': '0.57', 'lenght': '0.15', 'width': '0.1', 'height': '0.09'},
         'Box2': {'mass': '1.69', 'lenght': '0.2', 'width': '0.15', 'height': '0.15'}, 
         'Box3': {'mass': '3.58', 'lenght': '0.3', 'width': '0.2', 'height': '0.15'}, 
         'Box4': {'mass': '9.105', 'lenght': '0.4', 'width': '0.3', 'height': '0.18'}}

for box_id, box_info in boxes.items():
    M = boxes[box_id]['mass'] # mass in Kg
    L = boxes[box_id]['lenght'] # lenght in meters (min 0.1)
    W = boxes[box_id]['width'] # width in meters (min 0.1)
    H = boxes[box_id]['height'] # height in meters

    #for key in box_info:
    #    print(key + ':', box_info[key])


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
