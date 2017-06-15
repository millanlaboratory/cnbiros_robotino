#ifndef CNBIROS_ROBOTINO_BASE_HPP
#define CNBIROS_ROBOTINO_BASE_HPP

#include "cnbiros_robotino/Communication.hpp"
#include "cnbiros_robotino/CommService.h"

namespace cnbiros {
	namespace robotino {

class Base {

	public:
		Base(const std::string address, ros::NodeHandle* node);
		~Base(void);

		std::string GetAddress(void);
		ComId GetId(void);

		bool Connect(bool isblocking = true);
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
		std::string 		address_;
		Communication*		robotinocom_;
		ros::NodeHandle* 	rosnode_;
		ros::ServiceServer 	rossrv_communication_;


};


	}
}


#endif
