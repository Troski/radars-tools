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
		radar_detection_array_sub_ = nh_priv_.subscribe("/as_tx/detections",100,&SRRTranslator::radarDetectionsCB, this );
	}

	SRRTranslator::~SRRTranslator()
	{

	}

	void SRRTranslator::generateMakers()
	{
		visualization_msgs::MarkerArray viz_array_msg;
		visualization_msgs::Marker marker_msg = template_marker_;
		visualization_msgs::Marker text_marker_msg = template_string_marker_;
		float lat_speed, track_angle, track_range, track_width;
		float track_accel, track_speed;

		//for(auto it = detections_list_.begin(); it != detections_list_.end();++it)
		for(int i = 0; i < detections_list_.detections.size(); i++)
		{
			marker_msg.id = detections_list_.detections[i].detection_id;
			marker_msg.pose.position.x = detections_list_.detections[i].position.x;
			marker_msg.pose.position.y = detections_list_.detections[i].position.y;
			marker_msg.pose.position.z = 0.05;

			track_speed = detections_list_.detections[i].velocity.x;
			lat_speed = detections_list_.detections[i].velocity.y;

			std::string lat_speed_str = std::to_string(lat_speed);
			std::string speed_str = std::to_string(track_speed);

			std::string viz_info_str = "lat_speed: " + lat_speed_str + "\n"
									   + "speed: " + speed_str + "\n";

			text_marker_msg.id = marker_msg.id + 1000;
			text_marker_msg.text = viz_info_str;
			text_marker_msg.scale.z = 0.07;
			text_marker_msg.pose.position = marker_msg.pose.position;
			text_marker_msg.pose.position.z+=0.06;

			marker_msg.header.stamp = ros::Time::now();
			text_marker_msg.header.stamp = marker_msg.header.stamp;

			viz_array_msg.markers.push_back(marker_msg);
			viz_array_msg.markers.push_back(text_marker_msg);
		}

		viz_pub_.publish(viz_array_msg);
	}

	void SRRTranslator::srrTrackCB(const delphi_srr_msgs::SrrTrackConstPtr &track_msg)
	{
		double speed = track_msg->CAN_TX_DETECT_RANGE_RATE;
		double range = track_msg->CAN_TX_DETECT_RANGE;
		double angle = track_msg->CAN_TX_DETECT_ANGLE;
		double amplitude = track_msg->CAN_TX_DETECT_AMPLITUDE;
		bool detect_stat = track_msg->CAN_TX_DETECT_STATUS;

	}

	void SRRTranslator::radarDetectionsCB(const radar_msgs::RadarDetectionArrayConstPtr &detections_msg)
	{
		detections_list_ = *detections_msg;
		ROS_INFO_STREAM("Detections: "<<detections_list_.detections.size());
		generateMakers();
	}


}


