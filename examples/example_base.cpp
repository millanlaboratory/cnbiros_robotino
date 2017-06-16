#include <ros/ros.h>
#include "cnbiros_robotino/Base.hpp"


int main (int argc, char** argv) {

	std::string address = "192.168.1.3";
	
	ros::init(argc, argv, "robotino_base");
	ros::NodeHandle node("~");
	ros::Rate r(10);

	cnbiros::robotino::Base robotino(&node);

	ROS_INFO("Try to connect to robotino base at: %s", address.c_str());
	robotino.Connect(address);
	
	while(node.ok()) {


		robotino.ProcessEvents();
		r.sleep();
		ros::spinOnce();
	}

	return 0;
}
