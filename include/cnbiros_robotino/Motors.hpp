#ifndef CNBIROS_ROBOTINO_MOTORS_HPP
#define CNBIROS_ROBOTINO_MOTORS_HPP

#include <rec/robotino/api2/OmniDrive.h>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include "cnbiros_robotino/Base.hpp"
#include "cnbiros_robotino/Flags.hpp"

namespace cnbiros {
	namespace robotino {

class Motors : public rec::robotino::api2::OmniDrive {
	
	public:
		Motors(cnbiros::robotino::Base* base);
		~Motors(void);

	private:
		void on_command_velocity(const geometry_msgs::Twist& msg);

	private:
		cnbiros::robotino::Base* robotinobase_;
		ros::Subscriber 		 rossub_;

};
	}
}

#endif

