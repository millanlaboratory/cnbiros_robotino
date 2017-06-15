#ifndef CNBIROS_ROBOTINO_POWER_HPP
#define CNBIROS_ROBOTINO_POWER_HPP

#include <rec/robotino/api2/PowerManagement.h>
#include <ros/ros.h>

namespace cnbiros {
	namespace robotino {

class Power : public rec::robotino::api2::PowerManagement {

	public:
		void readingsEvent(float voltage, float current, bool extpower, int nchargers, 
						   const char* btype, bool blow, int blowcounter);


	
};

	}
}


#endif
