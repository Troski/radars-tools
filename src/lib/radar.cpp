/*
 * radar.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: marco
 */

#include<lib/radar.hpp>



Radar::Radar():timeout_secs_(0.01),
			   running_from_bag_(false),
			   nh_priv_("~")
{
	template_marker_.id = 0;
	template_marker_.type = visualization_msgs::Marker::CUBE;
	template_marker_.header.frame_id = ""; //define your own
	template_marker_.color.r = 0;
	template_marker_.color.g = 255;
	template_marker_.color.b = 0;
	template_marker_.color.a = 1.0;

	template_marker_.scale.x = 0.1;
	template_marker_.scale.y = 0.1;
	template_marker_.scale.z = 0.1;

	template_string_marker_.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
	template_string_marker_.header.frame_id = template_marker_.header.frame_id;
	template_string_marker_.id = -1;
	template_string_marker_.color.r = 255;
	template_string_marker_.color.g = 255;
	template_string_marker_.color.b = 0;
	template_string_marker_.color.a = 1.2;
}


Radar::~Radar()
{


}

void Radar::generateMakers()
{


}

