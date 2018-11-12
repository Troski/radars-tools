/*
 * delphi_esr.hpp
 *
 *  Created on: Nov 1, 2018
 *      Author: marco
 */

#ifndef INCLUDE_ESR_TRANSLATOR_HPP_
#define INCLUDE_ESR_TRANSLATOR_HPP_

#include<ros/ros.h>
#include<map>
#include<string>
#include <thread>
#include <mutex>

#include<delphi_esr_msgs/EsrTrack.h>
#include<delphi_esr_msgs/EsrTrackMotionPower.h>
#include<radar_msgs/RadarStatus.h>
#include<radar_msgs/RadarTrackArray.h>

#include<visualization_msgs/Marker.h>
#include<visualization_msgs/MarkerArray.h>

#include<geometry_msgs/TwistStamped.h>
#include<geometry_msgs/PolygonStamped.h>
#include<geometry_msgs/Pose.h>

#include<nav_msgs/Odometry.h>

#include <tf2_ros/transform_listener.h>
#include <tf2_ros/transform_broadcaster.h>

namespace esr_translator
{

	class ESRTranslator
	{

	public:
		ESRTranslator();
		~ESRTranslator();
		void run();

	private:

		ros::NodeHandle nh_priv_;
		ros::Subscriber esr_trackarray_sub_, odom_sub_, radar_track_array_sub_;
		ros::Publisher viz_pub_, twist_pub_, poly_pub_;
		visualization_msgs::Marker template_marker_, template_string_marker_;
		nav_msgs::Odometry current_odom_;
        tf2_ros::Buffer tf2_buffer_;
		tf2_ros::TransformListener tf2_listener_;
		tf2_ros::TransformBroadcaster tf2_broadcaster_;

		std::mutex odom_mutex_;

		double timeout_secs_; //timeout in seconds.
		bool running_from_bag_;
		bool publish_tf_;
		std::string frame_id_str_;
		std::map<unsigned char, delphi_esr_msgs::EsrTrack> tracks_list_;

		void ESRTrackCB(const delphi_esr_msgs::EsrTrackConstPtr& msg);
		void updateTracksList(delphi_esr_msgs::EsrTrack track);
		//AS Delphi Driver Subscribes to geometry_msg::Twist
		void OdomTwistConverterCB(const nav_msgs::OdometryConstPtr& msg);
		void radarTracks(const radar_msgs::RadarTrackArrayConstPtr& msg);
		void generateMakers();

	};

}



#endif /* INCLUDE_ESR_TRANSLATOR_HPP_ */
