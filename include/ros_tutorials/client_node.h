#ifndef CLIENT_NODE_H_
#define CLIENT_NODE_H_

#include <iostream>
#include <vector>
#include <ros/ros.h>
#include <string>
#include "ros_tutorials/edit_field.h"
#include "ros_tutorials/population_msg.h"
#include "ros_tutorials/file_entry.h"

using namespace std;
class client_node
{
	private:

		ros::NodeHandle* nh_;
		ros::Subscriber file_sub;
		ros::ServiceClient client;
	public:
		client_node(ros::NodeHandle* nh);
		void population_callback(const ros_tutorials::population_msg& msg);
		void make_service_request(string state_name, float population);

};


#endif