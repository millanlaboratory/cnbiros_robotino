#ifndef CNBIROS_ROBOTINO_POWER_CPP
#define CNBIROS_ROBOTINO_POWER_CPP

#include "cnbiros_robotino/Power.hpp" 

namespace cnbiros {
	namespace robotino {

void Power::readingsEvent(float voltage, float current, bool extpower, int nchargers,
					 	  const char* btype, bool blow, int blowcounter) {
	if(extpower == true) {
		ROS_INFO("robotino connected to external power (battery status: voltage=%fV, current=%fA)", 
				  voltage, current);
	} else if(blow == false) {
		ROS_WARN("robotino's battery level is getting low: voltage=%fV, current=%fA", voltage, current);
		ROS_WARN("robotino's counter to shutdown: %d", blowcounter);
	}
}


	}
}

#endif

