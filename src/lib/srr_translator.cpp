/*
 * srr_translator.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: marco
 */

#include<lib/srr_translator.hpp>


namespace srr_translator
{

	SRRTranslator::SRRTranslator()
	{

	}

	SRRTranslator::~SRRTranslator()
	{

	}

	void SRRTranslator::generateMakers()
	{
		visualization_msgs::MarkerArray viz_array_msg;
		visualization_msgs::Marker marker_msg = template_marker_;
		visualization_msgs::Marker text_marker_msg = template_string_marker_;
		float track_angle, track_range,track_speed, track_amplitude;

		for(auto it = tracks_list_.begin(); it != tracks_list_.end();++it)
		{
			delphi_srr_msgs::SrrTrack track = it->second;
			track_angle = track.CAN_TX_DETECT_ANGLE; //rad
			track_range = track.CAN_TX_DETECT_RANGE; //meters
			track_amplitude = track.CAN_TX_DETECT_AMPLITUDE; //dBsm
			track_speed = track.CAN_TX_DETECT_RANGE_RATE; //m/s
//
//			marker_msg.id = track.track_ID;
			marker_msg.pose.position.x = track_range * std::cos(track_angle);
			marker_msg.pose.position.y = track_range * std::sin(track_angle);
			marker_msg.pose.position.z = 0.05;
//
//
			std::string speed_str = std::to_string(track_speed);

//
			std::string viz_info_str = "lat_speed: " + lat_speed_str +
									   "\n" + "speed: " + speed_str +
									   "\n"+ "accel: " + accel_str+
									   "\n";
//
//			text_marker_msg.id = marker_msg.id + 1000;
//			text_marker_msg.text = viz_info_str;
//			text_marker_msg.scale.z = 0.07;
//			text_marker_msg.pose.position = marker_msg.pose.position;
//			text_marker_msg.pose.position.z+=0.06;
//
//			marker_msg.header.stamp = ros::Time::now();
//			text_marker_msg.header.stamp = marker_msg.header.stamp;
//
//			viz_array_msg.markers.push_back(marker_msg);
//			viz_array_msg.markers.push_back(text_marker_msg);
		}

	}

}


