# DelphiESR
ROS package that Abstract Data from AutonomousStuff delphi_esr_msgs. 
This node listens to `/parsed_tx/radartrack` with **delphi_esr_msgs/ESR_Track.msg**, updates a list of tracks, 
and adds *lat_speed*, *accel*, and *speed* to the visualizations on Rviz. 

This package runs aling AutonomouStuff delphi_esr package and is inteded to be complementary to that package. 


Documentation from AutonomouStuff: [https://autonomoustuff.atlassian.net/wiki/spaces/RW/pages/17509820/Delphi+ESR](https://autonomoustuff.atlassian.net/wiki/spaces/RW/pages/17509820/Delphi+ESR)