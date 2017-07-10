#ifndef CNBIROS_ROBOTINO_POWER_HPP
#define CNBIROS_ROBOTINO_POWER_HPP

#include <rec/robotino/api2/PowerManagement.h>
#include <ros/ros.h>
#include <sensor_msgs/BatteryState.h>

#include "cnbiros_robotino/Base.hpp"
#include "cnbiros_robotino/GetPowerSrv.h"

namespace cnbiros {
	namespace robotino {

class Power : public rec::robotino::api2::PowerManagement {

	public:
		Power(cnbiros::robotino::Base* base);
		virtual ~Power(void);

		void readingsEvent(float voltage, float current, bool extpower, int nchargers, 
						   const char* btype, bool blow, int blowcounter);

	private:
		bool on_get_power_(cnbiros_robotino::GetPowerSrv::Request &req,
							   cnbiros_robotino::GetPowerSrv::Response &res);
	private:
		ros::ServiceServer 			rossrv_get_power_;
		ros::Publisher 			 	rospub_;
		cnbiros::robotino::Base* 	robotinobase_;
	
};

	}
}


#endif
