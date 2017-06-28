#ifndef CNBIROS_ROBOTINO_POWER_CPP
#define CNBIROS_ROBOTINO_POWER_CPP

#include "cnbiros_robotino/Power.hpp" 

namespace cnbiros {
	namespace robotino {

Power::Power(cnbiros::robotino::Base* base) {
	this->robotinobase_ = base;
	
	// Robotino base connection
	this->setComId(base->GetId());

	// Topic initialization
	this->rospub_ = base->GetNode()->advertise<sensor_msgs::BatteryState>
								("power", CNBIROS_CORE_BUFFER_MESSAGES);

	// Ros initialization
	this->rossrv_power_ = base->GetNode()->advertiseService(
					  	  "get_power_info", &Power::on_power_service_, this);
}

Power::~Power(void) {}

bool Power::on_power_service_(cnbiros_robotino::PowerService::Request &req,
							  cnbiros_robotino::PowerService::Response &res) {

	res.voltage   			 = this->voltage();
	res.current   			 = this->current();
	res.external_power  	 = this->ext_power();
	res.num_chargers 		 = this->num_chargers();
	res.battery_type     	 = std::string(this->batteryType());
	res.battery_low	  		 = this->batteryLow();
	res.battery_low_shutdown = this->batteryLowShutdownCounter();

	return true;
}

void Power::readingsEvent(float voltage, float current, bool extpower, int nchargers,
					 	  const char* btype, bool blow, int blowcounter) {

	// Created by L.Tonin  <luca.tonin@epfl.ch> on 19/06/17 12:52:46	
	// api not working!
	
	sensor_msgs::BatteryState msg;
	msg.voltage = voltage;
	msg.current = current;

	if(extpower == true) {
		ROS_INFO("robotino connected to external power (battery status: voltage=%fV, current=%fA)", 
				  voltage, current);
	} else if(blow == true) {
		ROS_WARN("robotino's battery level is getting low: voltage=%fV, current=%fA", voltage, current);
		ROS_WARN("robotino's counter to shutdown: %d", blowcounter);
	}

	this->rospub_.publish(msg);
}


	}
}

#endif

