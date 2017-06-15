#ifndef CNBIROS_ROBOTINO_COMMUNICATION_CPP
#define CNBIROS_ROBOTINO_COMMUNICATION_CPP

#include "cnbiros_robotino/Communication.hpp"

namespace cnbiros {
	namespace robotino {

void Communication::errorEvent(const char* e) {
	ROS_ERROR_ONCE("robotino communication error: %s", e);
}

void Communication::connectedEvent(void) {
	ROS_INFO("robotino connected to %s", this->address());
}

void Communication::connectionClosedEvent(void) {
	ROS_INFO("robotino disconnected from %s", this->address());
}

	}
}

#endif
