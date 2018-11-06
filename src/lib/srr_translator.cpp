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
			track_angle = track.CAN_TX_DETECT_ANGLE;
//			track_range = track.track_range;
//			track_width = track.track_width;
//			track_accel = track.track_range_accel;
//			track_speed = track.track_range_rate;
//
//			marker_msg.id = track.track_ID;
//			marker_msg.pose.position.x = track_range * std::cos(track_angle);
//			marker_msg.pose.position.y = track_range * std::sin(track_angle);
//			marker_msg.pose.position.z = 0.05;
//
//
//			std::string lat_speed_str = std::to_string(lat_speed);
//			std::string speed_str = std::to_string(track_speed);
//			std::string accel_str = std::to_string(track_accel);
//
//			std::string viz_info_str = "lat_speed: " + lat_speed_str +
//									   "\n" + "speed: " + speed_str +
//									   "\n"+ "accel: " + accel_str+
//									   "\n";
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


