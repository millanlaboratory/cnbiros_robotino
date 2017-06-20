#ifndef CNBIROS_ROBOTINO_INFRARED_CPP
#define CNBIROS_ROBOTINO_INFRARED_CPP

#include "cnbiros_robotino/Infrared.hpp"

namespace cnbiros {
	namespace robotino {

Infrared::Infrared(cnbiros::robotino::Base* base) {

	this->robotinobase_ = base;
	this->setComId(base->GetId());
	this->rospub_ = base->GetNode()->advertise<sensor_msgs::PointCloud2>
								(base->GetNode()->getNamespace()+"/infrared", 
								 CNBIROS_CORE_BUFFER_MESSAGES);
}

Infrared::~Infrared(void) {}

void Infrared::distancesChangedEvent(const float* ranges, unsigned int size) {

	float x, y, z;
	float angle_inc, range_min, range_max, height, base_radius;
	unsigned int inrange = 0;

	PointCloud::Ptr msg(new PointCloud);
	msg->header.frame_id = "infrared_link";
	msg->height =  1;
	msg->width =  size;

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

		x = (ranges[i] + base_radius) * cos(angle_inc * i);
		y = (ranges[i] + base_radius) * sin(angle_inc * i);
		z = height;
		
		msg->points.push_back(pcl::PointXYZ(x, y, z));
		inrange++;
	}

	msg->points.resize(inrange);
	msg->width = inrange;

	this->rospub_.publish(msg);
}


	}
}

#endif
