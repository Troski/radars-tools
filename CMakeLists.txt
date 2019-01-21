cmake_minimum_required(VERSION 2.8.3)
project(radars-tools)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  			 roscpp
  			 rospy
  			 std_msgs
  			 geometry_msgs
  			 tf2
  			 tf2_ros
  			 delphi_esr_msgs
  			 radar_msgs 
  			 visualization_msgs)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(INCLUDE_DIRS include
			   #LIBRARIES delphi_esr
  			   CATKIN_DEPENDS
   			   roscpp
   			   rospy
   			   tf2
  			   tf2_ros
               std_msgs
               delphi_esr_msgs
               geometry_msgs
               radar_msgs
               visualization_msgs
			   #DEPENDS system_lib
			   )

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include
  					${catkin_INCLUDE_DIRS})

## Declare a C++ library
add_library(TRACKS_FILTER
   			src/lib/tracks_filter.cpp)


## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(tracks_filter_node src/tracks_filter_node.cpp)

target_link_libraries(tracks_filter_node
   					  TRACKS_FILTER)

## Specify libraries to link a library or executable target against
target_link_libraries(tracks_filter_node
    				  ${catkin_LIBRARIES})
