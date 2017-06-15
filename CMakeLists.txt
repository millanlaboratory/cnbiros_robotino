set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
cmake_minimum_required(VERSION 2.8.3)
project(cnbiros_robotino)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation
			 cnbiros_core)

SET(CMAKE_BUILD_TYPE RelWithDebInfo)

include_directories(${catkin_INCLUDE_DIRS} 
		    include)

catkin_package(
  INCLUDE_DIRS 
	include
  LIBRARIES 
	${PROJECT_NAME}
  CATKIN_DEPENDS
  	roscpp
)

add_library(cnbiros_robotino
			Communication.cpp)
target_link_libraries(cnbiros_robotino ${catkin_LIBRARIES})
