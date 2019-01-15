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
#include<radar_msgs/RadarDetection.h>
#include<radar_msgs/RadarDetectionArray.h>
#include<visualization_msgs/Marker.h>
#include<visualization_msgs/MarkerArray.h>
#include<geometry_msgs/PolygonStamped.h>

#include<tf2_ros/transform_listener.h>
#include<math.h>


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
		ros::Publisher viz_pub_, filtered_tracks_pub_;
		visualization_msgs::Marker template_marker_, template_string_marker_;


		double timeout_secs_; //timeout in seconds.
		double range_limit_,angle_limit_;

		bool running_from_bag_;
		std::map<unsigned char, delphi_esr_msgs::EsrTrack> tracks_list_;

		void trackCB(const radar_msgs::RadarTrackArrayConstPtr& msg);
		void generateMakers();
		void publishPolygons(radar_msgs::RadarTrackArray tracks);
	};

}



#endif /* INCLUDE_ESR_TRANSLATOR_HPP_ */
