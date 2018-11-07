/*
 * esr_translator.cpp
 *
 *  Created on: Nov 1, 2018
 *      Author: marco
 */


#include<lib/esr_translator.hpp>

namespace esr_translator
{

	ESRTranslator::ESRTranslator():nh_priv_("~"),
								   timeout_secs_(0.5),
								   running_from_bag_(false)
	{
		esr_trackarray_sub_ = nh_priv_.subscribe("/parsed_tx/radartrack",100, &ESRTranslator::ESRTrackCB, this);
		odom_sub_ = nh_priv_.subscribe("/my_odom",100,&ESRTranslator::OdomCB,this);
		viz_pub_ = nh_priv_.advertise<visualization_msgs::MarkerArray>("esr_tracks_viz",10);
		twist_pub_ = nh_priv_.advertise<geometry_msgs::TwistStamped>("as_rx/vehicle_motion",10);

		nh_priv_.getParam("running_from_bag",running_from_bag_);

		template_marker_.id = 0;
		template_marker_.type = visualization_msgs::Marker::CUBE;
		template_marker_.header.frame_id = "/esr_1";
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

	ESRTranslator::~ESRTranslator()
	{

	}

	void ESRTranslator::run()
	{
		ros::Rate rate(30);

		while(ros::ok())
		{
			ros::spinOnce();
			rate.sleep();
		}

	}

	void ESRTranslator::ESRTrackCB(const delphi_esr_msgs::EsrTrackConstPtr& msg)
	{
		delphi_esr_msgs::EsrTrack track = *msg;

		if(running_from_bag_)
			track.header.stamp = ros::Time::now(); //update timestamp, for tracks_list_ upkeep.

		updateTracksList(track);
		generateMakers();
	}

	void ESRTranslator::generateMakers()
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

	void ESRTranslator::updateTracksList(delphi_esr_msgs::EsrTrack track)
	{
		unsigned char track_id = track.track_ID;
		auto track_item = tracks_list_.find(track_id); //search track in tracks_list_ by id.

		if(track_item == tracks_list_.end())
		{
			std::pair<unsigned char,delphi_esr_msgs::EsrTrack> new_entry;
			new_entry.first = track_id;
			new_entry.second = track;
			tracks_list_.insert(new_entry); //if track not in list add it to the list.
		}
		else
		{
			 track_item->second = track; //edit track if found on list.
		}

		//Going through list, and erase tracks that have been in the list longer than the timeout.
		for(auto it = tracks_list_.begin(); it != tracks_list_.end();)
		{
			unsigned char key_id = it->first;
			delphi_esr_msgs::EsrTrack track = it->second;
			double time_delta = (ros::Time::now() - track.header.stamp).toSec();
			if(time_delta > timeout_secs_)
			{
				it = tracks_list_.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void ESRTranslator::OdomCB(const nav_msgs::OdometryConstPtr& msg)
	{
		geometry_msgs::TwistStamped twist;
		twist.twist = msg->twist.twist;
		twist.header = msg->header;


	}

}

