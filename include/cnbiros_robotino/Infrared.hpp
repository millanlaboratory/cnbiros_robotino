#ifndef CNBIROS_ROBOTINO_INFRARED_HPP
#define CNBIROS_ROBOTINO_INFRARED_HPP

#include <rec/robotino/api2/DistanceSensorArray.h>

#include <ros/ros.h>
#include <sensor_msgs/PointCloud.h>

#include "cnbiros_core/NodeInterface.hpp"
#include "cnbiros_robotino/Base.hpp"
#include "cnbiros_robotino/Flags.hpp"

namespace cnbiros {
	namespace robotino {

class Infrared :  public cnbiros::core::NodeInterface,
				  public rec::robotino::api2::DistanceSensorArray {

	public:
		Infrared(cnbiros::robotino::Base* base, ros::NodeHandle* node);
		~Infrared(void);


	private:
		void onRunning(void) {};
		void distancesChangedEvent(const float* ranges, unsigned int size);

	private:
		cnbiros::robotino::Base* robotinobase_;
		ros::Publisher 			 rospub_;
};


	}
}

#endif
