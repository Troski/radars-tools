/*
 * delphi_esr_node.cpp
 *
 *  Created on: Nov 1, 2018
 *      Author: marco
 */



#include<ros/ros.h>
#include<lib/esr_translator.hpp>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "delphi_esr");
    esr_translator::ESRTranslator translator;
    translator.run();
    return 0;
}

