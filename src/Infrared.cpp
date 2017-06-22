#ifndef CNBIROS_ROBOTINO_INFRARED_CPP
#define CNBIROS_ROBOTINO_INFRARED_CPP

#include "cnbiros_robotino/Infrared.hpp"

namespace cnbiros {
	namespace robotino {

Infrared::Infrared(cnbiros::robotino::Base* base) {

	this->robotinobase_ = base;
	this->setComId(base->GetId());
	this->rospub_ = base->GetNode()->advertise<sensor_msgs::PointCloud>
								(base->GetNode()->getNamespace()+"/infrared", 
								 CNBIROS_CORE_BUFFER_MESSAGES);
}

Infrared::~Infrared(void) {}

void Infrared::distancesChangedEvent(const float* ranges, unsigned int size) {

	float angle_inc, range_min, range_max, height, base_radius;
	unsigned int inrange = 0;

	geometry_msgs::Point32 point;
	sensor_msgs::PointCloud msg;

	msg.header.stamp = ros::Time::now();
	msg.header.frame_id = "infrared_link";
	msg.points.clear();

	angle_inc   = CNBIROS_ROBOTINO_INFRARED_ANGLE_INC;
	range_max   = CNBIROS_ROBOTINO_INFRARED_RANGE_MAX;
	height 		= CNBIROS_ROBOTINO_INFRARED_HEIGHT;
	base_radius = CNBIROS_ROBOTINO_BASE_RADIUS;

	// Fill the point cloud by iterating the input vector of distance. Checking
	// if the distance are inside the min-max range of the infrared sensors.
	// Otherwise set the value to 0 (not done by the robotino::api2)
	for(auto i = 0; i < size; ++i) {
		
		if(ranges[i] > range_max) 
			continue;

		point.x = (ranges[i] + base_radius) * cos(angle_inc * i);
		point.y = (ranges[i] + base_radius) * sin(angle_inc * i);
		point.z = height;
		
		msg.points.push_back(point);
		inrange++;
	}

	this->rospub_.publish(msg);
}


	}
}

#endif
