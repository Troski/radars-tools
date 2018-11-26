/*
 * srr_translator.hpp
 *
 *  Created on: Nov 6, 2018
 *      Author: marco
 */

#include<ros/ros.h>
#include<delphi_srr_msgs/SrrTrack.h>
#include<visualization_msgs/Marker.h>
#include<visualization_msgs/MarkerArray.h>

#include<radar_msgs/RadarDetectionArray.h>
#include<radar_msgs/RadarDetection.h>


namespace srr_translator
{

	class SRRTranslator
	{
	public:
		SRRTranslator();
		~SRRTranslator();
	private:
		ros::Subscriber srr_track_sub_;
		ros::Subscriber radar_detection_array_sub_;
		radar_msgs::RadarDetectionArray detections_list_;


		void generateMakers();
		void srrTrackCB(const delphi_srr_msgs::SrrTrackConstPtr &track_msg);
		void radarDetectionsCB(const radar_msgs::RadarDetectionArrayConstPtr &detections_msg);
	};

}

