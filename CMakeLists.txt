cmake_minimum_required(VERSION 2.8.3)
project(delphi_esr_translator)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  			 roscpp
  			 rospy
  			 std_msgs
  			 tf2
  			 tf2_ros
  			 delphi_esr_msgs
  			 delphi_srr_msgs
  			 geometry_msgs
  			 nav_msgs
  			 radar_msgs 
  			 visualization_msgs)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)


################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

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
               delphi_srr_msgs
               geometry_msgs
               nav_msgs
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
add_library(esr_translator
   			src/lib/esr_translator.cpp)

add_library(srr_translator
			src/lib/srr_translator.cpp)
		
		
## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(${PROJECT_NAME}_node
		       src/delphi_esr_node.cpp)

target_link_libraries(${PROJECT_NAME}_node
   					  esr_translator)

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node
    				  ${catkin_LIBRARIES})
