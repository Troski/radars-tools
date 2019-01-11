/*
 * delphi_esr_node.cpp
 *
 *  Created on: Nov 1, 2018
 *      Author: marco
 */



#include<ros/ros.h>

#include "../include/lib/tracks_filter.hpp"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "delphi_esr");
    tracks_filter::TracksFilter translator;
    translator.run();
    return 0;
}

