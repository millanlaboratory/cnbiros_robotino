#include <ros/ros.h>
#include "cnbiros_robotino/Infrared.hpp"
#include "cnbiros_robotino/Power.hpp"
#include "cnbiros_robotino/Odometry.hpp"
#include "cnbiros_robotino/Motors.hpp"


int main (int argc, char** argv) {

	std::string address;
	
	ros::init(argc, argv, "ros_robotino");
	ros::NodeHandle node("~");

	cnbiros::robotino::Base robotino(&node);
	robotino.SetRate(20);

	cnbiros::robotino::Infrared infrared(&robotino);
	cnbiros::robotino::Power 	power(&robotino);
	cnbiros::robotino::Odometry odometry(&robotino);
	cnbiros::robotino::Motors	motors(&robotino);

	node.getParam("/ros_robotino/address", address);

	ROS_INFO("Try to connect to robotino at: %s", address.c_str());
	robotino.Connect(address);
	
	robotino.Start();

	return 0;
}
