#include <ros/ros.h>
#include "cnbiros_robotino/Infrared.hpp"


int main (int argc, char** argv) {

	std::string address = "192.168.1.3";
	
	ros::init(argc, argv, "robotino_infrared");
	ros::NodeHandle node("~");
	ros::Rate r(10);

	cnbiros::robotino::Base robotino(address);
	robotino.EnableServices(&node);

	cnbiros::robotino::Infrared infrared(&robotino, &node);

	ROS_INFO("Try to connect to robotino base at: %s", address.c_str());
	robotino.Connect();
	
	while(node.ok()) {


		robotino.ProcessEvents();
		r.sleep();
		ros::spinOnce();
	}

	return 0;
}
