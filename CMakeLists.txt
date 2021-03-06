set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
cmake_minimum_required(VERSION 2.8.3)
project(cnbiros_robotino)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs nav_msgs message_generation
			 cnbiros_core)

SET(CMAKE_BUILD_TYPE RelWithDebInfo)

# Robotino libraries
set(CMAKE_MODULE_PATH /usr/local/robotino/api2/cmake)
find_package(RobotinoAPI2)

include_directories(${catkin_INCLUDE_DIRS} 
		    include)

add_service_files(
  FILES
  CommService.srv
  GetPowerSrv.srv
  GetOdometrySrv.srv
  SetOdometrySrv.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
  nav_msgs
)

catkin_package(
  INCLUDE_DIRS 
	include
  LIBRARIES 
	${PROJECT_NAME}
  CATKIN_DEPENDS
  	roscpp
)

add_library(cnbiros_robotino
			src/Communication.cpp
			src/Power.cpp
			src/Base.cpp
			src/Infrared.cpp
			src/Odometry.cpp
			src/Motors.cpp)
target_link_libraries(cnbiros_robotino 
					  ${catkin_LIBRARIES}
					  ${REC_ROBOTINO_API2_LIBRARY})

add_executable(ros_robotino src/ros_robotino.cpp)
target_link_libraries(ros_robotino cnbiros_robotino)

add_executable(example_base examples/example_base.cpp)
target_link_libraries(example_base cnbiros_robotino)

add_executable(example_infrared examples/example_infrared.cpp)
target_link_libraries(example_infrared cnbiros_robotino)
