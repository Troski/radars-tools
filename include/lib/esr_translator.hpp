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


#include<delphi_esr_msgs/EsrTrack.h>
#include<delphi_esr_msgs/EsrTrackMotionPower.h>
#include<radar_msgs/RadarStatus.h>
#include<radar_msgs/RadarTrackArray.h>

#include<visualization_msgs/Marker.h>
#include<visualization_msgs/MarkerArray.h>
#include<geometry_msgs/TwistStamped.h>
#include<nav_msgs/Odometry.h>

#include <tf2_ros/transform_listener.h>

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
		ros::Subscriber esr_trackarray_sub_, odom_sub_;
		ros::Publisher viz_pub_, twist_pub_;
		visualization_msgs::Marker template_marker_, template_string_marker_;
		double timeout_secs_; //timeout in seconds.
		bool running_from_bag_;
		std::map<unsigned char, delphi_esr_msgs::EsrTrack> tracks_list_;

		void ESRTrackCB(const delphi_esr_msgs::EsrTrackConstPtr& msg);
		void updateTracksList(delphi_esr_msgs::EsrTrack track);
		void OdomCB(const nav_msgs::OdometryConstPtr& msg);
		void generateMakers();

	};

}



#endif /* INCLUDE_ESR_TRANSLATOR_HPP_ */
