/*
 * srr_node.cpp
 *
 *  Created on: Nov 26, 2018
 *      Author: marco
 */



#include<ros/ros.h>
#include<lib/srr_translator.hpp>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "delphi_srr");
    srr_translator::SRRTranslator translator;
    //translator.run();
    return 0;
}
