/*
 * srr_translator.hpp
 *
 *  Created on: Nov 6, 2018
 *      Author: marco
 */

#include<lib/radar.hpp>
#include<delphi_srr_msgs/SrrTrack.h>

namespace srr_translator
{

	class SRRTranslator:Radar
	{
	public:
		SRRTranslator();
		~SRRTranslator();
	private:
		std::map<unsigned char, delphi_srr_msgs::SrrTrack> tracks_list_;
		void generateMakers();


	};

}

