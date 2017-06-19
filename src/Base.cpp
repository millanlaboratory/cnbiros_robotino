#ifndef CNBIROS_ROBOTINO_BASE_CPP
#define CNBIROS_ROBOTINO_BASE_CPP

#include "cnbiros_robotino/Base.hpp"

namespace cnbiros {
	namespace robotino {

Base::Base(ros::NodeHandle* node) : cnbiros::core::NodeInterface(node, "robotino_base") {
	this->robotinocom_ = new Communication;

	this->rossrv_communication_ = node->advertiseService(
								  node->getNamespace()+"/communication", 
								  &Base::on_communication_service_, this);
}

Base::~Base(void) {
	delete robotinocom_;
}

bool Base::on_communication_service_(cnbiros_robotino::CommService::Request &req,
									 cnbiros_robotino::CommService::Response &res) {

	res.result = true;
	switch(req.type) {
		case Base::DoConnect:
			ROS_INFO("robotino requested to connect to %s", req.address.c_str());
			this->Connect(req.address.c_str(), true);
			break;
		case Base::DoDisconnect:
			ROS_INFO("robotino requested to disconnect");
			this->Disconnect();
			break;
		default:
			ROS_ERROR("Unknown communication service requested");
			break;
	}

	res.connected = this->IsConnected();

	return res.result;
}

std::string Base::GetAddress(void) {
	std::string address = "undefined_address";
	if(this->IsConnected()) {
		this->robotinocom_->address();
	} else {
		ROS_WARN("robotino is not connected to any address");
	}

	return address;
}

ComId Base::GetId(void) {
	return this->robotinocom_->id();
}

bool Base::Connect(const std::string address, bool isblocking) {

	if(this->IsConnected() == true) {
		ROS_WARN("robotino already connected at %s. Need to be disconnected first.", 
				 this->robotinocom_->address());
		return this->IsConnected();
	} else {
		this->robotinocom_->setAddress(address.c_str());
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
		ROS_WARN("robotino is not connected");
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

void Base::onRunning(void) {
	this->ProcessEvents();
}

	}
}

#endif
