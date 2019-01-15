/*
 * esr_translator.cpp
 *
 *  Created on: Nov 1, 2018
 *      Author: marco
 */


#include "../../include/lib/tracks_filter.hpp"

namespace tracks_filter
{

    TracksFilter::TracksFilter():nh_priv_("~"),
								 timeout_secs_(0.5),
								 running_from_bag_(false),
								 angle_limit_(20),
								 range_limit_(5)

	{
    	track_array_sub_ = nh_priv_.subscribe("/front_esr/as_tx/radar_tracks",100, &TracksFilter::trackCB, this);
    	viz_pub_ = nh_priv_.advertise<visualization_msgs::MarkerArray>("esr_tracks_viz",10);
    	filtered_tracks_pub_ = nh_priv_.advertise<geometry_msgs::PolygonStamped>("filtered_tracks",10);


		nh_priv_.getParam("range_limit", range_limit_);
		nh_priv_.getParam("angle_limit", angle_limit_);


		template_marker_.id = 0;
		template_marker_.type = visualization_msgs::Marker::CUBE;
		template_marker_.header.frame_id = "/front_esr";
		template_marker_.color.r = 0;
		template_marker_.color.g = 255;
		template_marker_.color.b = 0;
		template_marker_.color.a = 1.0;

		template_marker_.scale.x = 0.1;
		template_marker_.scale.y = 0.1;
		template_marker_.scale.z = 0.5;

		template_string_marker_.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
		template_string_marker_.header.frame_id = template_marker_.header.frame_id;
		template_string_marker_.id = -1;
		template_string_marker_.color.r = 255;
		template_string_marker_.color.g = 0;
		template_string_marker_.color.b = 0;
		template_string_marker_.color.a = 1.2;

	}

    TracksFilter::~TracksFilter()
	{

	}

	void TracksFilter::run()
	{
		ros::Rate rate(30);

		while(ros::ok())
		{
			ros::spinOnce();
			rate.sleep();
		}

	}

	void TracksFilter::trackCB(const radar_msgs::RadarTrackArrayConstPtr& msg)
	{
		radar_msgs::RadarTrackArray tracks = *msg;
		publishPolygons(tracks);

	}

	void TracksFilter::publishPolygons(radar_msgs::RadarTrackArray tracks)
	{

		visualization_msgs::MarkerArray viz_array_msg;
		visualization_msgs::Marker marker_msg = template_marker_;
		visualization_msgs::Marker text_marker_msg = template_string_marker_;
		float lat_speed, track_angle, track_range, track_width;
		float track_accel, track_speed;
		float range, angle;


		for(int i = 0; i < tracks.tracks.size(); i++)
		{
			float x = tracks.tracks[i].track_shape.points[0].x;
			float y = tracks.tracks[i].track_shape.points[0].y;
			range = sqrt(pow(x,2) + pow(y,2));
			angle = atan(y/x) * 180 / 3.14;
			if(range < 10)
			{

				marker_msg.id = tracks.tracks[i].track_id;
				marker_msg.pose.position.x = tracks.tracks[i].track_shape.points[0].x;
				marker_msg.pose.position.y = tracks.tracks[i].track_shape.points[0].y;
				marker_msg.pose.position.z = 0.05;

				marker_msg.header.stamp = ros::Time::now();
				text_marker_msg.header.stamp = marker_msg.header.stamp;

				viz_array_msg.markers.push_back(marker_msg);
				viz_array_msg.markers.push_back(text_marker_msg);
			}


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


		}
		viz_pub_.publish(viz_array_msg);

	}

	void TracksFilter::generateMakers()
	{

		visualization_msgs::MarkerArray viz_array_msg;
		visualization_msgs::Marker marker_msg = template_marker_;
		visualization_msgs::Marker text_marker_msg = template_string_marker_;
		float lat_speed, track_angle, track_range, track_width;
		float track_accel, track_speed;

		for(auto it = tracks_list_.begin(); it != tracks_list_.end();++it)
		{
			delphi_esr_msgs::EsrTrack track = it->second;
			lat_speed =  track.track_lat_rate;
			track_angle = track.track_angle;
			track_range = track.track_range;
			track_width = track.track_width;
			track_accel = track.track_range_accel;
			track_speed = track.track_range_rate;

			marker_msg.id = track.track_ID;
			marker_msg.pose.position.x = track_range * std::cos(track_angle);
			marker_msg.pose.position.y = track_range * std::sin(track_angle);
			marker_msg.pose.position.z = 0.05;


			std::string lat_speed_str = std::to_string(lat_speed);
			std::string speed_str = std::to_string(track_speed);
			std::string accel_str = std::to_string(track_accel);

			std::string viz_info_str = "lat_speed: " + lat_speed_str +
									   "\n" + "speed: " + speed_str +
									   "\n"+ "accel: " + accel_str+
									   "\n";

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
}

