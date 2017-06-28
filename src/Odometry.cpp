#ifndef CNBIROS_ROBOTINO_ODOMETRY_CPP
#define CNBIROS_ROBOTINO_ODOMETRY_CPP

#include "cnbiros_robotino/Odometry.hpp"

namespace cnbiros {
	namespace robotino {

Odometry::Odometry(cnbiros::robotino::Base* base) {
	this->robotinobase_ = base;
	this->setComId(base->GetId());
	this->rospub_ = base->GetNode()->advertise<nav_msgs::Odometry>
								("odom", CNBIROS_CORE_BUFFER_MESSAGES);


	// Add odometry service
}

Odometry::~Odometry(void) {}

void Odometry::readingsEvent(double x, double y, double omega, 
				             float vx, float vy, float vomega, 
						   	 unsigned int sequence) {
	float z  = 0.0f;
	float vz = 0.0f;
	nav_msgs::Odometry odom;

	odom.header.stamp    = ros::Time::now();
	odom.header.seq      = sequence;

	odom.pose.pose.position.x  = x;
	odom.pose.pose.position.y  = y;
	odom.pose.pose.position.z  = z;
	odom.pose.pose.orientation = tf::createQuaternionMsgFromYaw(omega);

	odom.twist.twist.linear.x  = vx;
	odom.twist.twist.linear.y  = vy;
	odom.twist.twist.linear.z  = vz;
	odom.twist.twist.angular.z = vomega;

	this->rospub_.publish(odom);
}

	}
}

#endif

