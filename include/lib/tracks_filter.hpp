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


#include <tf2_ros/transform_listener.h>

namespace tracks_filter
{

	class TracksFilter
	{

	public:
		TracksFilter();
		~TracksFilter();
		void run();

	private:

		ros::NodeHandle nh_priv_;
		ros::Subscriber track_array_sub_;
		ros::Publisher viz_pub_;
		visualization_msgs::Marker template_marker_, template_string_marker_;
		double timeout_secs_; //timeout in seconds.
		bool running_from_bag_;
		std::map<unsigned char, delphi_esr_msgs::EsrTrack> tracks_list_;

		void trackCB(const delphi_esr_msgs::EsrTrackConstPtr& msg);
		void updateTracksList(delphi_esr_msgs::EsrTrack track);
		void generateMakers();

	};

}



#endif /* INCLUDE_ESR_TRANSLATOR_HPP_ */
