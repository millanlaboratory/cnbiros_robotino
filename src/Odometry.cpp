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
	this->rossrv_get_odometry_ = base->GetNode()->advertiseService(
					  	     ros::this_node::getName() + "/get_odometry", &Odometry::on_get_odometry_, this);
	
	this->rossrv_set_odometry_ = base->GetNode()->advertiseService(
					  	     ros::this_node::getName() + "/set_odometry", &Odometry::on_set_odometry_, this);
}

Odometry::~Odometry(void) {}

bool Odometry::on_get_odometry_(cnbiros_robotino::GetOdometrySrv::Request &req,
							    cnbiros_robotino::GetOdometrySrv::Response &res) {

	double x, y, phi;
	unsigned int sequence;

	this->readings(&x, &y, &phi, &sequence);
	
	res.odometry.header.stamp    = ros::Time::now();
	res.odometry.header.seq      = sequence;
	res.odometry.header.frame_id = CNBIROS_ROBOTINO_ODOMETRY_LINK;
	res.odometry.child_frame_id  = CNBIROS_ROBOTINO_BASE_LINK;
	
	res.odometry.pose.pose.position.x  = x;
	res.odometry.pose.pose.position.y  = y;
	res.odometry.pose.pose.position.z  = 0.0f;
	res.odometry.pose.pose.orientation = tf::createQuaternionMsgFromYaw(phi);

	res.odometry.twist.twist.linear.x  = 0.0f;
	res.odometry.twist.twist.linear.y  = 0.0f;
	res.odometry.twist.twist.linear.z  = 0.0f;
	res.odometry.twist.twist.angular.z = 0.0f;

	return true;
}


bool Odometry::on_set_odometry_(cnbiros_robotino::SetOdometrySrv::Request &req,
							    cnbiros_robotino::SetOdometrySrv::Response &res) {

	res.result = this->set(req.x, req.y, req.phi, false);

	return res.result;
}


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

