/*
 * radar.hpp
 *
 *  Created on: Nov 6, 2018
 *      Author: marco
 */

#ifndef INCLUDE_RADAR_HPP_
#define INCLUDE_RADAR_HPP_

#include<ros/ros.h>
#include<map>
#include<string>

#include<visualization_msgs/Marker.h>
#include<visualization_msgs/MarkerArray.h>


class Radar
{

public:

	Radar();
	virtual ~Radar();

protected:

	visualization_msgs::Marker template_marker_, template_string_marker_;
	ros::NodeHandle nh_priv_;
	ros::Publisher viz_pub_;
	double timeout_secs_;
	bool running_from_bag_;

};

#endif /* INCLUDE_RADAR_HPP_ */
