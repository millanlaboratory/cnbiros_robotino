#ifndef CNBIROS_ROBOTINO_BASE_CPP
#define CNBIROS_ROBOTINO_BASE_CPP

#include "cnbiros_robotino/Base.hpp"

namespace cnbiros {
	namespace robotino {

Base::Base(const std::string address, ros::NodeHandle* node) {
	this->address_ = address;
	this->robotinocom_ = new Communication;
	this->robotinocom_->setAddress(address.c_str());

	this->rosnode_ = node;
	this->rossrv_communication_ = this->rosnode_->advertiseService(
								  this->rosnode_->getNamespace()+"/communication", 
								  &Base::on_communication_service_, this);
}

Base::~Base(void) {
	delete robotinocom_;
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
