#ifndef CNBIROS_ROBOTINO_MOTORS_CPP
#define CNBIROS_ROBOTINO_MOTORS_CPP

#include "cnbiros_robotino/Motors.hpp"

namespace cnbiros {
	namespace robotino {

Motors::Motors(cnbiros::robotino::Base* base) {
	this->robotinobase_ = base;
	this->setComId(base->GetId());
	this->rossub_ = base->GetNode()->subscribe(base->GetNode()->getNamespace()+"/cmd_vel", 
									 CNBIROS_CORE_BUFFER_MESSAGES, &Motors::on_command_velocity, this);
}

Motors::~Motors(void){}

void Motors::on_command_velocity(const geometry_msgs::Twist& msg) {

	this->setVelocity(msg.linear.x, msg.linear.y, msg.angular.z);
}


	}
}

#endif
