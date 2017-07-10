#ifndef CNBIROS_ROBOTINO_ODOMETRY_HPP
#define CNBIROS_ROBOTINO_ODOMETRY_HPP

#include <rec/robotino/api2/Odometry.h>

#include <ros/ros.h>
#include "tf/transform_datatypes.h"
#include <nav_msgs/Odometry.h>

#include "cnbiros_robotino/Base.hpp"
#include "cnbiros_robotino/Flags.hpp"
#include "cnbiros_robotino/GetOdometrySrv.h"
#include "cnbiros_robotino/SetOdometrySrv.h"

namespace cnbiros {
	namespace robotino {

class Odometry : public rec::robotino::api2::Odometry {

	public:
		Odometry(cnbiros::robotino::Base* base);
		~Odometry(void);

	private:

		bool on_get_odometry_(cnbiros_robotino::GetOdometrySrv::Request &req,
							  cnbiros_robotino::GetOdometrySrv::Response &res);
		bool on_set_odometry_(cnbiros_robotino::SetOdometrySrv::Request &req,
							  cnbiros_robotino::SetOdometrySrv::Response &res);

		void readingsEvent(double x, double y, double omega, 
				           float vx, float vy, float vomega, 
						   unsigned int sequence);

	private:
		cnbiros::robotino::Base* robotinobase_;
		ros::Publisher 			 rospub_;
		ros::ServiceServer 	     rossrv_get_odometry_;
		ros::ServiceServer 	     rossrv_set_odometry_;

};

	}
}

#endif
