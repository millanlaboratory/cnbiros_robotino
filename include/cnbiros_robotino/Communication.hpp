#ifndef CNBIROS_ROBOTINO_COMMUNICATION_HPP
#define CNBIROS_ROBOTINO_COMMUNICATION_HPP

#include <rec/robotino/api2/Com.h>
#include <ros/ros.h>

namespace cnbiros {
	namespace robotino {

typedef rec::robotino::api2::ComId ComId;

class Communication : public rec::robotino::api2::Com {
	
	public:
		virtual void errorEvent(const char* e);
		virtual void connectedEvent(void);
		virtual void connectionClosedEvent(void);

};
	}
}

#endif
