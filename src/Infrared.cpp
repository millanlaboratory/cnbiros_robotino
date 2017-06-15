#ifndef CNBIROS_ROBOTINO_INFRARED_CPP
#define CNBIROS_ROBOTINO_INFRARED_CPP

#include "cnbiros_robotino/Infrared.hpp"

namespace cnbiros {
	namespace robotino {

Infrared::Infrared(cnbiros::robotino::Base* base, ros::NodeHandle* node) : 
				   cnbiros::core::NodeInterface (node, "infrared") {

	this->robotinobase_ = base;
	this->setComId(this->robotinobase_->GetId());
	this->rospub_ = this->GetNode()->advertise<sensor_msgs::PointCloud>
								("/robotino_infrared", CNBIROS_CORE_BUFFER_MESSAGES);
}

Infrared::~Infrared(void) {}

void Infrared::distancesChangedEvent(const float* ranges, unsigned int size) {

	float x, y, z;
	float angle_inc, range_min, range_max, height, base_radius;
	geometry_msgs::Point32 point;
	sensor_msgs::ChannelFloat32 channel;
	sensor_msgs::PointCloud data;

	angle_inc   = CNBIROS_ROBOTINO_INFRARED_ANGLE_INC;
	range_max   = CNBIROS_ROBOTINO_INFRARED_RANGE_MAX;
	height 		= CNBIROS_ROBOTINO_INFRARED_HEIGHT;
	base_radius = CNBIROS_ROBOTINO_BASE_RADIUS;

	// Build the PointCloud msg
	data.header.stamp 		= ros::Time::now();
	data.header.frame_id 	= "base_link";
	data.points.clear();
	data.channels.clear();

	channel.name = "strength";
	channel.values.resize(size);

	// Fill the point cloud by iterating the input vector of distance. Checking
	// if the distance are inside the min-max range of the infrared sensors.
	// Otherwise set the value to 0 (not done by the robotino::api2)
	for(auto i = 0; i < size; ++i) {
		point.x = (ranges[i] + base_radius) * cos(angle_inc * i);
		point.y = (ranges[i] + base_radius) * sin(angle_inc * i);
		point.z = height;
		
		channel.values[i] = 0.0f;
		if(ranges[i] > 0.0f && ranges[i] < range_max) {
			channel.values[i] = 1.0f;
		} 

		data.points.push_back(point);
	}
	data.channels.push_back(channel);

	this->rospub_.publish(data);
}


	}
}

#endif
