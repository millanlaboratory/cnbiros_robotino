#ifndef CNBIROS_ROBOTINO_BASE_HPP
#define CNBIROS_ROBOTINO_BASE_HPP

#include "cnbiros_robotino/Communication.hpp"
#include "cnbiros_robotino/Power.hpp"
#include "cnbiros_robotino/CommService.h"
#include "cnbiros_robotino/PowerService.h"

namespace cnbiros {
	namespace robotino {

class Base {

	public:
		Base(const std::string address);
		~Base(void);

		std::string GetAddress(void);
		ComId GetId(void);

		void EnableServices(ros::NodeHandle* node);

		bool Connect(bool isblocking = true);
		bool Disconnect(void);
		bool IsConnected(void);
		
		void ProcessEvents(void);

	private:
		bool on_communication_service_(cnbiros_robotino::CommService::Request &req,
									   cnbiros_robotino::CommService::Response &res);
		bool on_power_service_(cnbiros_robotino::PowerService::Request &req,
							 cnbiros_robotino::PowerService::Response &res);
	public:
		static const unsigned int DoConnect 	= 1;
		static const unsigned int DoDisconnect 	= 2;

	private:
		std::string 		address_;
		Communication*		robotinocom_;
		Power*				robotinopower_;
		ros::ServiceServer 	rossrv_communication_;
		ros::ServiceServer 	rossrv_power_;


};


	}
}


#endif
