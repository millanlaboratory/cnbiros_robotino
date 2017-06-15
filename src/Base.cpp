#ifndef CNBIROS_ROBOTINO_BASE_CPP
#define CNBIROS_ROBOTINO_BASE_CPP

#include "cnbiros_robotino/Base.hpp"

namespace cnbiros {
	namespace robotino {

Base::Base(const std::string address) {
	this->address_ = address;
	this->robotinocom_ = new Communication;
	this->robotinocom_->setAddress(address.c_str());

	this->robotinopower_ = new Power;
	this->robotinopower_->setComId(this->robotinocom_->id());
}

Base::~Base(void) {
	delete robotinocom_;
	delete robotinopower_;
}

void Base::EnableServices(ros::NodeHandle* node) {
	
	this->rossrv_communication_ = node->advertiseService(
								  node->getNamespace()+"/communication", 
								  &Base::on_communication_service_, this);
	
	this->rossrv_power_ = node->advertiseService(
						  node->getNamespace()+"/power", 
						  &Base::on_power_service_, this);

}

bool Base::on_communication_service_(cnbiros_robotino::CommService::Request &req,
									 cnbiros_robotino::CommService::Response &res) {

	res.result = false;
	switch(req.type) {
		case Base::DoConnect:
			ROS_INFO("robotino requested to connect to %s", this->GetAddress().c_str());
			res.result = this->Connect(true);
			break;
		case Base::DoDisconnect:
			ROS_INFO("robotino requested to disconnect from %s", this->GetAddress().c_str());
			res.result = this->Disconnect();
			break;
		default:
			ROS_ERROR("Unknown communication service requested");
			break;
	}

	return res.result;
}

bool Base::on_power_service_(cnbiros_robotino::PowerService::Request &req,
							 cnbiros_robotino::PowerService::Response &res) {

	res.voltage   			 = this->robotinopower_->voltage();
	res.current   			 = this->robotinopower_->current();
	res.external_power  	 = this->robotinopower_->ext_power();
	res.num_chargers 		 = this->robotinopower_->num_chargers();
	res.battery_type     	 = std::string(this->robotinopower_->batteryType());
	res.battery_low	  		 = this->robotinopower_->batteryLow();
	res.battery_low_shutdown = this->robotinopower_->batteryLowShutdownCounter();

	return true;
}

std::string Base::GetAddress(void) {
	return this->address_;
}

ComId Base::GetId(void) {
	return this->robotinocom_->id();
}

bool Base::Connect(bool isblocking) {

	if(this->IsConnected() == true) {
		ROS_INFO("robotino already connected at %s", this->GetAddress().c_str());
		return this->IsConnected();
	}

	try {
		// Set connection reconnection
		this->robotinocom_->setAutoReconnectEnabled(false);

		// Blocking function
		this->robotinocom_->connectToServer(isblocking);
	} catch (rec::robotino::api2::RobotinoException& e) {
		ROS_ERROR_ONCE("%s", e.what());
	}
		
	return this->IsConnected();
}

bool Base::Disconnect(void) {

	if(this->IsConnected() == false) {
		ROS_INFO("robotino already disconnected from %s", this->GetAddress().c_str());
	} else {
		this->robotinocom_->disconnectFromServer();
	}

	return !this->IsConnected();
}

bool Base::IsConnected(void) {
	return this->robotinocom_->isConnected();
}

void Base::ProcessEvents(void) {
	this->robotinocom_->processEvents();
}

	}
}

#endif
