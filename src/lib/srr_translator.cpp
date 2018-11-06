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
		viz_pub_ = nh_priv_.advertise<visualization_msgs::MarkerArray>("srr_tracks_viz",10);
	}

	SRRTranslator::~SRRTranslator()
	{

	}
	//TODO: Use the radars detection array message to draw the markers, and use that info for navi.
	void SRRTranslator::generateMakers()
	{
		visualization_msgs::MarkerArray viz_array_msg;
		visualization_msgs::Marker marker_msg = template_marker_;
		visualization_msgs::Marker text_marker_msg = template_string_marker_;
		float lat_speed, track_angle, track_range, track_width;
		float track_accel, track_speed;

		for(auto it = detections_list_.begin(); it != detections_list_.end();++it)
		{
			radar_msgs::RadarDetection detection = it->second;

			marker_msg.id = detection.detection_id;
			marker_msg.pose.position.x = detection.position.x;
			marker_msg.pose.position.y = detection.position.y;
			marker_msg.pose.position.z = 0.05;


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

		viz_pub_.publish(viz_array_msg);
	}

	void SRRTranslator::srrTrackCB(const delphi_srr_msgs::SrrTrackConstPtr &track_msg)
	{
		generateMakers();

	}

	void SRRTranslator::radarDetectionsCB(const radar_msgs::RadarDetectionArrayConstPtr &detections_msg)
	{


	}


}


