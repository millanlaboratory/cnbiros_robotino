#ifndef CNBIROS_ROBOTINO_BASE_HPP
#define CNBIROS_ROBOTINO_BASE_HPP

#include "cnbiros_core/NodeInterface.hpp"
#include "cnbiros_robotino/Communication.hpp"
#include "cnbiros_robotino/CommService.h"

namespace cnbiros {
	namespace robotino {

class Base : public cnbiros::core::NodeInterface {

	public:
		Base(ros::NodeHandle* node);
		~Base(void);

		std::string GetAddress(void);
		ComId GetId(void);

		bool Connect(const std::string address = "192.168.1.3", bool isblocking = true);
		bool Disconnect(void);
		bool IsConnected(void);
		
		void ProcessEvents(void);

	private:
		bool on_communication_service_(cnbiros_robotino::CommService::Request &req,
									   cnbiros_robotino::CommService::Response &res);

	public:
		static const unsigned int DoConnect 	= 1;
		static const unsigned int DoDisconnect 	= 2;

	private:
		Communication*		robotinocom_;
		ros::ServiceServer 	rossrv_communication_;


};


	}
}


#endif
